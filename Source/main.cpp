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

#include"CTransform.h"

#include"TestSpace.h"

#include "MeshField_Ground.h"
//Class
#include"CUI.h"

#include"MeshField_Ground.h"

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

	MeshField_Ground_Initialize();	//MeshField仕様変更
	XModel_Initialize();			//XModel仕様変更
	Bullet_Initialize();			//Bulletの初期化 (問題処理)
	Screwdrop_Init();				//ネジが落ちる
	CTeamProt_Initialize();
	TestSpace_Initialize();	//テストスペース
	Player_Initialize();			
	Cube_Initialize();				//Cube色をMaterialで管理

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
	Bullet_Update();	//弾の更新
	Screwdrop_Update();		//弾落とす動き
	//Player_Update();		//GameObjectで更新をかける
	CTeamProt_Update();		//CTeamでの更新処理
	TestSpace_UpdateBegin();//テストスペース処理

}

//=============================================================
//	描画処理
//=============================================================
void Main_Render(void)
{
	MeshField_Ground_Render( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), MeshGroundTexture1 );
	CTeamProt_Render();
	TestSpace_Render();

	uiSprite.render.Begin(R2D_SPRITE_ROTATE);
	Bullet_Render();
	Screwdrop_Render();
	//Player_Render();			GameObjectで描画をかける
	
}


//=============================================================
//	後 処理
//=============================================================
void Main_UpdateEnd()
{
	TestSpace_UpdateEnd();
}

//=============================================================
//	終了処理
//=============================================================
void Main_Finalize(void)
{
	TestSpace_Finalize();
	CTeamProt_Finalize();

	MeshField_Ground_Finalize();

}
