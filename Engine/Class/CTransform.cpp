//
//	Transform.cpp
//		Author:HIROMASA IKEDA	DATA:2018/12/02
//===============================================
#include<d3dx9.h>
#include"CTransform.h"
#include"Animation.h"

//=========================================================
//	Transform3
//=========================================================

//-------------------------------------
//	グローバル
//-------------------------------------
std::vector<Transform*>  Transform::pIndex;

//===============================================
//	Constructor/Destroctor
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Transform::Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation)
{
	this->m_bEnable_Convert = true;
	this->m_bConverted = false;
	this->m_pParent = NULL;

	//ワールド位置を設定
	this->m_Position = Position;
	this->m_Rotation = Rotation;
	this->m_Scale = Scale;

	this->Get_MtxWorld();

	//登録
	pIndex.push_back(this);
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
Transform::~Transform()
{
	this->m_pParent = NULL;

	//子を持っているなら
	if (this->m_pChild.size() > 0)
	{
		for (int i = 0; i < this->m_pChild.size(); i++)
		{
			//親を無くす
			this->m_pChild.at(i)->Release_Parent();
		}
	}
}

//===============================================
//	行列変換
//===============================================

void Transform::g_Convert()
{
	for (int i = 0; i < pIndex.size(); i++)
	{
		pIndex.at(i)->m_bConverted = false;	//未行列変換
		pIndex.at(i)->Convert();
	}
}

//-------------------------------------
//	行列変換 開始
//-------------------------------------

D3DXMATRIX Transform::Convert() 
{
	if (this->m_bConverted == true || this->m_bEnable_Convert == true) return this->m_MtxWorld;

	D3DXMatrixIdentity(&this->m_MtxWorld);
	D3DXMatrixTranslation(&this->m_MtxTransform, this->m_Position.x, this->m_Position.y, this->m_Position.z);
	D3DXMatrixScaling(&this->m_MtxScale, this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	this->m_MtxWorld = this->m_MtxScale * this->m_MtxRotation * this->m_MtxTransform;

	if(this->Have_a_Parent())
	{
		this->m_MtxWorld *= this->m_pParent->Convert();
	}

	this->m_bConverted = true;

	return this->m_MtxWorld;
}

//-------------------------------------
//	ワールド情報
//-------------------------------------

D3DXVECTOR3* Transform::Position()
{
	this->Get_Position();
	return &this->m_Rotation;
}

D3DXVECTOR3* Transform::Rotation()
{
	this->Get_Rotation();
	return &this->m_Rotation;
}

D3DXVECTOR3* Transform::Scale()
{
	this->Get_Scale();
	return &this->m_Scale;
}

//・Get Position	位置情報
D3DXVECTOR3 Transform::Get_Position()
{
	if(this->Have_a_Parent())
	{
		D3DXVECTOR3 position;
		D3DXVec3TransformCoord(&position,&position,&this->Get_MtxWorld());
		return position;
	}
	
	return this->m_Position;
}

//・Get Rotation	回転情報
//	親のワールド回転値に自身の回転値を加算
//
D3DXVECTOR3 Transform::Get_Rotation()
{
	if(this->Have_a_Parent())
	{
		this->m_Rotation += this->m_pParent->Get_Rotation();
	}

	return this->m_Rotation;
}

//・Get Scale		大きさ情報
//	親のスケール値に自身のスケール値を乗算
//	
D3DXVECTOR3 Transform::Get_Scale()
{
	D3DXVECTOR3 Scale = this->m_Scale;

	if(this->Have_a_Parent())
	{
		D3DXVECTOR3 ParentScale = this->m_pParent->Get_Scale();
		Scale.x *= ParentScale.x;
		Scale.y *= ParentScale.y;
		Scale.z *= ParentScale.z;
	}

	return Scale;
}

//Set Position
void Transform::Set_Position(D3DXVECTOR3 Position)
{
	//親との相対位置を算出
	if(this->Have_a_Parent())
	{
		Position -= this->m_pParent->Get_Position();
	}

	this->m_Position = Position;

	return;
}

//Set Rotation
void Transform::Set_Rotation(D3DXVECTOR3 Rotation)
{
	if(this->Have_a_Parent())
	{
		Rotation -= this->m_pParent->Get_Rotation();
	}

	this->m_Rotation = Rotation;

	return;
}

//Set Scale
void Transform::Set_Scale(D3DXVECTOR3 Scale)
{
	if(this->Have_a_Parent())
	{
		D3DXVECTOR3 scale = this->m_pParent->Get_Scale();
		Scale.x /= scale.x;
		Scale.y /= scale.y;
		Scale.z /= scale.z;
	}

	this->m_Scale = Scale;
	return;
}

//-------------------------------------
//	行列関係
//-------------------------------------

D3DXMATRIX* Transform::MtxTransform()
{
	this->Get_MtxTransform();
	return &this->m_MtxTransform;
}

D3DXMATRIX* Transform::MtxScale()
{
	this->Get_MtxScale();
	return &this->m_MtxScale;
}

D3DXMATRIX* Transform::MtxRotation()
{
	this->Get_MtxRotation();
	return &this->m_MtxRotation;
}

D3DXMATRIX* Transform::MtxWorld()
{
	this->Get_MtxWorld();
	return &this->m_MtxWorld;
}

//	Get MtxTransform	位置行列
D3DXMATRIX Transform::Get_MtxTransform()
{
	D3DXMatrixTranslation(&this->m_MtxTransform,this->m_Position.x,this->m_Position.y,this->m_Position.z);
	
	if(this->Have_a_Parent())
	{
		this->m_MtxTransform *= this->m_pParent->Get_MtxTransform();
	}

	return this->m_MtxTransform;
}

//	Get MtxRotation	回転行列
D3DXMATRIX Transform::Get_MtxRotation()
{
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation,this->m_Rotation.y,this->m_Rotation.x,this->m_Rotation.z);
	
	if (this->Have_a_Parent())
	{
		this->m_MtxRotation *= this->m_pParent->Get_MtxRotation();
	}
	
	return this->m_MtxRotation;
}

//	Get MtxScale	サイズ行列
D3DXMATRIX Transform::Get_MtxScale()
{
	D3DXMatrixScaling(&this->m_MtxScale,this->m_Scale.x,this->m_Scale.y,this->m_Scale.z);

	if(this->Have_a_Parent())
	{
		this->m_MtxScale *= this->m_pParent->Get_MtxScale();
	}

	return this->m_MtxScale;
}

//	Get MtxWorld ワールド空間行列
D3DXMATRIX Transform::Get_MtxWorld()
{
	D3DXMatrixTranslation(&this->m_MtxTransform, this->m_Position.x, this->m_Position.y, this->m_Position.z);
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);
	D3DXMatrixScaling(&this->m_MtxScale, this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);

	this->m_MtxWorld = this->m_MtxScale * this->m_MtxRotation * this->m_MtxTransform;

	if(this->Have_a_Parent())
	{
		this->m_MtxWorld *= this->m_pParent->Get_MtxWorld();
	}

	return this->m_MtxWorld;
}

