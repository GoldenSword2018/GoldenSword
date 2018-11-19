//
//	CCollisionChecker.cpp
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"

//class
#include "CCollisionChecker.h"
#include "CCollisionShape.h"

#include "Bullet.h"
#include "Player.h"
#include "CCoreObject.h"
//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================


//===============================================
//	Tmp Collision Collection
//===============================================

TmpCollisionChecker* TmpCollisionChecker::pInstance;
//-------------------------------------
//	GetInstance
//-------------------------------------

TmpCollisionChecker* TmpCollisionChecker::GetInstance( void )
{
	if( !pInstance )
	{
		pInstance = new TmpCollisionChecker;
	}
	return pInstance;
}

TmpCollisionChecker::TmpCollisionChecker()
{
	// NULL初期化
	pPlayer = NULL;

	for( int bi = 0; bi < COLLISION_BULLET_MAX; bi++ )
	{
		pBulletCollection[ bi ] = NULL;
	}

	for( int ci = 0; ci < COLLISION_CORE_MAX; ci++ )
	{
		pCoreCollection[ ci ] = NULL;
	}
}

//-------------------------------------
//	RegisterCollision_Player プレイヤリストに登録
//-------------------------------------
bool TmpCollisionChecker::RegisterCollision_Player( Player* Collision )
{
	if( !pPlayer )
	{
		pPlayer = Collision;
	}
	return false;
}

//-------------------------------------
//	DeregisterCollision_Player プレイヤリストから解除
//-------------------------------------
bool TmpCollisionChecker::DeregisterCollision_Player( Player* Collision )
{
	if( pPlayer )
	{
		pPlayer = NULL;
	}
	return false;
}

//-------------------------------------
//	RegisterCollision_Bullet 弾リストに登録
//-------------------------------------
bool TmpCollisionChecker::RegisterCollision_Bullet( Bullet* Collision )
{
	for( int bi = 0; bi < COLLISION_BULLET_MAX; bi++ )
	{
		if( pBulletCollection[ bi ] == NULL )
		{
			pBulletCollection[ bi ] = Collision;
			return true;
		}
	}
	return false;
}

//-------------------------------------
//	DeregisterCollison_Bullet 弾リストから解除
//-------------------------------------
bool TmpCollisionChecker::DeregisterCollision_Bullet( Bullet* Collision )
{
	for( int bi = 0; bi < COLLISION_BULLET_MAX; bi++ )
	{
		if( pBulletCollection[ bi ] == Collision )
		{
			pBulletCollection[ bi ] = NULL;
			return true;
		}
	}
	return false;
}

//-------------------------------------
//	RegisterCollision_CoreObject コアリストに登録
//-------------------------------------
bool TmpCollisionChecker::RegisterCollision_CoreObject( CoreObject* Collision )
{
	for( int ci = 0; ci < COLLISION_CORE_MAX; ci++ )
	{
		if( pCoreCollection[ ci ] == NULL )
		{
			pCoreCollection[ ci ] = Collision;
			return true;
		}
	}
	return false;
}

//-------------------------------------
//	RegisterCollision_CoreObject コアリストから解除
//-------------------------------------
bool TmpCollisionChecker::DeregisterCollision_CoreObject( CoreObject* Collision )
{
	for( int ci = 0; ci < COLLISION_CORE_MAX; ci++ )
	{
		if( pCoreCollection[ ci ] == Collision )
		{
			pCoreCollection[ ci ] = NULL;
			return true;
		}
	}
	return false;
}

//-------------------------------------
//	CheckCollision 衝突チェック
//-------------------------------------
void TmpCollisionChecker::CheckCollision( void )
{
	CheckBulletVsCoreObj();
}


//-------------------------------------
//	CheckCollisionPlayerVsStageObj 
//  衝突チェック プレイヤーvsステージオブジェクト
//-------------------------------------
void TmpCollisionChecker::CheckBulletVsCoreObj( void )
{
	for( int bi = 0; bi < COLLISION_BULLET_MAX; bi++ )
	{
		for( int ci = 0; ci < COLLISION_CORE_MAX; ci++ )
		{
			if( pBulletCollection[ bi ] != NULL && pCoreCollection[ ci ] != NULL )
			{
				if( CollisionCheck::SphereVsSphere( pBulletCollection[ bi ]->ColSphape, pCoreCollection[ ci ]->ColShape ) )
				{
					pCoreCollection[ ci ]->Hit();
					Bullet_GetBullet( bi )->DisEnable();
				}
				else
				{
					// null
				}
			}
			else
			{
				// null
			}
		}
	}
}

//===============================================
//	Collision Collection
//===============================================

CollisionCollection* CollisionCollection::pInstance[ ENUM_COLLISION_SIDE_MAX ];
//-------------------------------------
//	GetInstance
//-------------------------------------

CollisionCollection* CollisionCollection::GetInstance( COLLISION_SIDE Idx )
{
	if( !pInstance[ Idx ] )
	{
		pInstance[ Idx ] = new CollisionCollection;
	}
	return pInstance[ Idx ];
}


//-------------------------------------
//	GetIsExist インスタンスが存在するか
//-------------------------------------
bool CollisionCollection::GetIsExist( COLLISION_SIDE Idx )
{
	if( !pInstance[ Idx ] )
	{ // インスタンスなし！
		return false;
	}
	return true;
}


//-------------------------------------
//	RegisterCollision_Bullet 弾リストに登録
//-------------------------------------
bool CollisionCollection::RegisterCollision_Bullet( ShapeSphere* Collision )
{
	for( int bi = 0; bi < COLLISION_BULLET_MAX; bi++ )
	{
		if( pBulletCollection[ bi ] == NULL )
		{
			pBulletCollection[ bi ] = Collision;
			return true;
		}
	}
	return false;
}

//-------------------------------------
//	DeregisterCollison_Bullet 弾リストから解除
//-------------------------------------
bool CollisionCollection::DeregisterCollison_Bullet( ShapeSphere* Collision )
{
	for( int bi = 0; bi < COLLISION_BULLET_MAX; bi++ )
	{
		if( pBulletCollection[ bi ] == Collision )
		{
			pBulletCollection[ bi ] = NULL;
			return true;
		}
	}
	return false;
}



//-------------------------------------
//	RegisterCollision_CoreObject コアリストに登録
//-------------------------------------
bool CollisionCollection::RegisterCollision_CoreObject( ShapeSphere* Collision )
{
	for( int bi = 0; bi < COLLISION_BULLET_MAX; bi++ )
	{
		if( pCoreCollection[ bi ] == Collision )
		{
			pCoreCollection[ bi ] = NULL;
			return true;
		}
	}
	return false;
}

//-------------------------------------
//	RegisterCollision_CoreObject コアリストから解除
//-------------------------------------
bool CollisionCollection::DeregisterCollision_CoreObject( ShapeSphere* Collision )
{
	for( int bi = 0; bi < COLLISION_BULLET_MAX; bi++ )
	{
		if( pCoreCollection[ bi ] == Collision )
		{
			pCoreCollection[ bi ] = NULL;
			return true;
		}
	}
	return false;
}



//===============================================
//	Collision Checker
//===============================================

void CheckCollisionPlayerVsBullet( void )
{

}
void CheckCollisionPlayerVsStageObj( void ); // プレイヤー vs 地形 // 名前が微妙
void CheckCollisionBulletVsStageObj( void );// 弾 vs 地形