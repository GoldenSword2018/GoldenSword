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
static float movez = -5.0f;

//===============================================
//	関数
//===============================================

//-------------------------------------
//	初期化
//-------------------------------------
void CTeamProt_Initialize()
{
}

//-------------------------------------
//	更新
//-------------------------------------
void CTeamProt_Update()
{
	GameObject::g_Update();		//ゲームオブジェクトの更新

	TmpCollisionChecker::GetInstance()->CheckCollision();
}

//-------------------------------------
//	描画
//-------------------------------------
void CTeamProt_Render()
{
	DebugCollisionModule::GetInstance()->BatchBegin();
	GameObject::g_Render();
	DebugCollisionModule::GetInstance()->BatchRun();

}

//-------------------------------------
//	終了
//-------------------------------------
void CTeamProt_Finalize()
{

}

