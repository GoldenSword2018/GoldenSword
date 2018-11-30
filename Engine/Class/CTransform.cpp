//
//	Transform.cpp
//		Author:HIROMASA IKEDA	DATA:2018/09/28
//===============================================
#include<d3dx9.h>
#include"CTransform.h"
#include"Animation.h"

//===============================================
//	MatrixTransform 
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
MatrixTransform::MatrixTransform()
{
	D3DXMatrixIdentity(&this->MtxWorld);
	D3DXMatrixIdentity(&this->MtxTransform);
	D3DXMatrixIdentity(&this->MtxRotation);
}

//-------------------------------------
//	
//-------------------------------------

//===============================================
//	Transform3
//===============================================
std::vector<Transform*>  Transform::pIndex;

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Transform::Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation, D3DCOLOR Color)
{
	this->bConverted = false;
	this->pParent = NULL;

	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;
	this->WorldPosition = Position;
	this->Color = Color;

	this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	this->forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Normalize(&this->forward, &this->forward);

	D3DXVec3Cross(&this->right, &this->forward, &this->up);
	D3DXVec3Normalize(&this->right, &this->right);

	pIndex.push_back(this);
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
Transform::~Transform()
{
	this->pParent = NULL;

	//子を持っているなら
	if (this->pChild.size() > 0)
	{
		for (int i = 0; i < this->pChild.size(); i++)
		{
			this->pChild.at(i)->Release_Parent();
		}

	}

}

//-------------------------------------
//	行列変換開始
//-------------------------------------
D3DXMATRIX Transform::Convert()
{
	if (this->bConverted) return this->MtxWorld;

	D3DXMATRIX MtxTransform;
	D3DXMATRIX MtxScale;
	D3DXMATRIX MtxRotation;

	//変換
	D3DXMatrixIdentity(&this->MtxWorld);
	D3DXMatrixTranslation(&MtxTransform,this->Position.x, this->Position.y,this->Position.z);
	D3DXMatrixScaling(&MtxScale, this->Scale.x,this->Scale.y,this->Scale.z);
	D3DXMatrixRotationYawPitchRoll(&MtxRotation,this->Rotation.y,this->Rotation.x,this->Rotation.z);

	//ローカル方向
	this->up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	D3DXVec3TransformNormal(&this->up,&this->up,&MtxRotation);
	D3DXVec3Normalize(&this->up,&this->up);
	
	this->forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3TransformNormal(&this->forward,&this->forward,&MtxRotation);
	D3DXVec3Normalize(&this->forward,&this->forward);

	D3DXVec3Cross(&this->right,&this->up,&this->forward);

	//合成
	this->MtxWorld = MtxScale * MtxRotation * MtxTransform;

	//親が居る
	if(this->pParent != NULL)
	{
		//親の行列を見てくる
		this->MtxWorld *= this->pParent->Convert();
		this->WorldPosition = this->pParent->Position + this->Position;
	}
	else
	{
		this->WorldPosition = this->Position;
	}

	//変換終了
	this->bConverted = true;

	return this->MtxWorld;
}

//-------------------------------------
//	親を設定
//-------------------------------------
void Transform::Set_Parent(Transform* pParent)
{
	this->pParent = pParent;
	pParent->pChild.push_back(this);
	this->Set_WorldTransform();
}

//-------------------------------------
//	親と離れる
//-------------------------------------
void Transform::Release_Parent()
{

}

//-----------------------------------------------
//	グローバル
//-----------------------------------------------
void Transform::ResetConvert()
{
	for(int i = 0; i < pIndex.size(); i++)
	{
		pIndex.at(i)->bConverted = false;
	}
}

void Transform::Set_WorldTransform()
{
	if(this->pParent != NULL)
	{
		this->pParent->Set_WorldTransform();
		this->WorldPosition = this->pParent->WorldPosition + this->Position;
		this->WorldRotation = this->pParent->WorldRotation + this->Rotation;
	}
	else
	{
		this->WorldPosition = this->Position;
		this->WorldRotation = this->Rotation;
	}
}

D3DXVECTOR3 Transform::GetWorldPosision( void )
{
	if( this->pParent != NULL )
	{
		D3DXVECTOR3 WorldPos;
		D3DXVec3TransformCoord( &WorldPos, &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), &this->GetWorldMatrix() );
		return WorldPos;
	}
	else
	{
		return this->Position;
	}
}


D3DXMATRIX Transform::GetWorldMatrix( void )
{
	D3DXMATRIX MtxTranslation;
	D3DXMATRIX MtxRotation;
	D3DXMATRIX MtxScale;


	//変換
	D3DXMatrixTranslation( &MtxTranslation, this->Position.x, this->Position.y, this->Position.z );
	D3DXMatrixScaling( &MtxScale, this->Scale.x, this->Scale.y, this->Scale.z );
	D3DXMatrixRotationYawPitchRoll( &MtxRotation, this->Rotation.y, this->Rotation.x, this->Rotation.z );


	D3DXMATRIX _MtxWorld;
	D3DXMatrixIdentity( &_MtxWorld );
	_MtxWorld = MtxScale * MtxRotation * MtxTranslation;

	if( this->pParent != NULL )
	{
		_MtxWorld *= this->pParent->GetWorldMatrix();
	}
	else
	{
		// null
	}

	return _MtxWorld;
}

void Transform::SetWorldPosition( D3DXVECTOR3 NewPos )
{
	if( this->pParent != NULL )
	{ // 親がいるので、相対座標を変更。
		this->Position += this->GetWorldPosision() - NewPos;
	}
	else
	{ // 親がいないので、ワールド座標を変更
		this->Position = NewPos;
	}
}


void Transform::SetLocalPosition( D3DXVECTOR3 NewPos )
{
	this->Position = NewPos;
}

//===============================================
//	Transform2
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Transform2::Transform2()
{
	Position = {0.0f,0.0f};
	Scale = {1.0f,1.0f};
	Rotation = 0;
	Color = Color;
}

Transform2::Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation)
{
	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;
	Color = D3DCOLOR_RGBA(255,255,255,255);
}

Transform2::Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation, D3DCOLOR Color)
{
	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;
	this->Color = Color;
}
