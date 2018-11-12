//
//	CTeamProt.cpp
//		Author:HIROMASA IEKDA	DATE:2018/10/15
//===============================================

#include<d3dx9.h>
#include"common.h"
#include"CTeamProt.h"
#include"input.h"

//Gometry
#include"Cube.h"
#include"Grid.h"

//Class
#include"CArmorObject.h"
#include"CCoreObject.h"
#include"CBodyObject.h"
#include"CCamera.h"

// Test
#include "Debug_Collision.h"
//===============================================
//	�O���[�o���ϐ�
//===============================================
static Camera g_Camera;	
static float movez=-5.0f;

// 
class tmp : public GameObject
{
public:
	ShapeOBB ColShape;
public:
	tmp( Transform* pTransform, Texture* pTexture )
		:GameObject( pTransform, pTexture ),
		ColShape( &transform.Position, &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), &D3DXVECTOR3( 10.0f, 10.0f, 10.0f ) )
	{

	}
public:
	void Hit() {}
	void Render()
	{
		DebugCollisionModule::Cuboid_BatchBegin();
		DebugCollisionModule::BatchDrawCuboid( &ColShape );
		DebugCollisionModule::Cuboid_BatchRun();
	}
};
static tmp Test
(
	&Transform
	( 
		D3DXVECTOR3( 0.0f, 0.0f, -3.0f ),
		D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f )
	),
	&Texture
	(
		EroTexture1,
		{ 0,0 },
		{ 0,0 }
	)
	
);
//����
static BodyObject Body_07(
	&Transform
	(
		D3DXVECTOR3(0.0f, 0.0f + 3.0f, movez-1.0f),
		D3DXVECTOR3(8.0f, 8.0f, 0.1f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 255, 255, 255)
	),
	&Texture
	(
		EroTexture1,
		{ 0,0 },
		{ 0,0 }
	)
);
//�A�[�}�[
static ArmorObject Armor_7_11(
	&Transform
	(
		D3DXVECTOR3(-3.0f, 3.0f+3.0f, 0.0f+movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_12(
	&Transform
	(
		D3DXVECTOR3(-1.0f, 3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_13(
	&Transform
	(
		D3DXVECTOR3(1.0f, 3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_14(
	&Transform
	(
		D3DXVECTOR3(3.0f, 3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_21(
	&Transform
	(
		D3DXVECTOR3(-3.0f, 1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_22(
	&Transform
	(
		D3DXVECTOR3(-1.0f, 1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_23(
	&Transform
	(
		D3DXVECTOR3(1.0f, 1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_24(
	&Transform
	(
		D3DXVECTOR3(3.0f, 1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_31(
	&Transform
	(
		D3DXVECTOR3(-3.0f, -1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_32(
	&Transform
	(
		D3DXVECTOR3(-1.0f, -1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_33(
	&Transform
	(
		D3DXVECTOR3(1.0f, -1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_34(
	&Transform
	(
		D3DXVECTOR3(3.0f, -1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_41(
	&Transform
	(
		D3DXVECTOR3(-3.0f, -3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_42(
	&Transform
	(
		D3DXVECTOR3(-1.0f, -3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_43(
	&Transform
	(
		D3DXVECTOR3(1.0f, -3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	),
	RADIALLY
);
//�A�[�}�[
static ArmorObject Armor_7_44(
	&Transform
	(
		D3DXVECTOR3(3.0f, -3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	RADIALLY
);

//�l�W
static CoreObject Screw_07
(
	&Transform
	(
		D3DXVECTOR3(0.0f,3.0f, 1.0f + movez),
		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(100, 100, 100, 255)
	),
	&Texture
	(
		EroTexture1,
		{ 0,0 },
		{ 0,0 }
	)
);

//����
static BodyObject Body_08(
	&Transform
	(
		D3DXVECTOR3(0.0f, 0.0f + 3.0f, 5.0f*movez-1.0f),
		D3DXVECTOR3(8.0f, 8.0f, 0.1f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 255, 255, 255)
	),
	&Texture
	(
		EroTexture2,
		{ 0,0 },
		{ 0,0 }
	)
);
//�A�[�}�[
static ArmorObject Armor_8_11(
	&Transform
	(
		D3DXVECTOR3(-3.0f, 3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_12(
	&Transform
	(
		D3DXVECTOR3(-1.0f, 3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_13(
	&Transform
	(
		D3DXVECTOR3(1.0f, 3.0f + 3.0f, 0.0f + 5* movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_14(
	&Transform
	(
		D3DXVECTOR3(3.0f, 3.0f + 3.0f, 0.0f+ 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_21(
	&Transform
	(
		D3DXVECTOR3(-3.0f, 1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_22(
	&Transform
	(
		D3DXVECTOR3(-1.0f, 1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_23(
	&Transform
	(
		D3DXVECTOR3(1.0f, 1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_24(
	&Transform
	(
		D3DXVECTOR3(3.0f, 1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_31(
	&Transform
	(
		D3DXVECTOR3(-3.0f, -1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_32(
	&Transform
	(
		D3DXVECTOR3(-1.0f, -1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_33(
	&Transform
	(
		D3DXVECTOR3(1.0f, -1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_34(
	&Transform
	(
		D3DXVECTOR3(3.0f, -1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_41(
	&Transform
	(
		D3DXVECTOR3(-3.0f, -3.0f + 3.0f, 0.0f+5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_42(
	&Transform
	(
		D3DXVECTOR3(-1.0f, -3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_43(
	&Transform
	(
		D3DXVECTOR3(1.0f, -3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	),
	FALL
);
//�A�[�}�[
static ArmorObject Armor_8_44(
	&Transform
	(
		D3DXVECTOR3(3.0f, -3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	FALL
);

//�l�W
static CoreObject Screw_08
(
	&Transform
	(
		D3DXVECTOR3(0.0f, 3.0f, 1.0f + 5 * movez),
		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(100, 100, 100, 255)
	),
	&Texture
	(
		TEXTURE_NONE,
		{ 0,0 },
		{ 0,0 }
	)
);
//===============================================
//	�֐�
//===============================================

//-------------------------------------
//	������
//-------------------------------------
void CTeamProt_Initialize()
{

	Screw_07.Set_JudgeType(CoreObject::CORE_JUDGE_TYPE_1);

	Screw_07.Set(&Armor_7_11, &Body_07);//�l�W�ɓ��̂ƃA�[�}�[��ݒ�
	Screw_07.Set(&Armor_7_12);			//�l�W�̓��̂͌��܂��Ă���̂ŁA�A�[�}�[�����ݒ�
	Screw_07.Set(&Armor_7_13);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_14);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_21);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_22);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_23);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_24);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_31);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_32);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_33);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_34);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_41);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_42);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_43);			//�A�[�}�[�ݒ�
	Screw_07.Set(&Armor_7_44);			//�A�[�}�[�ݒ�
//	Screw_07.Set_JudgeType(CoreObject::CORE_JUDGE_TYPE_1);

	Screw_08.Set_JudgeType(CoreObject::CORE_JUDGE_TYPE_0);

	Screw_08.Set(&Armor_8_11, &Body_07);//�l�W�ɓ��̂ƃA�[�}�[��ݒ�
	Screw_08.Set(&Armor_8_12);			//�l�W�̓��̂͌��܂��Ă���̂ŁA�A�[�}�[�����ݒ�
	Screw_08.Set(&Armor_8_13);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_14);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_21);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_22);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_23);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_24);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_31);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_32);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_33);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_34);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_41);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_42);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_43);			//�A�[�}�[�ݒ�
	Screw_08.Set(&Armor_8_44);			//�A�[�}�[�ݒ�

	DebugCollisionModule::Init();

	Grid_Initialize();
	g_Camera.Set_Main();
}

//-------------------------------------
//	�X�V
//-------------------------------------
void CTeamProt_Update()
{
	GameObject::g_Update();
	g_Camera.Update();
}

//-------------------------------------
//	�`��
//-------------------------------------
void CTeamProt_Render()
{
	GameObject::g_Render();

	//Grid_Render();

	Camera::Begin();
	
}

//-------------------------------------
//	�I��
//-------------------------------------
void CTeamProt_Finalize()
{

}

