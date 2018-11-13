//
//	CCamera.h
//		Author:HIROMASA IKEDA	DATE:2018/10/16
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CCAMERA_H
#define CCAMERA_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>

//Class
#include"CTransform.h"

//===============================================
//	マクロ定義	define
//===============================================


//================================================
//	列挙型		enum
//================================================


//===============================================
//	マクロ定義
//===============================================
#define CAMERA_POS (D3DXVECTOR3(0.0f, 5.0f, 5.0f))		//カメラ位置
#define CAMERA_AT (D3DXVECTOR3(0.0f, 0.0f, 0.0f))		//カメラの注視点
#define CAMERA_UP (D3DXVECTOR3(0.0f,1.0f,0.0f))			//カメラの上方向 (どういう捩れで見るの？)
#define CAMERA_FORWARD (D3DXVECTOR3(0.0f,0.0f,-1.0f))	//カメラ前
#define CAMERA_INITIALSPEED (0.05f)						//カメラの初期速度

#define CAMERA_NEAR (0.1f)
#define CAMERA_WAR (100.0f)

#define SCREEN_ASPECT ((float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT)
#define CAMERA_ATDISTANCE (10.0f)
#define CAMERA_FOV (D3DXToRadian(60))

#define CAMERA_COUNT (4) //カメラ数

//================================================
//	グローバル変数　global
//================================================

//================================================
//	クラス		class
//================================================

//-------------------------------------
//	Camera　クラス
//-------------------------------------
class Camera
{
public:
	static Camera* Get_Main();
	static bool Begin();		//描画開始

private:
	static Camera* MainCamera;					//メインカメラ
	//static Camera* SubCamera;					//サブカメラ

public:
	D3DXVECTOR3 position;		//位置
	float Speed;				//移動速度

	D3DXVECTOR3 at;				//注視点
	D3DXVECTOR3 up;				//カメラ上
	D3DXVECTOR3 forward;		//カメラ前
	D3DXVECTOR3 right;			//カメラ右
	float atDistance;			//注視点までの距離
	float fov;					//画角

public:
	Camera() :Camera(CAMERA_POS, CAMERA_AT, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	Camera(D3DXVECTOR3 Position) : Camera(Position, CAMERA_AT, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	Camera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov);

public:
	void Set_Main();			//メインカメラに設定
	//void Set_Sub();				//サブカメラに設定

public:
	virtual void Initialize();	//初期化
	virtual void Update();		//更新
};


#endif