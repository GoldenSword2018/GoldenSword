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

//===============================================
//	ACamera
//===============================================
ACamera* ACamera::pMainCamera[CAMERA_COUNT] = {NULL};

//-------------------------------------
//	Constructor
//-------------------------------------
ACamera::ACamera(D3DXVECTOR3 Position,D3DXVECTOR3 At,float atDistance,float fov)
{
	this->Position = Position;
	this->at = At;
	this->atDistance = atDistance;
	this->fov = fov;
	this->up = CAMERA_UP;
}

//-------------------------------------
//	Destructor
//-------------------------------------
ACamera::~ACamera()
{
	
}

//-------------------------------------
//	Get_Main
//-------------------------------------
ACamera* ACamera::Get_Main(int ScreenNum)
{
	return pMainCamera[ScreenNum];
}

//-------------------------------------
//	Begin
//-------------------------------------
bool ACamera::Begin(int ScreenNum)
{
	if (pMainCamera[ScreenNum] == NULL) return false;
	
	D3DXMATRIX mtxProjection;		//�v���W�F�N�V�����ϊ��s��
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fov�͉�p�@�ϊ�
	D3DXMatrixLookAtLH(&pMainCamera[ScreenNum]->MtxView, &pMainCamera[ScreenNum]->Position, &pMainCamera[ScreenNum]->at, &pMainCamera[ScreenNum]->up);	//�ϊ�
																							//�J�����̍��W��ύX�i�r���[�s��j
	System_GetDevice()->SetTransform(D3DTS_VIEW, &pMainCamera[ScreenNum]->MtxView);
	System_GetDevice()->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	return true;
}

//-------------------------------------
//	Set_Main(int ScreenNum)
//-------------------------------------
void ACamera::Set_Main(int ScreenNum)
{
	pMainCamera[ScreenNum] = this;
}

//-------------------------------------
//	Update()
//-------------------------------------	
void ACamera::Update()
{

}

//===============================================
//	Camera	�N���X
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Camera::Camera(D3DXVECTOR3 Position, D3DXVECTOR3 At,float AtDistance,float fov)
:
	ACamera(Position,At,AtDistance,fov)
{
	this->Speed = CAMERA_INITIALSPEED;

	//�O

	this->forward = CAMERA_FORWARD;
	D3DXVec3Normalize(&this->forward, &this->forward);

	//�E
	D3DXVec3Cross(&this->right, &this->forward, &this->up);
	D3DXVec3Normalize(&this->right, &this->right);
}


//-------------------------------------
//	�X�V
//-------------------------------------
void Camera::Update()
{
	//------------------------------------
	//	�J����
	//------------------------------------
	this->at = this->forward * this->atDistance + this->Position;

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

		this->Position = at - this->forward * this->atDistance;
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
			this->Position += front * this->Speed;
		}

		if (Keyboard_IsPress(DIK_S))
		{
			this->Position -= front * this->Speed;
		}

		if (Keyboard_IsPress(DIK_A))
		{
			this->Position += right * this->Speed;
		}

		if (Keyboard_IsPress(DIK_D))
		{
			this->Position -= right * this->Speed;
		}

		if (Keyboard_IsPress(DIK_Q))
		{
			this->Position.y -= this->Speed;
		}

		if (Keyboard_IsPress(DIK_E))
		{
			this->Position.y += this->Speed;
		}
		this->Position += this->forward * Mouse_IsAccelerationZ() *0.01f;
	}

	return;
}

