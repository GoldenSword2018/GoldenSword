//
//	Player.h
//		Author:YU NISHIMAKI	DATE:2018/10/13
//===============================================
#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include"common.h"
#include<d3dx9.h>

//Class
#include"CGameObject.h"
#include"CCamera.h"
#include"CCollisionShape.h"
#include"CBodyObject.h"
#include"CCoreObject.h"
#include"CArmorObject.h"

//===============================================
//	マクロ定義
//===============================================
#define PLAYER_MOVE_SPEED		(0.1f)				// プレイヤー移動速度
#define WAIT_ANGLER_VEROCITY	(100.0f * 24.0f)	// 角速度補正値
#define WAIT_ROT_Y				(40)				// 視点左右回転速度補正値

#define DISTANCE_TO_AT			(5.0f)				// 注視点までの距離
#define LIMIT_CAMERA_ELEVATION	(80.0f)				// カメラの仰俯角の限界値

//===============================================
//	Player 構造体
//===============================================
typedef struct PLAYER_tag
{
	D3DXVECTOR3 Position;				// プレイヤー座標
	D3DXVECTOR3 Verocity;				// 速度
	D3DXVECTOR3 vecDir;					// 向いている方向
	float AngleY;						// Y軸周りの回転角（視点の左右方向角度）
	float AngleX;						// X軸周りの回転角（視点の仰角俯角）
}PLAYER;

//===============================================
//	クラス
//===============================================
class Player;
class PlayerCamera;
//-------------------------------------
//	プレイヤーカメラ
//-------------------------------------
class PlayerCamera:public Camera
{
public:
	void Initialize();
	void Update();
};

//-------------------------------------
//	プレイヤー
//-------------------------------------
class Player:public GameObject
{
public:

private:
	D3DXVECTOR3 Forward;
	D3DXVECTOR3 Right;

	float AngleY;						// Y軸周りの回転角（視点の左右方向角度）
	float AngleX;						// X軸周りの回転角（視点の仰角俯角）
	float g_OldAngleX;
public:
	ShapeOBB ColShape;

	float RotY;
	float RotAxis;
	
public:
	//各部位
	BodyObject Head;
	BodyObject Body;
	BodyObject LeftArm;
	BodyObject RightArm;
	BodyObject LeftLeg;
	BodyObject RightLeg;

public:
	//コア
	CoreObject Head_Screw;
	CoreObject Body_Screw;
	CoreObject LeftArm_Screw;
	CoreObject RightArm_Screw;
	CoreObject LeftLeg_Screw;
	CoreObject RightLeg_Screw;

public:
	//アーマー
	ArmorObject Head_Armor01;

	ArmorObject Body_Armor01;

	ArmorObject LeftArm_Armor01;

	ArmorObject RightArm_Armor01;

	ArmorObject LeftLeg_Armor01;

	ArmorObject RightLeg_Armor01;

public:
	Player(Transform* pTransform, D3DXVECTOR3* pForward);

private:
	void Set_Parts();		//部位を設定

public:
	PlayerCamera Camera;
	void Update();
	void Render();
	void Move();
	void Rotation();
	void SetPosition(D3DXVECTOR3 Position);
	void SetForward(D3DXVECTOR3 Forward);
	void ResetAngle();
	void Fire();
	D3DXMATRIX CalWorldMtx();

};

//===============================================
//	関数
//===============================================
void Player_Initialize(void);
void Player_Update(void);
void Player_Render(void);
void Player_Finalize(void);

void Player_ResetAngle(void);
const PLAYER *Player_GetPlayer(void);

#endif // !PLAYER_H