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

//-------------------------------------
//	Camera�@�N���X
//-------------------------------------
class Camera
{
public:
	static Camera* Get_Main();
	static bool Begin();		//�`��J�n

private:
	static Camera* MainCamera;					//���C���J����
	//static Camera* SubCamera;					//�T�u�J����

public:
	D3DXVECTOR3 position;		//�ʒu
	float Speed;				//�ړ����x

	D3DXVECTOR3 at;				//�����_
	D3DXVECTOR3 up;				//�J������
	D3DXVECTOR3 forward;		//�J�����O
	D3DXVECTOR3 right;			//�J�����E
	float atDistance;			//�����_�܂ł̋���
	float fov;					//��p

public:
	Camera() :Camera(CAMERA_POS, CAMERA_AT, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	Camera(D3DXVECTOR3 Position) : Camera(Position, CAMERA_AT, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	Camera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov);

public:
	void Set_Main();			//���C���J�����ɐݒ�
	//void Set_Sub();				//�T�u�J�����ɐݒ�

public:
	virtual void Initialize();	//������
	virtual void Update();		//�X�V
};


#endif