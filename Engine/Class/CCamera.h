//
//	CCamera.h
//		Author:HIROMASA IKEDA	DATE:2018/10/16
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CCAMERA_H
#define CCAMERA_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>

//Class
#include"CTransform.h"

//===============================================
//	�}�N����`	define
//===============================================


//================================================
//	�񋓌^		enum
//================================================


//===============================================
//	�}�N����`
//===============================================
#define CAMERA_POS (D3DXVECTOR3(0.0f, 5.0f, 5.0f))		//�J�����ʒu
#define CAMERA_AT (D3DXVECTOR3(0.0f, 0.0f, 0.0f))		//�J�����̒����_
#define CAMERA_UP (D3DXVECTOR3(0.0f,1.0f,0.0f))			//�J�����̏���� (�ǂ���������Ō���́H)
#define CAMERA_FORWARD (D3DXVECTOR3(0.0f,0.0f,-1.0f))	//�J�����O
#define CAMERA_INITIALSPEED (0.05f)						//�J�����̏������x

#define CAMERA_NEAR (0.1f)
#define CAMERA_WAR (100.0f)

#define SCREEN_ASPECT ((float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT)
#define CAMERA_ATDISTANCE (10.0f)
#define CAMERA_FOV (D3DXToRadian(60))

#define CAMERA_COUNT (4) //�J������

//================================================
//	�O���[�o���ϐ��@global
//================================================

//================================================
//	�N���X		class
//================================================

class ACamera
{
public:
	static ACamera* pMainCamera[CAMERA_COUNT];

public:
	static ACamera* Get_Main(int ScreenNum);
	static bool Begin(int ScreenNum);

public:
	D3DXMATRIX MtxView;			//View�s��
	D3DXVECTOR3 Position;
	D3DXVECTOR3 at;				//�����_
	D3DXVECTOR3 up;				//�J������
	D3DXVECTOR3 forward;		//�J�����O
	D3DXVECTOR3 right;			//�J�����E
	float atDistance;			//�����_�܂ł̋���
	float fov;					//��p

public:
	ACamera(D3DXVECTOR3 Position,D3DXVECTOR3 At,float atDistance,float fov);
	~ACamera();

public:
	void Set_Main(int ScreenNum);

public:
	virtual void Update() = 0;

};


//-------------------------------------
//	Camera�@�N���X
//-------------------------------------
class Camera :public ACamera
{
public:
	float Speed;				//�ړ����x

public:
	Camera() :Camera(CAMERA_POS, CAMERA_AT, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	Camera(D3DXVECTOR3 Position) : Camera(Position, CAMERA_AT, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	Camera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov);

public:
	virtual void Update() override;		//�X�V
};


#endif