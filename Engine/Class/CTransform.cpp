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
//	�R���X�g���N�^
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
//	�R���X�g���N�^
//-------------------------------------
Transform::Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation, D3DCOLOR Color)
{
	this->bConverted = false;
	this->pParent = NULL;

	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;
	this->Color = Color;

	this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	this->forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Normalize(&this->forward, &this->forward);

	D3DXVec3Cross(&this->right, &this->forward, &this->up);
	D3DXVec3Normalize(&this->right, &this->right);

	pIndex.push_back(this);
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
Transform::~Transform()
{
	this->pParent = NULL;

	//�q�������Ă���Ȃ�
	if (this->pChild.size() > 0)
	{
		for (int i = 0; i < this->pChild.size(); i++)
		{
			this->pChild.at(i)->Release_Parent();
		}

	}

}

//-------------------------------------
//	�s��ϊ��J�n
//-------------------------------------
D3DXMATRIX Transform::Convert()
{
	if (this->bConverted) return this->MtxWorld;

	D3DXMATRIX MtxTransform;
	D3DXMATRIX MtxScale;
	D3DXMATRIX MtxRotation;

	//�ϊ�
	D3DXMatrixIdentity(&this->MtxWorld);
	D3DXMatrixTranslation(&MtxTransform,this->Position.x, this->Position.y,this->Position.z);
	D3DXMatrixScaling(&MtxScale, this->Scale.x,this->Scale.y,this->Scale.z);
	D3DXMatrixRotationYawPitchRoll(&MtxRotation,this->Rotation.y,this->Rotation.x,this->Rotation.z);

	//���[�J������
	D3DXVec3TransformNormal(&this->right,&this->right,&MtxRotation);
	D3DXVec3TransformNormal(&this->forward,&this->forward,&MtxRotation);
	D3DXVec3Cross(&this->up,&this->right,&this->forward);

	//����
	this->MtxWorld *= MtxScale * MtxRotation * MtxTransform;

	//�e������
	if(this->pParent != NULL)
	{
		//�e�̍s������Ă���
		this->MtxWorld *= this->pParent->Convert();
	}

	//�ϊ��I��
	this->bConverted = true;

	return this->MtxWorld;
}

//-------------------------------------
//	�e��ݒ�
//-------------------------------------
void Transform::Set_Parent(Transform* pParent)
{
	this->pParent = pParent;
	pParent->pChild.push_back(this);
}

//-------------------------------------
//	�e�Ɨ����
//-------------------------------------
void Transform::Release_Parent()
{

}

//-----------------------------------------------
//	�O���[�o��
//-----------------------------------------------
void Transform::ResetConvert()
{
	for(int i = 0; i < pIndex.size(); i++)
	{
		pIndex.at(i)->bConverted = false;
	}
}

//===============================================
//	Transform2
//===============================================

//-------------------------------------
//	�R���X�g���N�^
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
