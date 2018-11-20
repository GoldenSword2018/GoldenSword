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
#include "CStageBlock.h"
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

	for( int bi = 0; bi < BULLET_MAX; bi++ )
	{
		pBulletCollection[ bi ] = NULL;
	}

	for( int ci = 0; ci < COLLISION_CORE_MAX; ci++ )
	{
		pCoreCollection[ ci ] = NULL;
	}
	
	for( int si = 0; si < COLLISION_STAGEBLOCK_MAX; si++ )
	{
		pStageBlock[ si ] = NULL;
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
	for( int bi = 0; bi < BULLET_MAX; bi++ )
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
	for( int bi = 0; bi < BULLET_MAX; bi++ )
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
//	DeregisterCollision_CoreObject �R�A���X�g�������
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
//	RegisterCollision_StageBlock �n�`���X�g�������
//-------------------------------------
bool TmpCollisionChecker::RegisterCollision_StageBlock( StageBlock* pNewStageBlock )
{
	for( int si = 0; si < COLLISION_STAGEBLOCK_MAX; si++ )
	{
		if( pStageBlock[ si ] == NULL )
		{
			pStageBlock[ si ] = pNewStageBlock;
			return true;
		}
	}
	return false;
}

//-------------------------------------
//	DeregisterCollision_StageBlock �n�`���X�g�������
//-------------------------------------
bool TmpCollisionChecker::DeregisterCollision_StageBlock( StageBlock* pNewStageBlock )
{
	for( int si = 0; si < COLLISION_STAGEBLOCK_MAX; si++ )
	{
		if( pStageBlock[ si ] == pNewStageBlock )
		{
			pStageBlock[ si ] = NULL;
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
	CheckCollisionPlayerVsStageObj();
}


//-------------------------------------
//	CheckBulletVsCoreObj 
//  �����蔻��`�F�b�N �evs�X�R�A�I�u�W�F�N�g
//-------------------------------------
void TmpCollisionChecker::CheckBulletVsCoreObj( void )
{
	for( int bi = 0; bi < BULLET_MAX; bi++ )
	{
		for( int ci = 0; ci < COLLISION_CORE_MAX; ci++ )
		{
			if( pBulletCollection[ bi ] != NULL && pCoreCollection[ ci ] != NULL )
			{
				if( CollisionCheck::SphereVsSphere( pBulletCollection[ bi ]->ColSphape, pCoreCollection[ ci ]->ColShape ) )
				{
					pCoreCollection[ ci ]->Hit();
					Bullet_GetBullet( bi )->DisEnable();  // ------------------------------------------------------------------------------------------�����̏����̂��߂�Hit�������̏����Ƃ����������K�v����̂ł� CHANGE!>
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


void TmpCollisionChecker::CheckCollisionPlayerVsStageObj( void )
{
	for( int si = 0; si < COLLISION_STAGEBLOCK_MAX; si++ )
	{
		if( pStageBlock[ si ] != NULL && pPlayer != NULL )
		{
			if( CollisionCheck::OBBVsOBB( pStageBlock[ si ]->ColShape, pPlayer->ColShape ) )
			{ // Hit
				pPlayer->ColShape.Color = D3DCOLOR_RGBA( 255, 0, 0, 255 );
			}
			else
			{ // No Hit
				// null
			}
		}
		else
		{ // Invalid pointer
			 // null
		}
	}
}