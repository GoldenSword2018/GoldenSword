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
#define WAIT_ANGLER_VEROCITY	(100.0f * 24.0f)	// �p���x�␳�l
#define WAIT_ROT_Y				(40)				// ���_���E��]���x�␳�l

#define DISTANCE_TO_AT			(5.0f)				// �����_�܂ł̋���
#define LIMIT_CAMERA_ELEVATION	(80.0f)				// �J�����̋�p�̌��E�l

//===============================================
//	�O���[�o���ϐ�
//===============================================
Player Player01(&Transform(D3DXVECTOR3(0.0f, 0.0f, -10.0f),
	D3DXVECTOR3(1.0f, 1.0f, 1.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DCOLOR_RGBA(255, 255, 255, 255)),
	&D3DXVECTOR3(0.0f, 0.0f, 1.0f)
);

//===============================================
//	������
//===============================================
void Player_Initialize(void)
{
	Player01.Camera.Set_Main();
	Bullet_Initialize();

	


}

//===============================================
//	�X�V
//===============================================
void Player_Update(void)
{
	Player01.Update();
	Bullet_Update();
}

//===============================================
//	�`��
//===============================================
void Player_Render(void)
{
	Player01.Render();
	Bullet_Render();
}

//===============================================
//	�I������
//===============================================
void Player_Finalize(void)
{

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
}

//===============================================
//	PlayerCamera �N���X
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Player::Player(Transform *pTransform, D3DXVECTOR3 *pForward) :GameObject(pTransform, &Texture()), ColShape(&pTransform->Position,1.0f)
{
	this->Forward = *pForward;
	float AngleY = 0.0f;
	float AngleX = 0.0f;
	float g_OldAngleX = 0.0f;
	D3DXVECTOR3 vecRight = this->Forward;
	D3DXMATRIX mtxRotationY;
	D3DXMatrixRotationY(&mtxRotationY, (-D3DX_PI / 2));
	D3DXVec3TransformNormal(&vecRight, &vecRight, &mtxRotationY);
	vecRight.y = 0.0f;
	D3DXVec3Normalize(&vecRight, &vecRight);
	this->Right = vecRight;
}

//-------------------------------------
//	�X�V
//-------------------------------------
void Player::Update()
{
	this->Camera.Update();
	SetPosition(this->Camera.position);
	SetForward(this->Camera.forward);

#if !defined(DISABLE_JOYCON) && !defined(DISABLE_GAMEPAD)
	Move();
	Rotation();

	if (JoyconInput_IsTrigger(JOYCON_BUTTON_INDEX_R_ZR))		// ZR�{�^�����͂ŃJ�������Z�b�g
	{
		ResetAngle();
	}
#endif

	if (JoyconInput_IsTrigger(JOYCON_BUTTON_INDEX_R_SR) || Keyboard_IsTrigger(DIK_F))		// SR�{�^�����͂�F�L�[�Ŕ���
	{
		Fire();
	}

}


//-------------------------------------
//	�`��
//-------------------------------------
void Player::Render()
{
	XModel_Render(GetMeshData(BulletIndex), CalWorldMtx());
}


//-------------------------------------
//	�ړ�
//-------------------------------------
void Player::Move()
{
	// �ړ�
	D3DXVECTOR3 vecDirMove(0.0f, 0.0f, 0.0f);													// �ړ������x�N�g�����[�N

	vecDirMove.x = (float)JoyconInput_GetLeftStickX();											// Joy-Con�̃X�e�B�b�N���͂��擾
	vecDirMove.z = -(float)JoyconInput_GetLeftStickY();											// Joy-Con�̃X�e�B�b�N���͂��擾
	D3DXVec3Normalize(&vecDirMove, &vecDirMove);												// vecDir�̒P�ʃx�N�g����

	vecDirMove *= PLAYER_MOVE_SPEED;															// �ړ����x��ݒ�

	this->transform.Position += this->Forward * vecDirMove.z + this->Right * vecDirMove.x;		// �v���C���[���W�ɉ��Z���Ĕ��f

}

//-------------------------------------
//	��]
//-------------------------------------
void Player::Rotation()
{
	// ���_�ύX
	this->AngleY += JoyconInput_GetAVYaw() / WAIT_ANGLER_VEROCITY;						// Joy-Con�̃��[�p���x���擾���ĉ��Z
	this->AngleX += JoyconInput_GetAVPitch() / WAIT_ANGLER_VEROCITY;					// Joy-Con�̃s�b�`�p���x���擾���ĉ��Z

	// ���_����]�ړ�
	D3DXVECTOR3 vecDirForward = this->Forward;											// ���_�����x�N�g�����[�N
	D3DXVECTOR3 vecDirRight = this->Right;												// ���_�E�����x�N�g�����[�N

	float RotY = 0.0f;																	// Y������̉�]�p���[�N

	// �v���C���[�̉�]�p�ɉ����ăJ������]���x����
	RotY = this->AngleY / WAIT_ROT_Y;

	D3DXMATRIX mtxRotationY;															// �x�N�g����]�p�}�g���N�X
	D3DXMatrixRotationY(&mtxRotationY, D3DXToRadian(RotY));								// ��]�p��Y������ɉ�]����}�g���N�X��ݒ�

	D3DXVec3TransformNormal(&vecDirForward, &vecDirForward, &mtxRotationY);				// ���_������Y������ɉ�]
	D3DXVec3TransformNormal(&vecDirRight, &vecDirRight, &mtxRotationY);					// ���_�E������Y������ɉ�]
	D3DXVec3Normalize(&vecDirForward, &vecDirForward);									// �P�ʃx�N�g����
	D3DXVec3Normalize(&vecDirRight, &vecDirRight);										// �P�ʃx�N�g����

	// ���_�㉺�����ړ�
	D3DXMATRIX mtxRotationAxis;															// �C�ӎ�����ɉ�]����p�̃}�g���N�X
	float RotAxis = (this->AngleX - g_OldAngleX) / 1.2f;								// ��]�p���v���C���[�̏㉺�p����ݒ�
	
	// �㉺�����̉�]�ɏ����݂���
	if (this->AngleX > LIMIT_CAMERA_ELEVATION)										
		RotAxis = LIMIT_CAMERA_ELEVATION;
	else if (this->AngleX < -LIMIT_CAMERA_ELEVATION)
		RotAxis = -LIMIT_CAMERA_ELEVATION;

	D3DXMatrixRotationAxis(&mtxRotationAxis, &vecDirRight, D3DXToRadian(RotAxis));		// �^�������x�N�g������i���Ȃ킿�㉺�����j�Ɏ��_��������]������}�g���N�X��ݒ�

	D3DXVec3TransformNormal(&vecDirForward, &vecDirForward, &mtxRotationAxis);			// ��]��K�p
	D3DXVec3Normalize(&vecDirForward, &vecDirForward);									// �P�ʃx�N�g����

	this->Forward = vecDirForward;														// �����������_�����x�N�g�����v���C���[���_�����ɓK�p
	this->Right = vecDirRight;															// �����������_�����x�N�g�����v���C���[���_�����ɓK�p

	this->Camera.position = this->transform.Position;									// �J�����ʒu���v���C���[���W�ɓ���
	this->Camera.forward = this->Forward;												// �J�����������v���C���[�̌����ɓ���
	this->Camera.right = this->Right;
	this->Camera.at = this->transform.Position + this->Forward * DISTANCE_TO_AT;		// �J���������_���v���C���[���W�ƃv���C���[���_��������Z�o

	g_OldAngleX = this->AngleX;

}

//-------------------------------------
//	���W�Z�b�g
//-------------------------------------
void Player::SetPosition(D3DXVECTOR3 Position)
{
	this->transform.Position = Position;
}

//-------------------------------------
//	�����Z�b�g
//-------------------------------------
void Player::SetForward(D3DXVECTOR3 Forward)
{
	this->Forward = Forward;
}

//-------------------------------------
//	���_�������Z�b�g
//-------------------------------------
void Player::ResetAngle()
{
	this->AngleX = 0.0f;
	this->AngleY = 0.0f;
}

//-------------------------------------
//	����
//-------------------------------------
void Player::Fire()
{
	Bullet_Create(this->transform.Position, this->Forward, Bullet::NORMAL);
}

//-------------------------------------
//	�����Ă�����������WorldMatrix���v�Z
//-------------------------------------
D3DXMATRIX Player::CalWorldMtx()
{
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxRotationY;
	D3DXMATRIX mtxRotationAxis;
	D3DXMATRIX mtxTranslation;

	D3DXVECTOR3 vecDirGround = this->Forward;
	vecDirGround.y = 0.0f;
	D3DXVec3Normalize(&vecDirGround, &vecDirGround);

	float RotY = atan2f(vecDirGround.x, vecDirGround.z);
	float RotAxis = acosf(D3DXVec3Dot(&this->Forward, &vecDirGround));
	D3DXMatrixRotationY(&mtxRotationY, RotY);
	D3DXMatrixRotationAxis(&mtxRotationAxis, &this->Right, RotAxis);

	D3DXMatrixTranslation(&mtxTranslation, this->transform.Position.x, this->transform.Position.y, this->transform.Position.z);
	mtxWorld = mtxRotationY * mtxRotationAxis * mtxTranslation;
	return mtxWorld;
}
