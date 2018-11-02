//
//	Player.cpp
//		Author:YU NISHIMAKI	DATE:2018/10/13
//===============================================
//	�ύX�� Changed By
//		Name:HIROMASA IEKDA	DATE:2018/10/17
//
//-----------------------------------------------
#include<d3dx9.h>
#include"common.h"
#include"input.h"
#include"joycon_input.h"
#include"Debug_font.h"
#include"Player.h"

#include"Bullet.h"
//Class

//===============================================
//	�}�N����`
//===============================================
#define PLAYER_MOVE_SPEED		(0.1f)				// �v���C���[�ړ����x
#define PLAYER_ROT_FAST_Y		(6.0f)				// �v���C���[��Y������̎��_�ړ����x(����)
#define PLAYER_ROT_SLOW_Y		(2.0f)				// �v���C���[��Y������̎��_�ړ����x(�ᑬ)

#define DISTANCE_TO_AT			(5.0f)				// �����_�܂ł̋���
#define LIMIT_CAMERA_ELEVATION	(80.0f)				// �J�����̍s��p�̌��E�l

//===============================================
//	�O���[�o���ϐ�
//===============================================
static PLAYER g_Player;
static PlayerCamera g_PlayerCamera;
static float g_OldAngleX;

//===============================================
//	������
//===============================================
void Player_Initialize(void)
{
	g_Player.Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// �v���C���[���W�x�N�g��
	g_Player.Verocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �v���C���[���x�x�N�g��
	g_Player.vecDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);		// �v���C���[���_�����x�N�g��
	g_Player.AngleY = 0.0f;									// �R���g���[�����E��]�p	
	g_Player.AngleX = 0.0f;									// �R���g���[���㉺��]�p

	g_OldAngleX = 0.0f;

	g_PlayerCamera.Set_Main();
	Bullet_Initialize();
}

//===============================================
//	�X�V
//===============================================
void Player_Update(void)
{
	g_PlayerCamera.Update();

	if (JoyconInput_IsTrigger(JOYCON_BUTTON_INDEX_R_SR) || Keyboard_IsTrigger(DIK_F))
	{
		Bullet_Create(g_Player.Position, g_Player.vecDir,BULLET_NORMAL);
	}

	Bullet_Update();
}

//===============================================
//	�`��
//===============================================
void Player_Render(void)
{
	Bullet_Render();
	DebugFont_Draw(500, 0, "���E�p�x%.3f\n�㉺�p�x%.3f", g_Player.AngleY, g_Player.AngleX);
}

//===============================================
//	�I������
//===============================================
void Player_Finalize(void)
{

}

//===============================================
//	���_������
//===============================================
void Player_ResetAngle(void)
{
	g_Player.AngleY = 0.0f;
	g_Player.AngleX = 0.0f;	
}

//===============================================
//	���擾
//===============================================
const PLAYER *Player_GetPlayer(void)
{
	return &g_Player;
}

//===============================================
//	PlayerCamera �N���X
//===============================================

//-------------------------------------
//	������
//-------------------------------------
void PlayerCamera::Initialize()
{

}

