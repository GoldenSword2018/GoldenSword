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
//	�O���[�o��
//-------------------------------------
std::vector<Transform*>  Transform::pIndex;

//===============================================
//	Constructor/Destroctor
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Transform::Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation)
{
	this->m_bEnable_Convert = true;
	this->m_bConverted = false;
	this->m_pParent = NULL;

	//���[���h�ʒu��ݒ�
	this->m_Position = Position;
	this->m_Rotation = Rotation;
	this->m_Scale = Scale;

	this->Get_MtxWorld();

	//�o�^
	pIndex.push_back(this);
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
Transform::~Transform()
{
	this->m_pParent = NULL;

	//�q�������Ă���Ȃ�
	if (this->m_pChild.size() > 0)
	{
		for (int i = 0; i < this->m_pChild.size(); i++)
		{
			//�e�𖳂���
			this->m_pChild.at(i)->Release_Parent();
		}
	}
}

//===============================================
//	�s��ϊ�
//===============================================

void Transform::g_Convert()
{
	for (int i = 0; i < pIndex.size(); i++)
	{
		pIndex.at(i)->m_bConverted = false;	//���s��ϊ�
		pIndex.at(i)->Convert();
	}
}

//-------------------------------------
//	�s��ϊ� �J�n
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
//	���[���h���
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

//�EGet Position	�ʒu���
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

//�EGet Rotation	��]���
//	�e�̃��[���h��]�l�Ɏ��g�̉�]�l�����Z
//
D3DXVECTOR3 Transform::Get_Rotation()
{
	if(this->Have_a_Parent())
	{
		this->m_Rotation += this->m_pParent->Get_Rotation();
	}

	return this->m_Rotation;
}

//�EGet Scale		�傫�����
//	�e�̃X�P�[���l�Ɏ��g�̃X�P�[���l����Z
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
	//�e�Ƃ̑��Έʒu���Z�o
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
//	�s��֌W
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

//	Get MtxTransform	�ʒu�s��
D3DXMATRIX Transform::Get_MtxTransform()
{
	D3DXMatrixTranslation(&this->m_MtxTransform,this->m_Position.x,this->m_Position.y,this->m_Position.z);
	
	if(this->Have_a_Parent())
	{
		this->m_MtxTransform *= this->m_pParent->Get_MtxTransform();
	}

	return this->m_MtxTransform;
}

//	Get MtxRotation	��]�s��
D3DXMATRIX Transform::Get_MtxRotation()
{
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation,this->m_Rotation.y,this->m_Rotation.x,this->m_Rotation.z);
	
	if (this->Have_a_Parent())
	{
		this->m_MtxRotation *= this->m_pParent->Get_MtxRotation();
	}
	
	return this->m_MtxRotation;
}

//	Get MtxScale	�T�C�Y�s��
D3DXMATRIX Transform::Get_MtxScale()
{
	D3DXMatrixScaling(&this->m_MtxScale,this->m_Scale.x,this->m_Scale.y,this->m_Scale.z);

	if(this->Have_a_Parent())
	{
		this->m_MtxScale *= this->m_pParent->Get_MtxScale();
	}

	return this->m_MtxScale;
}

//	Get MtxWorld ���[���h��ԍs��
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
//	���΍s�� �擾
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
//	�s��@�ݒ�
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
//	���Έʒu �擾
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
//	���Έʒu �ݒ�
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
//	�����֌W
//-------------------------------------

//Get ��
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

//Get �E
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

//Get �O
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
//	��]�֐�
//===============================================

//-------------------------------------
//	Rotation
//-------------------------------------
void Transform::RotationVec3(const D3DXVECTOR3 value)
{
	this->m_Rotation += value;	//���Z

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
	D3DXVec3TransformNormal(&VecAxis, &VecAxis, &MtxAxis);	//�ω��l�𓾂�

	this->m_Rotation += VecAxis;	//���Z

	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	return;
}

//===============================================
//	�e�q�֌W
//===============================================

//-------------------------------------
//	�e��ݒ�
//-------------------------------------
void Transform::Set_Parent(Transform* pParent)
{
	this->m_pParent = pParent;
	pParent->m_pChild.push_back(this);
}

//-------------------------------------
//	�擾
//-------------------------------------
Transform* Transform::Get_Parent()
{
	return this->m_pParent;
}

//-------------------------------------
//	�e�Ɨ����
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