//-------------------------------------
//	相対行列 取得
//-------------------------------------

D3DXMATRIX Transform::Get_localMtxTransform()
{
	D3DXMatrixTranslation(&this->m_MtxTransform, this->m_Position.x, this->m_Position.y, this->m_Position.z);
	return this->m_MtxTransform;
}

D3DXMATRIX Transform::Get_localMtxScale()
{
	D3DXMatrixScaling(&this->m_MtxScale, this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);
	return this->m_MtxScale;
}

D3DXMATRIX Transform::Get_localMtxRotation()
{
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);
	return this->m_MtxRotation;
}

D3DXMATRIX Transform::Get_localMtxWorld() 
{
	this->m_MtxWorld = this->Get_MtxScale() * this->Get_MtxRotation() * this->Get_MtxTransform();
	return this->m_MtxWorld;
}

//-------------------------------------
//	行列　設定
//-------------------------------------

void Transform::Set_MtxTransform(D3DXMATRIX MtxTransform)
{
	this->m_MtxTransform = MtxTransform;
}

void Transform::Set_MtxScale(D3DXMATRIX MtxScale) 
{
	this->m_MtxScale = MtxScale;
}

void Transform::Set_MtxRotation(D3DXMATRIX MtxRotation)
{
	this->m_MtxRotation = MtxRotation;
}

