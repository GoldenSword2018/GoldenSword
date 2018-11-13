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

//-------------------------------------
//	プレイヤーカメラ
//-------------------------------------
class PlayerCamera:public Camera
{
private:

public:
	
	void Initialize();
	void Update();
};

//-------------------------------------
//	プレイヤー
//-------------------------------------
class Player:public GameObject
{
private:
	D3DXVECTOR3 Forward;
	D3DXVECTOR3 Right;
	float AngleY;						// Y軸周りの回転角（視点の左右方向角度）
	float AngleX;						// X軸周りの回転角（視点の仰角俯角）
	float g_OldAngleX;
	ShapeSphere ColShape;
	BodyObject Head;
	BodyObject Body;
	BodyObject LeftArm;
	BodyObject RightArm;
	BodyObject LeftLeg;
	BodyObject RightLeg;

public:
	Player(Transform* pTransform, D3DXVECTOR3* pForward);
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