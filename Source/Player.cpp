//
//	Player.cpp
//		Author:YU NISHIMAKI	DATE:2018/10/13
//===============================================
//	変更者 Changed By
//		Name:HIROMASA IEKDA	DATE:2018/11/13
//
//-----------------------------------------------
#include<d3dx9.h>
#include"common.h"
#include"input.h"
#include"joycon_input.h"
#include"Debug_font.h"
#include"Player.h"

#include"Bullet.h"
#include"CGameObject.h"
//Class
#include "CCollisionChecker.h"
// Debug用
#include "Debug_Collision.h"

//===============================================
//	グローバル変数
//===============================================
Player Player01(
	&Transform
	(
		D3DXVECTOR3(0.0f, 0.0f, -10.0f),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DCOLOR_RGBA(255, 255, 255, 255)
	),
	&D3DXVECTOR3(0.0f, 0.0f, 1.0f)
);

//===============================================
//	初期化
//===============================================
void Player_Initialize(void)
{
	Player01.Camera.Set_Main(0);
	Bullet_Initialize();
	TmpCollisionChecker::GetInstance()->RegisterCollision_Player( &Player01 );
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
	TmpCollisionChecker::GetInstance()->DeregisterCollision_Player( &Player01 );
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
	this->atDistance = 3.0f;
	Camera::Update();
}

