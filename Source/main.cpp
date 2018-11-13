//
//	Main.cpp
//		Author:HIROMASA IKEDA		Date:2018/09/13
//================================================
#include"common.h"
#include<time.h>
#include"System.h"

#include"Cube.h"
#include"Lighting.h"

#include"SecondWindow.h"
#include"CTeamProt.h"
#include"Player.h"
#include"Bullet.h"
#include"XModel.h"
#include"Screwdrop.h"

#define MODEL_FILE ()

#include"CTransform.h"

//Class
#include"CUI.h"

//===============================================
//	グローバル変数
//===============================================

//UI表示
static UI uiSprite(
	&Transform2
	(
		D3DXVECTOR2(WINDOWSCREEN_WIDTH*0.5f,WINDOWSCREEN_HEIGHT * 0.5f),
		D3DXVECTOR2(5.0f, 5.0f),
		0,
		D3DCOLOR_RGBA(255, 255, 0, 255)
	),
	&Texture
	(
		CubeTexture,
		{ 0,0 },
		{ 256,256 }
	)
);

//=============================================================
//	初期化処理
//=============================================================
void Main_Initialize(void)
{
	Lighting_Initialize();

	XModel_Initialize();
	Bullet_Initialize();
	Screwdrop_Init();
	CTeamProt_Initialize();
	Player_Initialize();
	Cube_Initialize();

	uiSprite = uiSprite;

	srand((UINT)time(NULL));

	//XModel_Load("Models/Ps4_Controller2.x");
}

//=============================================================
//	前 更新処理
//=============================================================
void Main_UpdateBegin(void)
{
	WinSock_Receiver();	//データを受信します。

	CTeamProt_Update();
	Bullet_Update();
	Screwdrop_Update();
	Player_Update();

}

//=============================================================
//	描画処理
//=============================================================
void Main_Render(void)
{
	//XModel_Render();
	Transform::ResetConvert();		//変換判定を初期化

	CTeamProt_Render();

	uiSprite.render.Begin(R2D_SPRITE_ROTATE);
	
	Bullet_Render();
	Screwdrop_Render();
	Player_Render();
	
}


//=============================================================
//	後 処理
//=============================================================
void Main_UpdateEnd()
{

}

//=============================================================
//	終了処理
//=============================================================
void Main_Finalize(void)
{
	Player_Finalize();
	CTeamProt_Finalize();
}
