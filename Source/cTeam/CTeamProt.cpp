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
#include "CCollisionChecker.h" // 当たり判定
#include "Debug_Collision.h" // 当たり判定デバッグ描画

//===============================================
//	グローバル変数
//===============================================
static Camera g_Camera;
static Camera g_Camera1;
static Camera g_Camera2;
static Camera g_Camera3;
static float movez = -5.0f;

//胴体
static BodyObject Body_07(
	&Transform
	(
		D3DXVECTOR3(0.0f, 0.0f + 3.0f, movez - 1.0f),
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
//アーマー
static ArmorObject Armor_7_11(
	&Transform
	(
		D3DXVECTOR3(-3.0f, 3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	RADIALLY
);
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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

//ネジ
static CoreObject Screw_07
(
	&Transform
	(
		D3DXVECTOR3(0.0f, 3.0f, 1.0f + movez),
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

//胴体
static BodyObject Body_08(
	&Transform
	(
		D3DXVECTOR3(0.0f, 0.0f + 3.0f, 5.0f*movez - 1.0f),
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
//アーマー
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
//アーマー
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
//アーマー
static ArmorObject Armor_8_13(
	&Transform
	(
		D3DXVECTOR3(1.0f, 3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	),
	FALL
);
//アーマー
static ArmorObject Armor_8_14(
	&Transform
	(
		D3DXVECTOR3(3.0f, 3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	FALL
);
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
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
//アーマー
static ArmorObject Armor_8_41(
	&Transform
	(
		D3DXVECTOR3(-3.0f, -3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	),
	FALL
);
//アーマー
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
//アーマー
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
//アーマー
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

//ネジ
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
//	関数
//===============================================

//-------------------------------------
//	初期化
//-------------------------------------
void CTeamProt_Initialize()
{

	Screw_07.Set_JudgeType(CoreObject::CORE_JUDGE_TYPE_1);

	Screw_07.Set(&Armor_7_11, &Body_07);//ネジに胴体とアーマーを設定
	Screw_07.SetArmor(&Armor_7_12);			//ネジの胴体は決まっているので、アーマーだけ設定
	Screw_07.SetArmor(&Armor_7_13);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_14);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_21);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_22);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_23);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_24);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_31);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_32);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_33);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_34);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_41);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_42);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_43);			//アーマー設定
	Screw_07.SetArmor(&Armor_7_44);			//アーマー設定
										//	Screw_07.Set_JudgeType(CoreObject::CORE_JUDGE_TYPE_1);

	Screw_08.Set_JudgeType(CoreObject::CORE_JUDGE_TYPE_0);

	Screw_08.Set(&Armor_8_11, &Body_07);//ネジに胴体とアーマーを設定
	Screw_08.SetArmor(&Armor_8_12);			//ネジの胴体は決まっているので、アーマーだけ設定
	Screw_08.SetArmor(&Armor_8_13);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_14);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_21);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_22);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_23);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_24);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_31);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_32);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_33);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_34);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_41);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_42);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_43);			//アーマー設定
	Screw_08.SetArmor(&Armor_8_44);			//アーマー設定

	Grid_Initialize();
	g_Camera.Set_Main(0);
	g_Camera1.Set_Main(1);
	g_Camera2.Set_Main(2);
	g_Camera3.Set_Main(3);
}

//-------------------------------------
//	更新
//-------------------------------------
void CTeamProt_Update()
{
	GameObject::g_Update();

	TmpCollisionChecker::GetInstance()->CheckCollision();

	g_Camera.Update();

}

//-------------------------------------
//	描画
//-------------------------------------
void CTeamProt_Render()
{
	DebugCollisionModule::GetInstance()->BatchBegin();
	GameObject::g_Render();
	DebugCollisionModule::GetInstance()->BatchRun();
	//Grid_Render();

	//Camera::Begin();


}

//-------------------------------------
//	終了
//-------------------------------------
void CTeamProt_Finalize()
{

}