//===============================================
//	Player クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Player::Player(Transform *pTransform, D3DXVECTOR3 *pForward)
	:
	GameObject(pTransform, &Texture()),
	ColShape
	(
		&transform.Position,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&D3DXVECTOR3(1.0f, 5.0f, 1.0f)
	),
	//コア
	Head_Screw(&Transform(D3DCOLOR_RGBA(255,0,0,255))),
	Body_Screw(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	LeftArm_Screw(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	RightArm_Screw(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	LeftLeg_Screw(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	RightLeg_Screw(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),

	//アーマー
	Head_Armor01(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	Body_Armor01(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	LeftArm_Armor01(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	RightArm_Armor01(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	LeftLeg_Armor01(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255))),
	RightLeg_Armor01(&Transform(D3DCOLOR_RGBA(255, 0, 0, 255)))
{
	this->Forward = *pForward;
	this->AngleY = 0.0f;
	this->AngleX = 0.0f;
	this->RotY = 0.0f;
	this->RotAxis = 0.0f;
	this->g_OldAngleX = 0.0f;
	D3DXVECTOR3 vecRight = this->Forward;
	D3DXMATRIX mtxRotationY;
	D3DXMatrixRotationY(&mtxRotationY, (-D3DX_PI / 2));
	D3DXVec3TransformNormal(&vecRight, &vecRight, &mtxRotationY);
	vecRight.y = 0.0f;
	D3DXVec3Normalize(&vecRight, &vecRight);
	this->Right = vecRight;

	this->Set_Parts();
}

//-------------------------------------
//	各部位を設定
//-------------------------------------
void Player::Set_Parts()
{
	//プレイヤーと親子関係を作る
	Head.Set_Parent(this);
	Body.Set_Parent(this);
	LeftArm.Set_Parent(this);
	RightArm.Set_Parent(this);
	LeftLeg.Set_Parent(this);
	RightLeg.Set_Parent(this);

	Head_Screw.Set_Parent(this);
	Body_Screw.Set_Parent(this);
	LeftArm_Screw.Set_Parent(this);
	RightArm_Screw.Set_Parent(this);
	LeftLeg_Screw.Set_Parent(this);
	RightLeg_Screw.Set_Parent(this);

	//
	Head.transform.Position = D3DXVECTOR3(0.0f,1.4f,0.0f);
	Head.transform.Scale = D3DXVECTOR3(0.8f,0.8f,0.8f);

	//
	Body.transform.Position = D3DXVECTOR3(0.0f,-0.0f,0.0f);
	Body.transform.Scale = D3DXVECTOR3(1.0f,2.0f,1.0f);

	//
	LeftArm.transform.Position = D3DXVECTOR3(-0.9f,-0.2f,0.0f);
	LeftArm.transform.Scale = D3DXVECTOR3(0.5f,2.0f,0.5f);

	//
	RightArm.transform.Position = D3DXVECTOR3(0.9f,-0.2f,0.0f);
	RightArm.transform.Scale = D3DXVECTOR3(0.5f,2.0f,0.5f);

	//
	LeftLeg.transform.Position = D3DXVECTOR3(-0.2f,-2.0f,0.0f);
	LeftLeg.transform.Scale = D3DXVECTOR3(0.5f,2.0f,0.5f);

	//
	RightLeg.transform.Position = D3DXVECTOR3(0.2f,-2.0f,0.0f);
	RightLeg.transform.Scale = D3DXVECTOR3(0.5f,2.0f,0.5f);

	//コアの登録
	Head_Screw.SetBody(&Head);
	Body_Screw.SetBody(&Body);
	LeftArm_Screw.SetBody(&LeftArm);
	RightArm_Screw.SetBody(&RightArm);
	LeftLeg_Screw.SetBody(&LeftLeg);
	RightLeg_Screw.SetBody(&RightLeg);

	//アーマーの登録
	Head_Screw.SetArmor(&Head_Armor01);
	
	Body_Screw.SetArmor(&Body_Armor01);

	LeftArm_Screw.SetArmor(&LeftArm_Armor01);

	RightArm_Screw.SetArmor(&RightArm_Armor01);

	LeftLeg_Screw.SetArmor(&LeftLeg_Armor01);

	RightLeg_Screw.SetArmor(&RightLeg_Armor01);
}

//-------------------------------------
//	更新
//-------------------------------------
void Player::Update()
{
	this->Camera.Position = this->transform.Position;
	this->Camera.Update();
	this->transform.Set_WorldTransform();				//WorldPositionを算出
	this->transform.WorldPosition.y = 0.0f;				//高さを固定

	
	SetForward(this->Camera.forward);
	this->transform.Rotation.y = this->RotY;

	D3DXVECTOR3 face = this->Forward;
	face.y = 0.0f;
	Head_Screw.face = face;
	Body_Screw.face = face;
	LeftArm_Screw.face = face;
	RightArm_Screw.face = face;
	LeftLeg_Screw.face = face;
	RightLeg_Screw.face = face;

	Head_Screw.transform.Rotation.y = AngleY;
	Body_Screw.transform.Rotation.y = AngleY;
	LeftArm_Screw.transform.Rotation.y = AngleY;


	CalWorldMtx();

	if (Keyboard_IsPress(DIK_W))
	{
		this->transform.Position += this->transform.forward * PLAYER_MOVE_SPEED;
	}

	if(Keyboard_IsPress(DIK_S))
	{
		this->transform.Position -= this->transform.forward * PLAYER_MOVE_SPEED;
	}

	if (Keyboard_IsPress(DIK_A))
	{
		this->transform.Position -= this->transform.right * PLAYER_MOVE_SPEED;
	}

	if (Keyboard_IsPress(DIK_D))
	{
		this->transform.Position += this->transform.right * PLAYER_MOVE_SPEED;
	}



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

	SetPosition(this->transform.Position);
	this->Camera.at = this->transform.WorldPosition;	//注視点をプレイヤーに
	this->Camera.at.y += 2.0f;
	this->Camera.Position = this->Camera.at - this->Forward * this->Camera.atDistance;		//カメラ位置を決める

}


//-------------------------------------
//	描画
//-------------------------------------
void Player::Render()
{
	//XModel_Render( GetMeshData( BulletIndex ), CalWorldMtx() );
	ColShape.DebugDraw();
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

	this->Camera.Position = this->transform.Position;									// カメラ位置をプレイヤー座標に同期
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
	//わからねぇ！！！
	D3DXVECTOR3 look = this->Forward;
	Bullet_Create(this->transform.Position, look, Bullet::NORMAL);
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

	RotY = atan2f(vecDirGround.x, vecDirGround.z);
	RotAxis = acosf(D3DXVec3Dot(&this->Forward, &vecDirGround));
	D3DXMatrixRotationY(&mtxRotationY, RotY);
	D3DXMatrixRotationAxis(&mtxRotationAxis, &this->Right, RotAxis);

	D3DXMatrixTranslation(&mtxTranslation, this->transform.Position.x, this->transform.Position.y, this->transform.Position.z);
	mtxWorld = mtxRotationY * mtxRotationAxis * mtxTranslation;

	return mtxWorld;
}
