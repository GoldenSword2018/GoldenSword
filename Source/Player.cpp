//
//	Player.cpp
//		Author:YU NISHIMAKI	DATE:2018/10/13
//===============================================
//	�ύX�� Changed By
//		Name:HIROMASA IEKDA	DATE:2018/11/13
//
//-----------------------------------------------
#include<d3dx9.h>
#include"common.h"
#include"input.h"
#include"joycon_input.h"
#include"Debug_font.h"
#include"Player.h"

#include"Bullet.h"
#include"CGameObject.h"
//Class
#include "CCollisionChecker.h"
// Debug�p
#include "Debug_Collision.h"

//===============================================
//	�O���[�o���ϐ�
//===============================================
Player Player01(
	&Transform
	(
		D3DXVECTOR3(0.0f, 0.0f, -10.0f),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 255, 255, 255)
	),
	&D3DXVECTOR3(0.0f, 0.0f, 1.0f)
);

//===============================================
//	������
//===============================================
void Player_Initialize(void)
{
	Player01.Camera.Set_Main(0);
	Bullet_Initialize();
	TmpCollisionChecker::GetInstance()->RegisterCollision_Player( &Player01 );
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
	TmpCollisionChecker::GetInstance()->DeregisterCollision_Player( &Player01 );
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
	this->atDistance = 3.0f;
	Camera::Update();
}

