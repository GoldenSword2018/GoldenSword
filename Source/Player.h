//
//	Player.h
//		Author:YU NISHIMAKI	DATE:2018/10/13
//===============================================
#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include"common.h"
#include<d3dx9.h>

//Class
#include"CGameObject.h"
#include"CCamera.h"
#include"CCollisionShape.h"
#include"CBodyObject.h"
#include"CCoreObject.h"
#include"CArmorObject.h"

//===============================================
//	�}�N����`
//===============================================
#define PLAYER_MOVE_SPEED		(0.1f)				// �v���C���[�ړ����x
#define WAIT_ANGLER_VEROCITY	(100.0f * 24.0f)	// �p���x�␳�l
#define WAIT_ROT_Y				(40)				// ���_���E��]���x�␳�l

#define DISTANCE_TO_AT			(5.0f)				// �����_�܂ł̋���
#define LIMIT_CAMERA_ELEVATION	(80.0f)				// �J�����̋�p�̌��E�l

//===============================================
//	Player �\����
//===============================================
typedef struct PLAYER_tag
{
	D3DXVECTOR3 Position;				// �v���C���[���W
	D3DXVECTOR3 Verocity;				// ���x
	D3DXVECTOR3 vecDir;					// �����Ă������
	float AngleY;						// Y������̉�]�p�i���_�̍��E�����p�x�j
	float AngleX;						// X������̉�]�p�i���_�̋p��p�j
}PLAYER;

//===============================================
//	�N���X
//===============================================
class Player;
class PlayerCamera;
//-------------------------------------
//	�v���C���[�J����
//-------------------------------------
class PlayerCamera:public Camera
{
public:
	void Initialize();
	void Update();
};

//-------------------------------------
//	�v���C���[
//-------------------------------------
class Player:public GameObject
{
public:

private:
	D3DXVECTOR3 Forward;
	D3DXVECTOR3 Right;

	float AngleY;						// Y������̉�]�p�i���_�̍��E�����p�x�j
	float AngleX;						// X������̉�]�p�i���_�̋p��p�j
	float g_OldAngleX;
public:
	ShapeOBB ColShape;

	float RotY;
	float RotAxis;
	
public:
	//�e����
	BodyObject Head;
	BodyObject Body;
	BodyObject LeftArm;
	BodyObject RightArm;
	BodyObject LeftLeg;
	BodyObject RightLeg;

public:
	//�R�A
	CoreObject Head_Screw;
	CoreObject Body_Screw;
	CoreObject LeftArm_Screw;
	CoreObject RightArm_Screw;
	CoreObject LeftLeg_Screw;
	CoreObject RightLeg_Screw;

public:
	//�A�[�}�[
	ArmorObject Head_Armor01;

	ArmorObject Body_Armor01;

	ArmorObject LeftArm_Armor01;

	ArmorObject RightArm_Armor01;

	ArmorObject LeftLeg_Armor01;

	ArmorObject RightLeg_Armor01;

public:
	Player(Transform* pTransform, D3DXVECTOR3* pForward);

private:
	void Set_Parts();		//���ʂ�ݒ�

public:
	PlayerCamera Camera;
	void Update();
	void Render();
	void Move();
	void Rotation();
	void SetPosition(D3DXVECTOR3 Position);
	void SetForward(D3DXVECTOR3 Forward);
	void ResetAngle();
	void Fire();
	D3DXMATRIX CalWorldMtx();

};

//===============================================
//	�֐�
//===============================================
void Player_Initialize(void);
void Player_Update(void);
void Player_Render(void);
void Player_Finalize(void);

void Player_ResetAngle(void);
const PLAYER *Player_GetPlayer(void);

#endif // !PLAYER_H