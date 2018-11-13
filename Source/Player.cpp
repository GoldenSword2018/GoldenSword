//
//	Player.cpp
//		Author:YU NISHIMAKI	DATE:2018/10/13
//===============================================
//	変更者 Changed By
//		Name:HIROMASA IEKDA	DATE:2018/10/17
//
//-----------------------------------------------
#include<d3dx9.h>
#include"common.h"
#include"input.h"
#include"joycon_input.h"
#include"Debug_font.h"
#include"Player.h"

#include"Bullet.h"
//Class

//===============================================
//	マクロ定義
//===============================================
#define PLAYER_MOVE_SPEED		(0.1f)				// プレイヤー移動速度
#define WAIT_ANGLER_VEROCITY	(100.0f * 24.0f)	// 角速度補正値
#define WAIT_ROT_Y				(40)				// 視点左右回転速度補正値

#define DISTANCE_TO_AT			(5.0f)				// 注視点までの距離
#define LIMIT_CAMERA_ELEVATION	(80.0f)				// カメラの仰俯角の限界値

//===============================================
//	グローバル変数
//===============================================
Player Player01(&Transform(D3DXVECTOR3(0.0f, 0.0f, -10.0f),
	D3DXVECTOR3(1.0f, 1.0f, 1.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DCOLOR_RGBA(255, 255, 255, 255)),
	&D3DXVECTOR3(0.0f, 0.0f, 1.0f)
);

//===============================================
//	初期化
//===============================================
void Player_Initialize(void)
{
	Player01.Camera.Set_Main();
	Bullet_Initialize();

	


}

//===============================================
//	更新
//===============================================
void Player_Update(void)
{
	Player01.Update();
	Bullet_Update();
}

//===============================================
//	描画
//===============================================
void Player_Render(void)
{
	Player01.Render();
	Bullet_Render();
}

//===============================================
//	終了処理
//===============================================
void Player_Finalize(void)
{

}


//===============================================
//	PlayerCamera クラス
//===============================================

//-------------------------------------
//	初期化
//-------------------------------------
void PlayerCamera::Initialize()
{

}

//-------------------------------------
//	更新
//-------------------------------------
void PlayerCamera::Update()
{
	Camera::Update();
}

//===============================================
//	PlayerCamera クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Player::Player(Transform *pTransform, D3DXVECTOR3 *pForward) :GameObject(pTransform, &Texture()), ColShape(&pTransform->Position,1.0f)
{
	this->Forward = *pForward;
	float AngleY = 0.0f;
	float AngleX = 0.0f;
	float g_OldAngleX = 0.0f;
	D3DXVECTOR3 vecRight = this->Forward;
	D3DXMATRIX mtxRotationY;
	D3DXMatrixRotationY(&mtxRotationY, (-D3DX_PI / 2));
	D3DXVec3TransformNormal(&vecRight, &vecRight, &mtxRotationY);
	vecRight.y = 0.0f;
	D3DXVec3Normalize(&vecRight, &vecRight);
	this->Right = vecRight;
}

//-------------------------------------
//	更新
//-------------------------------------
void Player::Update()
{
	this->Camera.Update();
	SetPosition(this->Camera.position);
	SetForward(this->Camera.forward);

#if !defined(DISABLE_JOYCON) && !defined(DISABLE_GAMEPAD)
	Move();
	Rotation();

	if (JoyconInput_IsTrigger(JOYCON_BUTTON_INDEX_R_ZR))		// ZRボタン入力でカメラリセット
	{
		ResetAngle();
	}
#endif

	if (JoyconInput_IsTrigger(JOYCON_BUTTON_INDEX_R_SR) || Keyboard_IsTrigger(DIK_F))		// SRボタン入力かFキーで発射
	{
		Fire();
	}

}


//-------------------------------------
//	描画
//-------------------------------------
void Player::Render()
{
	XModel_Render(GetMeshData(BulletIndex), CalWorldMtx());
}


//-------------------------------------
//	移動
//-------------------------------------
void Player::Move()
{
	// 移動
	D3DXVECTOR3 vecDirMove(0.0f, 0.0f, 0.0f);													// 移動方向ベクトルワーク

	vecDirMove.x = (float)JoyconInput_GetLeftStickX();											// Joy-Conのスティック入力を取得
	vecDirMove.z = -(float)JoyconInput_GetLeftStickY();											// Joy-Conのスティック入力を取得
	D3DXVec3Normalize(&vecDirMove, &vecDirMove);												// vecDirの単位ベクトル化

	vecDirMove *= PLAYER_MOVE_SPEED;															// 移動速度を設定

	this->transform.Position += this->Forward * vecDirMove.z + this->Right * vecDirMove.x;		// プレイヤー座標に加算して反映

}

//-------------------------------------
//	回転
//-------------------------------------
void Player::Rotation()
{
	// 視点変更
	this->AngleY += JoyconInput_GetAVYaw() / WAIT_ANGLER_VEROCITY;						// Joy-Conのヨー角速度を取得して加算
	this->AngleX += JoyconInput_GetAVPitch() / WAIT_ANGLER_VEROCITY;					// Joy-Conのピッチ角速度を取得して加算

	// 視点横回転移動
	D3DXVECTOR3 vecDirForward = this->Forward;											// 視点方向ベクトルワーク
	D3DXVECTOR3 vecDirRight = this->Right;												// 視点右方向ベクトルワーク

	float RotY = 0.0f;																	// Y軸周りの回転角ワーク

	// プレイヤーの回転角に応じてカメラ回転速度調整
	RotY = this->AngleY / WAIT_ROT_Y;

	D3DXMATRIX mtxRotationY;															// ベクトル回転用マトリクス
	D3DXMatrixRotationY(&mtxRotationY, D3DXToRadian(RotY));								// 回転角分Y軸周りに回転するマトリクスを設定

	D3DXVec3TransformNormal(&vecDirForward, &vecDirForward, &mtxRotationY);				// 視点方向をY軸周りに回転
	D3DXVec3TransformNormal(&vecDirRight, &vecDirRight, &mtxRotationY);					// 視点右方向をY軸周りに回転
	D3DXVec3Normalize(&vecDirForward, &vecDirForward);									// 単位ベクトル化
	D3DXVec3Normalize(&vecDirRight, &vecDirRight);										// 単位ベクトル化

	// 視点上下方向移動
	D3DXMATRIX mtxRotationAxis;															// 任意軸周りに回転する用のマトリクス
	float RotAxis = (this->AngleX - g_OldAngleX) / 1.2f;								// 回転角をプレイヤーの上下角から設定
	
	// 上下方向の回転に上限を設ける
	if (this->AngleX > LIMIT_CAMERA_ELEVATION)										
		RotAxis = LIMIT_CAMERA_ELEVATION;
	else if (this->AngleX < -LIMIT_CAMERA_ELEVATION)
		RotAxis = -LIMIT_CAMERA_ELEVATION;

	D3DXMatrixRotationAxis(&mtxRotationAxis, &vecDirRight, D3DXToRadian(RotAxis));		// 真横方向ベクトル周り（すなわち上下方向）に視点方向を回転させるマトリクスを設定

	D3DXVec3TransformNormal(&vecDirForward, &vecDirForward, &mtxRotationAxis);			// 回転を適用
	D3DXVec3Normalize(&vecDirForward, &vecDirForward);									// 単位ベクトル化

	this->Forward = vecDirForward;														// 完成した視点方向ベクトルをプレイヤー視点方向に適用
	this->Right = vecDirRight;															// 完成した視点方向ベクトルをプレイヤー視点方向に適用

	this->Camera.position = this->transform.Position;									// カメラ位置をプレイヤー座標に同期
	this->Camera.forward = this->Forward;												// カメラ方向をプレイヤーの向きに同期
	this->Camera.right = this->Right;
	this->Camera.at = this->transform.Position + this->Forward * DISTANCE_TO_AT;		// カメラ注視点をプレイヤー座標とプレイヤー視点方向から算出

	g_OldAngleX = this->AngleX;

}

//-------------------------------------
//	座標セット
//-------------------------------------
void Player::SetPosition(D3DXVECTOR3 Position)
{
	this->transform.Position = Position;
}

//-------------------------------------
//	方向セット
//-------------------------------------
void Player::SetForward(D3DXVECTOR3 Forward)
{
	this->Forward = Forward;
}

//-------------------------------------
//	視点方向リセット
//-------------------------------------
void Player::ResetAngle()
{
	this->AngleX = 0.0f;
	this->AngleY = 0.0f;
}

//-------------------------------------
//	発射
//-------------------------------------
void Player::Fire()
{
	Bullet_Create(this->transform.Position, this->Forward, Bullet::NORMAL);
}

//-------------------------------------
//	向いている方向を基準にWorldMatrixを計算
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

	float RotY = atan2f(vecDirGround.x, vecDirGround.z);
	float RotAxis = acosf(D3DXVec3Dot(&this->Forward, &vecDirGround));
	D3DXMatrixRotationY(&mtxRotationY, RotY);
	D3DXMatrixRotationAxis(&mtxRotationAxis, &this->Right, RotAxis);

	D3DXMatrixTranslation(&mtxTranslation, this->transform.Position.x, this->transform.Position.y, this->transform.Position.z);
	mtxWorld = mtxRotationY * mtxRotationAxis * mtxTranslation;
	return mtxWorld;
}
