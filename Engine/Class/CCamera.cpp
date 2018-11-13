//
//	CCamera.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/17
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include<d3dx9.h>
#include"common.h"
#include"input.h"

//class
#include"CCamera.h"

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================
Camera* Camera::MainCamera = NULL;
Camera* Camera::MainCamera1 = NULL;
Camera* Camera::MainCamera2 = NULL;
Camera* Camera::MainCamera3 = NULL;

//===============================================
//	�J����		class
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Camera::Camera(D3DXVECTOR3 Position, D3DXVECTOR3 At,float AtDistance,float fov)
{
	this->position = Position;
	this->at = At;
	this->up = CAMERA_UP;
	this->atDistance = AtDistance;
	this->fov = fov;
	this->Speed = CAMERA_INITIALSPEED;

	//�O

	this->forward = CAMERA_FORWARD;
	D3DXVec3Normalize(&this->forward, &this->forward);

	//�E
	D3DXVec3Cross(&this->right, &this->forward, &this->up);
	D3DXVec3Normalize(&this->right, &this->right);
}

//-------------------------------------
//	������
//-------------------------------------
void Camera::Initialize()
{
	return;
}

//-------------------------------------
//	�X�V
//-------------------------------------
void Camera::Update()
{
	//------------------------------------
	//	�J����
	//------------------------------------
	this->at = this->forward * this->atDistance + this->position;

	D3DXVECTOR3 front = this->forward;
	D3DXVECTOR3 right = this->right;

	if(Keyboard_IsPress(DIK_LCONTROL))
	{
		if(Mouse_IsRightDown())
		{
			D3DXMATRIX mtxRotation;
			D3DXVECTOR3 AxisVec = this->at;
			AxisVec.x = 0;
			AxisVec.z = 0;
			D3DXMatrixRotationAxis(&mtxRotation,&AxisVec,Mouse_IsAccelerationX() * 0.001f);
			D3DXVec3TransformNormal(&this->forward, &this->forward, &mtxRotation);	//�x�N�g�����W�ϊ�
			D3DXVec3TransformNormal(&this->right, &this->right, &mtxRotation);
			D3DXVec3Cross(&this->up, &this->right, &this->forward);
		}

		this->position = at - this->forward * this->atDistance;
	}
	else
	{
		if (Mouse_IsRightDown())
		{
			D3DXMATRIX mtxRotation;
			D3DXMatrixRotationY(&mtxRotation, Mouse_IsAccelerationX() * 0.001f);
			D3DXVec3TransformNormal(&this->forward, &this->forward, &mtxRotation);	//�x�N�g�����W�ϊ�
			D3DXVec3TransformNormal(&this->right, &this->right, &mtxRotation);
			D3DXVec3Cross(&this->up, &this->right, &this->forward);

			D3DXMatrixIdentity(&mtxRotation);
			D3DXMatrixRotationAxis(&mtxRotation, &this->right, Mouse_IsAccelerationY() * -0.001f);
			D3DXVec3TransformNormal(&this->forward, &this->forward, &mtxRotation);	//�x�N�g�����W�ϊ�
			D3DXVec3TransformNormal(&this->right, &this->right, &mtxRotation);
			D3DXVec3Cross(&this->up, &this->right, &this->forward);

		}

		if (Keyboard_IsPress(DIK_W))
		{
			this->position += front * this->Speed;
		}

		if (Keyboard_IsPress(DIK_S))
		{
			this->position -= front * this->Speed;
		}

		if (Keyboard_IsPress(DIK_A))
		{
			this->position += right * this->Speed;
		}

		if (Keyboard_IsPress(DIK_D))
		{
			this->position -= right * this->Speed;
		}

		if (Keyboard_IsPress(DIK_Q))
		{
			this->position.y -= this->Speed;
		}

		if (Keyboard_IsPress(DIK_E))
		{
			this->position.y += this->Speed;
		}
		this->position += this->forward * Mouse_IsAccelerationZ() *0.01f;
	}

	return;
}


//-------------------------------------
//	���C���J�����ɐݒ�
//-------------------------------------
void Camera::Set_Main()
{
	this->MainCamera = this;
}

//�ʁX�o�^
void Camera::Set_Main(int Num)
{
	switch (Num)
	{
	case 0:
		this->MainCamera = this;
		break;
	case 1:
		this->MainCamera1 = this;
		break;
	case 2:
		this->MainCamera2 = this;
		break;
	case 3:
		this->MainCamera3 = this;
		break;
	default:
		this->MainCamera = this;
		break;
	}
}

//-------------------------------------
//	�T�u�J�����ɐݒ�
//-------------------------------------
//void Camera::Set_Sub()
//{
//	this->SubCamera = this;
//}

//-------------------------------------
//	���C���J�����擾
//-------------------------------------
Camera* Camera::Get_Main()
{
	return Camera::MainCamera;
}

//-------------------------------------
//	�ϊ��J�n
//-------------------------------------
bool Camera::Begin()
{
	if (MainCamera == NULL) return false;

	//------------------------------------
	//	�r���[�ϊ��s��
	//------------------------------------
	D3DXMATRIX mtxView;							//���C���r���[�ϊ��s��
	//------------------------------------
	//	�v���W�F�N�V�����ϊ��s��
	//------------------------------------
	D3DXMATRIX mtxProjection;		//�v���W�F�N�V�����ϊ��s��
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fov�͉�p�@�ϊ�
	D3DXMatrixLookAtLH(&mtxView, &MainCamera->position, &MainCamera->at, &MainCamera->up);	//�ϊ�
																							//�J�����̍��W��ύX�i�r���[�s��j
	System_GetDevice()->SetTransform(D3DTS_VIEW, &mtxView);
	System_GetDevice()->SetTransform(D3DTS_PROJECTION, &mtxProjection);
	System_GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);	//���C�e�B���O��OFF

	return true;
}

bool Camera::Begin(int num)
{
	D3DXMATRIX mtxView;							//���C���r���[�ϊ��s��
	D3DXMATRIX mtxProjection;		//�v���W�F�N�V�����ϊ��s��

	switch (num)
	{
	case 0:
		if (MainCamera == NULL) return false;
		D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fov�͉�p�@�ϊ�
		D3DXMatrixLookAtLH(&mtxView, &MainCamera->position, &MainCamera->at, &MainCamera->up);	//�ϊ�

		break;
	case 1:
		if (MainCamera1 == NULL) return false;
		D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fov�͉�p�@�ϊ�
		D3DXMatrixLookAtLH(&mtxView, &MainCamera1->position, &MainCamera1->at, &MainCamera1->up);	//�ϊ�

		break;
	case 2:
		if (MainCamera2 == NULL) return false;
		D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fov�͉�p�@�ϊ�
		D3DXMatrixLookAtLH(&mtxView, &MainCamera2->position, &MainCamera2->at, &MainCamera2->up);	//�ϊ�

		break;
	case 3:
		if (MainCamera3 == NULL) return false;
		D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fov�͉�p�@�ϊ�
		D3DXMatrixLookAtLH(&mtxView, &MainCamera3->position, &MainCamera3->at, &MainCamera3->up);	//�ϊ�

		break;
	default:
		break;
	}

	System_GetDevice()->SetTransform(D3DTS_VIEW, &mtxView);
	System_GetDevice()->SetTransform(D3DTS_PROJECTION, &mtxProjection);
	System_GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);	//���C�e�B���O��OFF

	return true;
}


