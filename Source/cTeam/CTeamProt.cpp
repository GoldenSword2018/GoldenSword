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

#include "Debug_Sphere.h"
//===============================================
//	グローバル変数
//===============================================
static Camera g_Camera;	
static float movez=-5.0f;

//胴体
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
//アーマー
static ArmorObject Armor_7_11(
	&Transform
	(
		D3DXVECTOR3(-3.0f, 3.0f+3.0f, 0.0f+movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_7_12(
	&Transform
	(
		D3DXVECTOR3(-1.0f, 3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_7_13(
	&Transform
	(
		D3DXVECTOR3(1.0f, 3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	)
);
//アーマー
static ArmorObject Armor_7_14(
	&Transform
	(
		D3DXVECTOR3(3.0f, 3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_7_21(
	&Transform
	(
		D3DXVECTOR3(-3.0f, 1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_7_22(
	&Transform
	(
		D3DXVECTOR3(-1.0f, 1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	)
);
//アーマー
static ArmorObject Armor_7_23(
	&Transform
	(
		D3DXVECTOR3(1.0f, 1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_7_24(
	&Transform
	(
		D3DXVECTOR3(3.0f, 1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_7_31(
	&Transform
	(
		D3DXVECTOR3(-3.0f, -1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	)
);
//アーマー
static ArmorObject Armor_7_32(
	&Transform
	(
		D3DXVECTOR3(-1.0f, -1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_7_33(
	&Transform
	(
		D3DXVECTOR3(1.0f, -1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_7_34(
	&Transform
	(
		D3DXVECTOR3(3.0f, -1.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	)
);
//アーマー
static ArmorObject Armor_7_41(
	&Transform
	(
		D3DXVECTOR3(-3.0f, -3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_7_42(
	&Transform
	(
		D3DXVECTOR3(-1.0f, -3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_7_43(
	&Transform
	(
		D3DXVECTOR3(1.0f, -3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	)
);
//アーマー
static ArmorObject Armor_7_44(
	&Transform
	(
		D3DXVECTOR3(3.0f, -3.0f + 3.0f, 0.0f + movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	)
);

//ネジ
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

//胴体
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
//アーマー
static ArmorObject Armor_8_11(
	&Transform
	(
		D3DXVECTOR3(-3.0f, 3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_8_12(
	&Transform
	(
		D3DXVECTOR3(-1.0f, 3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_8_13(
	&Transform
	(
		D3DXVECTOR3(1.0f, 3.0f + 3.0f, 0.0f + 5* movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	)
);
//アーマー
static ArmorObject Armor_8_14(
	&Transform
	(
		D3DXVECTOR3(3.0f, 3.0f + 3.0f, 0.0f+ 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_8_21(
	&Transform
	(
		D3DXVECTOR3(-3.0f, 1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_8_22(
	&Transform
	(
		D3DXVECTOR3(-1.0f, 1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	)
);
//アーマー
static ArmorObject Armor_8_23(
	&Transform
	(
		D3DXVECTOR3(1.0f, 1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_8_24(
	&Transform
	(
		D3DXVECTOR3(3.0f, 1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_8_31(
	&Transform
	(
		D3DXVECTOR3(-3.0f, -1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	)
);
//アーマー
static ArmorObject Armor_8_32(
	&Transform
	(
		D3DXVECTOR3(-1.0f, -1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_8_33(
	&Transform
	(
		D3DXVECTOR3(1.0f, -1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_8_34(
	&Transform
	(
		D3DXVECTOR3(3.0f, -1.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	)
);
//アーマー
static ArmorObject Armor_8_41(
	&Transform
	(
		D3DXVECTOR3(-3.0f, -3.0f + 3.0f, 0.0f+5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_8_42(
	&Transform
	(
		D3DXVECTOR3(-1.0f, -3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 255, 0, 255)
	)
);
//アーマー
static ArmorObject Armor_8_43(
	&Transform
	(
		D3DXVECTOR3(1.0f, -3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(0, 0, 255, 255)
	)
);
//アーマー
static ArmorObject Armor_8_44(
	&Transform
	(
		D3DXVECTOR3(3.0f, -3.0f + 3.0f, 0.0f + 5 * movez),
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 0, 0, 255)
	)
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
	Armor_7_11.Set_DischargingType(RADIALLY);
	Armor_7_12.Set_DischargingType(RADIALLY);
	Armor_7_13.Set_DischargingType(RADIALLY);
	Armor_7_14.Set_DischargingType(RADIALLY);
	Armor_7_21.Set_DischargingType(RADIALLY);
	Armor_7_22.Set_DischargingType(RADIALLY);
	Armor_7_23.Set_DischargingType(RADIALLY);
	Armor_7_24.Set_DischargingType(RADIALLY);
	Armor_7_31.Set_DischargingType(RADIALLY);
	Armor_7_32.Set_DischargingType(RADIALLY);
	Armor_7_33.Set_DischargingType(RADIALLY);
	Armor_7_34.Set_DischargingType(RADIALLY);
	Armor_7_41.Set_DischargingType(RADIALLY);
	Armor_7_42.Set_DischargingType(RADIALLY);
	Armor_7_43.Set_DischargingType(RADIALLY);
	Armor_7_44.Set_DischargingType(RADIALLY);


	Screw_07.Set(&Armor_7_11, &Body_07);//ネジに胴体とアーマーを設定
	Screw_07.Set(&Armor_7_12);			//ネジの胴体は決まっているので、アーマーだけ設定
	Screw_07.Set(&Armor_7_13);			//アーマー設定
	Screw_07.Set(&Armor_7_14);			//アーマー設定
	Screw_07.Set(&Armor_7_21);			//アーマー設定
	Screw_07.Set(&Armor_7_22);			//アーマー設定
	Screw_07.Set(&Armor_7_23);			//アーマー設定
	Screw_07.Set(&Armor_7_24);			//アーマー設定
	Screw_07.Set(&Armor_7_31);			//アーマー設定
	Screw_07.Set(&Armor_7_32);			//アーマー設定
	Screw_07.Set(&Armor_7_33);			//アーマー設定
	Screw_07.Set(&Armor_7_34);			//アーマー設定
	Screw_07.Set(&Armor_7_41);			//アーマー設定
	Screw_07.Set(&Armor_7_42);			//アーマー設定
	Screw_07.Set(&Armor_7_43);			//アーマー設定
	Screw_07.Set(&Armor_7_44);			//アーマー設定
//	Screw_07.Set_JudgeType(CoreObject::CORE_JUDGE_TYPE_1);
	
	Screw_08.Set_JudgeType(CoreObject::CORE_JUDGE_TYPE_0);
	Armor_8_11.Set_DischargingType(FALL);
	Armor_8_12.Set_DischargingType(FALL);
	Armor_8_13.Set_DischargingType(FALL);
	Armor_8_14.Set_DischargingType(FALL);
	Armor_8_21.Set_DischargingType(FALL);
	Armor_8_22.Set_DischargingType(FALL);
	Armor_8_23.Set_DischargingType(FALL);
	Armor_8_24.Set_DischargingType(FALL);
	Armor_8_31.Set_DischargingType(FALL);
	Armor_8_32.Set_DischargingType(FALL);
	Armor_8_33.Set_DischargingType(FALL);
	Armor_8_34.Set_DischargingType(FALL);
	Armor_8_41.Set_DischargingType(FALL);
	Armor_8_42.Set_DischargingType(FALL);
	Armor_8_43.Set_DischargingType(FALL);
	Armor_8_44.Set_DischargingType(FALL);


	Screw_08.Set(&Armor_8_11, &Body_07);//ネジに胴体とアーマーを設定
	Screw_08.Set(&Armor_8_12);			//ネジの胴体は決まっているので、アーマーだけ設定
	Screw_08.Set(&Armor_8_13);			//アーマー設定
	Screw_08.Set(&Armor_8_14);			//アーマー設定
	Screw_08.Set(&Armor_8_21);			//アーマー設定
	Screw_08.Set(&Armor_8_22);			//アーマー設定
	Screw_08.Set(&Armor_8_23);			//アーマー設定
	Screw_08.Set(&Armor_8_24);			//アーマー設定
	Screw_08.Set(&Armor_8_31);			//アーマー設定
	Screw_08.Set(&Armor_8_32);			//アーマー設定
	Screw_08.Set(&Armor_8_33);			//アーマー設定
	Screw_08.Set(&Armor_8_34);			//アーマー設定
	Screw_08.Set(&Armor_8_41);			//アーマー設定
	Screw_08.Set(&Armor_8_42);			//アーマー設定
	Screw_08.Set(&Armor_8_43);			//アーマー設定
	Screw_08.Set(&Armor_8_44);			//アーマー設定

	DebugBufferManager::Init();

	Grid_Initialize();
	g_Camera.Set_Main();
}

//-------------------------------------
//	更新
//-------------------------------------
void CTeamProt_Update()
{
	GameObject::g_Update();
	g_Camera.Update();
}

//-------------------------------------
//	描画
//-------------------------------------
void CTeamProt_Render()
{
	GameObject::g_Render();

	//Grid_Render();

	Camera::Begin();
	
}

//-------------------------------------
//	終了
//-------------------------------------
void CTeamProt_Finalize()
{

}