//-------------------------------------
//	�X�V
//-------------------------------------
void PlayerCamera::Update()
{
	Camera::Update();
	g_Player.Position = this->position;
	g_Player.vecDir = this->forward;

#if !defined(DISABLE_JOYCON) && !defined(DISABLE_GAMEPAD)
	g_Player.Position = this->position;
	g_Player.vecDir = this->forward;

	// �ړ�
	D3DXVECTOR3 vecDirMove(0.0f, 0.0f, 0.0f);													// �ړ������x�N�g�����[�N

	vecDirMove.x =(float)JoyconInput_GetLeftStickX();											// Joy-Con�̃X�e�B�b�N���͂��擾
	vecDirMove.z =-(float)JoyconInput_GetLeftStickY();											// Joy-Con�̃X�e�B�b�N���͂��擾
	D3DXVec3Normalize(&vecDirMove, &vecDirMove);												// vecDir�̒P�ʃx�N�g����

	D3DXVECTOR3 vecDirForword = g_Player.vecDir;												// �v���C���[�̈ړ������擾
	vecDirForword.y = 0.0f;																		// Y������0�ɂ���XY���ʂɓ���
	D3DXVec3Normalize(&vecDirForword, &vecDirForword);											// �P�ʃx�N�g����

	D3DXMATRIX mtxRotationMove;																	// �ړ�������]�p�}�g���N�X
	D3DXMatrixRotationY(&mtxRotationMove, atan2f(vecDirForword.x, vecDirForword.z));			// �v���C���[�̈ړ������ɍ��킹�ĉ�]�p��ݒ�
	D3DXVec3TransformNormal(&vecDirMove, &vecDirMove, &mtxRotationMove);						// ��]��K�p

	vecDirMove *= PLAYER_MOVE_SPEED;															// �ړ����x��ݒ�

	g_Player.Position += vecDirMove;															// �v���C���[���W�ɉ��Z���Ĕ��f


	// ���_�ύX
	g_Player.AngleY += JoyconInput_GetAVYaw() / 100.0f / 24;									// Joy-Con�̃��[�p���x���擾���ĉ��Z
	g_Player.AngleX += JoyconInput_GetAVPitch() / 100.0f / 24;									// Joy-Con�̃s�b�`�p���x���擾���ĉ��Z

	if (JoyconInput_IsTrigger(JOYCON_BUTTON_INDEX_R_ZR))										// ZR�{�^�����͂ŃJ�������Z�b�g
	{
		Player_ResetAngle();
	}

	// ���_����]�ړ�
	D3DXVECTOR3 vecDir = g_Player.vecDir;														// ���_�����x�N�g�����[�N
//	vecDir.y = 0.0f;																			// Y������0��
//	D3DXVec3Normalize(&vecDir, &vecDir);														// �P�ʃx�N�g����

	float RotY = 0.0f;																			// Y������̉�]�p���[�N

																								// �v���C���[�̉�]�p�ɉ����ăJ������]���x����
	RotY = g_Player.AngleY / 40;

	D3DXMATRIX mtxRotationY;																	// �x�N�g����]�p�}�g���N�X
	D3DXMatrixRotationY(&mtxRotationY, D3DXToRadian(RotY));										// ��]�p��Y������ɉ�]����}�g���N�X��ݒ�

	D3DXVec3TransformNormal(&vecDir, &vecDir, &mtxRotationY);									// ���_������Y������ɉ�]
	D3DXVec3Normalize(&vecDir, &vecDir);														// �P�ʃx�N�g����


	// ���_�㉺�����ړ�
	D3DXVECTOR3 VecDirSide(0.0f, 0.0f, 0.0f);													// �^�������x�N�g�����[�N�i��]���p�j
	VecDirSide.x = -vecDir.z;																	// Y����0�Ő����ȃx�N�g����ݒ�
	VecDirSide.z = vecDir.x;
	D3DXVec3Normalize(&VecDirSide, &VecDirSide);												// �P�ʃx�N�g����
	D3DXMATRIX mtxRotationAxis;																	// �C�ӎ�����ɉ�]����p�̃}�g���N�X
	float RotAxis = (g_Player.AngleX - g_OldAngleX)/ 1.2f;														// ��]�p���v���C���[�̏㉺�p����ݒ�
	if (g_Player.AngleX > LIMIT_CAMERA_ELEVATION)												// �㉺�����̉�]�ɏ����݂���
		RotAxis = LIMIT_CAMERA_ELEVATION;
	else if (g_Player.AngleX < -LIMIT_CAMERA_ELEVATION)
		RotAxis = -LIMIT_CAMERA_ELEVATION;

	D3DXMatrixRotationAxis(&mtxRotationAxis, &VecDirSide, D3DXToRadian(RotAxis));				// �^�������x�N�g������i���Ȃ킿�㉺�����j�Ɏ��_��������]������}�g���N�X��ݒ�

	D3DXVec3TransformNormal(&vecDir, &vecDir, &mtxRotationAxis);								// ��]��K�p
	D3DXVec3Normalize(&vecDir, &vecDir);														// �P�ʃx�N�g����

	g_Player.vecDir = vecDir;																	// �����������_�����x�N�g�����v���C���[���_�����ɓK�p

	this->position = g_Player.Position;															// �J�����ʒu���v���C���[���W�ɓ���
	this->forward = g_Player.vecDir;															// �J�����������v���C���[�̌����ɓ���
	this->at = this->position + this->forward * DISTANCE_TO_AT;									// �J���������_���v���C���[���W�ƃv���C���[���_��������Z�o
	
	D3DXVECTOR3 vecDirSide(0.0f, 0.0f, 0.0f);													// �^�������x�N�g�����[�N
	vecDirSide.x = this->forward.z;																// ���_�����ɐ����ȃx�N�g���𐶐�
	vecDirSide.z = -(this->forward.x);															// ����
	D3DXVec3Normalize(&vecDirSide, &vecDirSide);												// �P�ʃx�N�g����
	this->right = vecDirSide;
	D3DXVec3Cross(&this->up, &this->forward, &this->right);										// �O�ςɂ�莋�_�����A�^�������x�N�g���̗����ɐ����ȃx�N�g���𐶐��iCameraUp�j
	D3DXVec3Normalize(&this->up, &this->up);													// �P�ʃx�N�g����

	g_OldAngleX = g_Player.AngleX;
#else
	//Camera::Update();
#endif
}