//===============================================
//	Player �N���X
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Player::Player(Transform *pTransform, D3DXVECTOR3 *pForward)
	:
	GameObject(pTransform, &Texture()),
	ColShape
	(
		&transform.Position,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&D3DXVECTOR3(1.0f, 5.0f, 1.0f)
	),
	//�R�A
	Head_Screw(&Transform(D3DCOLOR_RGBA(255,0,0,255))),
	Body_Screw(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	LeftArm_Screw(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	RightArm_Screw(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	LeftLeg_Screw(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	RightLeg_Screw(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),

	//�A�[�}�[
	Head_Armor01(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	Body_Armor01(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	LeftArm_Armor01(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	RightArm_Armor01(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	LeftLeg_Armor01(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	RightLeg_Armor01(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255)))
{
	this->Forward = *pForward;
	this->AngleY = 0.0f;
	this->AngleX = 0.0f;
	this->RotY = 0.0f;
	this->RotAxis = 0.0f;
	this->g_OldAngleX = 0.0f;
	D3DXVECTOR3 vecRight = this->Forward;
	D3DXMATRIX mtxRotationY;
	D3DXMatrixRotationY(&mtxRotationY, (-D3DX_PI / 2));
	D3DXVec3TransformNormal(&vecRight, &vecRight, &mtxRotationY);
	vecRight.y = 0.0f;
	D3DXVec3Normalize(&vecRight, &vecRight);
	this->Right = vecRight;

	this->Set_Parts();
}

//-------------------------------------
//	�e���ʂ�ݒ�
//-------------------------------------
void Player::Set_Parts()
{
	//�v���C���[�Ɛe�q�֌W�����
	Head.Set_Parent(this);
	Body.Set_Parent(this);
	LeftArm.Set_Parent(this);
	RightArm.Set_Parent(this);
	LeftLeg.Set_Parent(this);
	RightLeg.Set_Parent(this);

	Head_Screw.Set_Parent(this);
	Body_Screw.Set_Parent(this);
	LeftArm_Screw.Set_Parent(this);
	RightArm_Screw.Set_Parent(this);
	LeftLeg_Screw.Set_Parent(this);
	RightLeg_Screw.Set_Parent(this);

	//
	Head.transform.Position = D3DXVECTOR3(0.0f,1.4f,0.0f);
	Head.transform.Scale = D3DXVECTOR3(0.8f,0.8f,0.8f);

	//
	Body.transform.Position = D3DXVECTOR3(0.0f,-0.0f,0.0f);
	Body.transform.Scale = D3DXVECTOR3(1.0f,2.0f,1.0f);

	//
	LeftArm.transform.Position = D3DXVECTOR3(-0.9f,-0.2f,0.0f);
	LeftArm.transform.Scale = D3DXVECTOR3(0.5f,2.0f,0.5f);

	//
	RightArm.transform.Position = D3DXVECTOR3(0.9f,-0.2f,0.0f);
	RightArm.transform.Scale = D3DXVECTOR3(0.5f,2.0f,0.5f);

	//
	LeftLeg.transform.Position = D3DXVECTOR3(-0.2f,-2.0f,0.0f);
	LeftLeg.transform.Scale = D3DXVECTOR3(0.5f,2.0f,0.5f);

	//
	RightLeg.transform.Position = D3DXVECTOR3(0.2f,-2.0f,0.0f);
	RightLeg.transform.Scale = D3DXVECTOR3(0.5f,2.0f,0.5f);

	//�R�A�̓o�^
	Head_Screw.SetBody(&Head);
	Body_Screw.SetBody(&Body);
	LeftArm_Screw.SetBody(&LeftArm);
	RightArm_Screw.SetBody(&RightArm);
	LeftLeg_Screw.SetBody(&LeftLeg);
	RightLeg_Screw.SetBody(&RightLeg);

	//�A�[�}�[�̓o�^
	Head_Screw.SetArmor(&Head_Armor01);
	
	Body_Screw.SetArmor(&Body_Armor01);

	LeftArm_Screw.SetArmor(&LeftArm_Armor01);

	RightArm_Screw.SetArmor(&RightArm_Armor01);

	LeftLeg_Screw.SetArmor(&LeftLeg_Armor01);

	RightLeg_Screw.SetArmor(&RightLeg_Armor01);
}

//-------------------------------------
//	�X�V
//-------------------------------------
void Player::Update()
{
	this->Camera.Position = this->transform.Position;
	this->Camera.Update();
	this->transform.Set_WorldTransform();				//WorldPosition���Z�o
	this->transform.WorldPosition.y = 0.0f;				//�������Œ�

	
	SetForward(this->Camera.forward);
	this->transform.Rotation.y = this->RotY;

	D3DXVECTOR3 face = this->Forward;
	face.y = 0.0f;
	Head_Screw.face = face;
	Body_Screw.face = face;
	LeftArm_Screw.face = face;
	RightArm_Screw.face = face;
	LeftLeg_Screw.face = face;
	RightLeg_Screw.face = face;

	Head_Screw.transform.Rotation.y = AngleY;
	Body_Screw.transform.Rotation.y = AngleY;
	LeftArm_Screw.transform.Rotation.y = AngleY;


	CalWorldMtx();

	if (Keyboard_IsPress(DIK_W))
	{
		this->transform.Position += this->transform.forward * PLAYER_MOVE_SPEED;
	}

	if(Keyboard_IsPress(DIK_S))
	{
		this->transform.Position -= this->transform.forward * PLAYER_MOVE_SPEED;
	}

	if (Keyboard_IsPress(DIK_A))
	{
		this->transform.Position -= this->transform.right * PLAYER_MOVE_SPEED;
	}

	if (Keyboard_IsPress(DIK_D))
	{
		this->transform.Position += this->transform.right * PLAYER_MOVE_SPEED;
	}



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

	SetPosition(this->transform.Position);
	this->Camera.at = this->transform.WorldPosition;	//�����_���v���C���[��
	this->Camera.at.y += 2.0f;
	this->Camera.Position = this->Camera.at - this->Forward * this->Camera.atDistance;		//�J�����ʒu�����߂�

}


//-------------------------------------
//	�`��
//-------------------------------------
void Player::Render()
{
	//XModel_Render( GetMeshData( BulletIndex ), CalWorldMtx() );
	ColShape.DebugDraw();
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

	this->Camera.Position = this->transform.Position;									// �J�����ʒu���v���C���[���W�ɓ���
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
	//�킩��˂��I�I�I
	D3DXVECTOR3 look = this->Forward;
	Bullet_Create(this->transform.Position, look, Bullet::NORMAL);
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

	RotY = atan2f(vecDirGround.x, vecDirGround.z);
	RotAxis = acosf(D3DXVec3Dot(&this->Forward, &vecDirGround));
	D3DXMatrixRotationY(&mtxRotationY, RotY);
	D3DXMatrixRotationAxis(&mtxRotationAxis, &this->Right, RotAxis);

	D3DXMatrixTranslation(&mtxTranslation, this->transform.Position.x, this->transform.Position.y, this->transform.Position.z);
	mtxWorld = mtxRotationY * mtxRotationAxis * mtxTranslation;

	return mtxWorld;
}
