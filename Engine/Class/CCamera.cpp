//
//	CCamera.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/17
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include<d3dx9.h>
#include"common.h"
#include"input.h"

//class
#include"CCamera.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================
Camera* Camera::MainCamera = NULL;
Camera* Camera::MainCamera1 = NULL;
Camera* Camera::MainCamera2 = NULL;
Camera* Camera::MainCamera3 = NULL;

//===============================================
//	カメラ		class
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Camera::Camera(D3DXVECTOR3 Position, D3DXVECTOR3 At,float AtDistance,float fov)
{
	this->position = Position;
	this->at = At;
	this->up = CAMERA_UP;
	this->atDistance = AtDistance;
	this->fov = fov;
	this->Speed = CAMERA_INITIALSPEED;

	//前

	this->forward = CAMERA_FORWARD;
	D3DXVec3Normalize(&this->forward, &this->forward);

	//右
	D3DXVec3Cross(&this->right, &this->forward, &this->up);
	D3DXVec3Normalize(&this->right, &this->right);
}

//-------------------------------------
//	初期化
//-------------------------------------
void Camera::Initialize()
{
	return;
}

//-------------------------------------
//	更新
//-------------------------------------
void Camera::Update()
{
	//------------------------------------
	//	カメラ
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
			D3DXVec3TransformNormal(&this->forward, &this->forward, &mtxRotation);	//ベクトル座標変換
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
			D3DXVec3TransformNormal(&this->forward, &this->forward, &mtxRotation);	//ベクトル座標変換
			D3DXVec3TransformNormal(&this->right, &this->right, &mtxRotation);
			D3DXVec3Cross(&this->up, &this->right, &this->forward);

			D3DXMatrixIdentity(&mtxRotation);
			D3DXMatrixRotationAxis(&mtxRotation, &this->right, Mouse_IsAccelerationY() * -0.001f);
			D3DXVec3TransformNormal(&this->forward, &this->forward, &mtxRotation);	//ベクトル座標変換
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
//	メインカメラに設定
//-------------------------------------
void Camera::Set_Main()
{
	this->MainCamera = this;
}

//別々登録
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
//	サブカメラに設定
//-------------------------------------
//void Camera::Set_Sub()
//{
//	this->SubCamera = this;
//}

//-------------------------------------
//	メインカメラ取得
//-------------------------------------
Camera* Camera::Get_Main()
{
	return Camera::MainCamera;
}

//-------------------------------------
//	変換開始
//-------------------------------------
bool Camera::Begin()
{
	if (MainCamera == NULL) return false;

	//------------------------------------
	//	ビュー変換行列
	//------------------------------------
	D3DXMATRIX mtxView;							//メインビュー変換行列
	//------------------------------------
	//	プロジェクション変換行列
	//------------------------------------
	D3DXMATRIX mtxProjection;		//プロジェクション変換行列
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fovは画角　変換
	D3DXMatrixLookAtLH(&mtxView, &MainCamera->position, &MainCamera->at, &MainCamera->up);	//変換
																							//カメラの座標を変更（ビュー行列）
	System_GetDevice()->SetTransform(D3DTS_VIEW, &mtxView);
	System_GetDevice()->SetTransform(D3DTS_PROJECTION, &mtxProjection);
	System_GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);	//ライティングをOFF

	return true;
}

bool Camera::Begin(int num)
{
	D3DXMATRIX mtxView;							//メインビュー変換行列
	D3DXMATRIX mtxProjection;		//プロジェクション変換行列

	switch (num)
	{
	case 0:
		if (MainCamera == NULL) return false;
		D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fovは画角　変換
		D3DXMatrixLookAtLH(&mtxView, &MainCamera->position, &MainCamera->at, &MainCamera->up);	//変換

		break;
	case 1:
		if (MainCamera1 == NULL) return false;
		D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fovは画角　変換
		D3DXMatrixLookAtLH(&mtxView, &MainCamera1->position, &MainCamera1->at, &MainCamera1->up);	//変換

		break;
	case 2:
		if (MainCamera2 == NULL) return false;
		D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fovは画角　変換
		D3DXMatrixLookAtLH(&mtxView, &MainCamera2->position, &MainCamera2->at, &MainCamera2->up);	//変換

		break;
	case 3:
		if (MainCamera3 == NULL) return false;
		D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fovは画角　変換
		D3DXMatrixLookAtLH(&mtxView, &MainCamera3->position, &MainCamera3->at, &MainCamera3->up);	//変換

		break;
	default:
		break;
	}

	System_GetDevice()->SetTransform(D3DTS_VIEW, &mtxView);
	System_GetDevice()->SetTransform(D3DTS_PROJECTION, &mtxProjection);
	System_GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);	//ライティングをOFF

	return true;
}


