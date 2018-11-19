//
//	CCollisionChecker.cpp
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"

//class
#include "CCollisionChecker.h"
#include "CCollisionShape.h"

#include "Bullet.h"
#include "Player.h"
#include "CCoreObject.h"
//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
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
	// NULL������
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
//	RegisterCollision_Player �v���C�����X�g�ɓo�^
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
//	DeregisterCollision_Player �v���C�����X�g�������
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
//	RegisterCollision_Bullet �e���X�g�ɓo�^
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
//	DeregisterCollison_Bullet �e���X�g�������
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
//	RegisterCollision_CoreObject �R�A���X�g�ɓo�^
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
//	RegisterCollision_CoreObject �R�A���X�g�������
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
//	CheckCollision �Փ˃`�F�b�N
//-------------------------------------
void TmpCollisionChecker::CheckCollision( void )
{
	CheckBulletVsCoreObj();
}


//-------------------------------------
//	CheckCollisionPlayerVsStageObj 
//  �Փ˃`�F�b�N �v���C���[vs�X�e�[�W�I�u�W�F�N�g
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
//	GetIsExist �C���X�^���X�����݂��邩
//-------------------------------------
bool CollisionCollection::GetIsExist( COLLISION_SIDE Idx )
{
	if( !pInstance[ Idx ] )
	{ // �C���X�^���X�Ȃ��I
		return false;
	}
	return true;
}


//-------------------------------------
//	RegisterCollision_Bullet �e���X�g�ɓo�^
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
//	DeregisterCollison_Bullet �e���X�g�������
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
//	RegisterCollision_CoreObject �R�A���X�g�ɓo�^
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
//	RegisterCollision_CoreObject �R�A���X�g�������
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
void CheckCollisionPlayerVsStageObj( void ); // �v���C���[ vs �n�` // ���O������
void CheckCollisionBulletVsStageObj( void );// �e vs �n�`