//
//	CCollisionChecker.h
//		Author:	Hashimoto Yuto DATE: 11/19/2018
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef _COLLISION_CHECKER_H_
#define _COLLISION_CHECKER_H_

//================================================
//	インクルード	include
//================================================
#include"common.h"

// #include <vector>
//Class
class ShapeSphere;
class ShapeOBB;
class Player;
class Bullet;
class CoreObject;

// using namespace std;
//================================================
//	マクロ定義	define
//================================================

#define COLLISION_BULLET_MAX    ( 1024 )
#define COLLISION_CORE_MAX      ( 1014 )
//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================


//================================================
//	グローバル変数　global
//================================================


//================================================
//	クラス		class
//================================================


//-------------------------------------
//	クラス名
//-------------------------------------
class TmpCollisionChecker
{
private:
	TmpCollisionChecker();
	TmpCollisionChecker( const TmpCollisionChecker& ) {};
private:
	static TmpCollisionChecker* pInstance;
public:
	static TmpCollisionChecker* GetInstance( void );
private: // 登録アドレス vectorでよいです ------------------------------------------------------- CHANGE!>
	Player* pPlayer; // 将来的に複数化
	Bullet* pBulletCollection[ COLLISION_BULLET_MAX ];
	CoreObject* pCoreCollection[ COLLISION_CORE_MAX ];
public: // 登録処理 戻値boolいらないのでは？
	// プレイヤー
	bool RegisterCollision_Player( Player* Collision );
	bool DeregisterCollision_Player( Player* Collision );
	// 弾
	bool RegisterCollision_Bullet( Bullet* Collision );
	bool DeregisterCollision_Bullet( Bullet* Collision );
	// コア
	bool RegisterCollision_CoreObject( CoreObject* Collision );
	bool DeregisterCollision_CoreObject( CoreObject* Collision );
public:
	void CheckCollision( void );
private:
	void CheckBulletVsCoreObj( void );
	// void CheckCollisionPlayerVsStageObj( void ); // プレイヤー vs 地形 // 名前が微妙
	// void CheckCollisionBulletVsStageObj( void );// 弾 vs 地形

};
class CollisionCollection
{
public:
	enum COLLISION_SIDE
	{
		PLAYER_01 = 0,
		PLAYER_02,
		PLAYER_03,
		PLAYER_04,
		NO_ALIGNED,
		ENUM_COLLISION_SIDE_MAX,
		ENUM_COLLISION_SIDE_HEAD
	};
private:
	CollisionCollection() {};
	CollisionCollection( CollisionCollection& ) {}
private: 
	static CollisionCollection* pInstance[ ENUM_COLLISION_SIDE_MAX ];
public:
	static CollisionCollection* GetInstance( COLLISION_SIDE SideIndex );
public:
	static bool GetIsExist( COLLISION_SIDE SideIndex );
private:
	ShapeOBB* pPlayer; // 将来的に複数化
	ShapeSphere* pBulletCollection[ COLLISION_BULLET_MAX ];
	ShapeSphere* pCoreCollection[ COLLISION_CORE_MAX ];
public: // 登録処理 戻値boolいらないのでは？
	bool RegisterCollision_CoreObject( ShapeSphere* Collision );
	bool DeregisterCollision_CoreObject( ShapeSphere* Collision );
	bool RegisterCollision_Bullet( ShapeSphere* Collision );
	bool DeregisterCollison_Bullet( ShapeSphere* Collision );
	
};

#endif