void Transform::Set_MtxWorld(D3DXMATRIX MtxWorld)
{
	this->m_MtxWorld = MtxWorld;
}

//-------------------------------------
//	相対位置 取得
//-------------------------------------

D3DXVECTOR3 Transform::Get_localPosition()
{
	return this->m_Position;
}

D3DXVECTOR3 Transform::Get_localRotation()
{
	return this->m_Rotation;
}

D3DXVECTOR3 Transform::Get_localScale()
{
	return this->m_Scale;
}

//-------------------------------------
//	相対位置 設定
//-------------------------------------

void Transform::Set_localPosition(D3DXVECTOR3 position)
{
	this->m_Position = position;
}

void Transform::Set_localRotation(D3DXVECTOR3 rotation)
{
	this->m_Rotation = rotation;
}

void Transform::Set_localScale(D3DXVECTOR3 scale)
{
	this->m_Scale = scale;
}

//-------------------------------------
//	方向関係
//-------------------------------------

//Get 上
D3DXVECTOR3 Transform::Get_Up()
{
	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);
	
	//up
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVec3TransformNormal(&up, &up, &MtxRotation);
	D3DXVec3Normalize(&up, &up);

	return up;
}

//Get 右
D3DXVECTOR3 Transform::Get_Right()
{
	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	//right
	D3DXVECTOR3 right(1.0f, 0.0f, 0.0f);
	D3DXVec3TransformNormal(&right, &right, &MtxRotation);
	D3DXVec3Normalize(&right, &right);

	return right;
}

//Get 前
D3DXVECTOR3 Transform::Get_Forward()
{
	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	//right
	D3DXVECTOR3 forward(0.0f, 0.0f, 1.0f);
	D3DXVec3TransformNormal(&forward, &forward, &MtxRotation);
	D3DXVec3Normalize(&forward, &forward);

	return forward;
}

//===============================================
//	回転関数
//===============================================

//-------------------------------------
//	Rotation
//-------------------------------------
void Transform::RotationVec3(const D3DXVECTOR3 value)
{
	this->m_Rotation += value;	//加算

	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	return;
}

//-------------------------------------
//	RotationAxis
//-------------------------------------
void Transform::RotationAxis(const D3DXVECTOR3 Axis, const float Value)
{
	D3DXMATRIX MtxAxis;
	D3DXMatrixRotationAxis(&MtxAxis, &Axis, Value);

	D3DXVECTOR3 VecAxis;
	D3DXVec3TransformNormal(&VecAxis, &VecAxis, &MtxAxis);	//変化値を得る

	this->m_Rotation += VecAxis;	//加算

	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	return;
}

//===============================================
//	親子関係
//===============================================

//-------------------------------------
//	親を設定
//-------------------------------------
void Transform::Set_Parent(Transform* pParent)
{
	this->m_pParent = pParent;
	pParent->m_pChild.push_back(this);
}

//-------------------------------------
//	取得
//-------------------------------------
Transform* Transform::Get_Parent()
{
	return this->m_pParent;
}

//-------------------------------------
//	親と離れる
//-------------------------------------
void Transform::Release_Parent()
{
	this->m_pParent = NULL;
}

void Transform::ConvertEnable(bool enable)
{
	this->m_bEnable_Convert = enable;
}

bool Transform::Have_a_Parent()
{
	if(this->m_pParent != NULL)
	{
		return true;
	}

	return false;
};

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
