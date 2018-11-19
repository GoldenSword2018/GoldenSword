//
//	CCollisionChecker.h
//		Author:	Hashimoto Yuto DATE: 11/19/2018
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef _COLLISION_CHECKER_H_
#define _COLLISION_CHECKER_H_

//================================================
//	�C���N���[�h	include
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
//	�}�N����`	define
//================================================

#define COLLISION_BULLET_MAX    ( 1024 )
#define COLLISION_CORE_MAX      ( 1014 )
//================================================
//	�񋓌^		enum
//================================================


//================================================
//	�\����		struct/typedef
//================================================


//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�N���X		class
//================================================


//-------------------------------------
//	�N���X��
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
private: // �o�^�A�h���X vector�ł悢�ł� ------------------------------------------------------- CHANGE!>
	Player* pPlayer; // �����I�ɕ�����
	Bullet* pBulletCollection[ COLLISION_BULLET_MAX ];
	CoreObject* pCoreCollection[ COLLISION_CORE_MAX ];
public: // �o�^���� �ߒlbool����Ȃ��̂ł́H
	// �v���C���[
	bool RegisterCollision_Player( Player* Collision );
	bool DeregisterCollision_Player( Player* Collision );
	// �e
	bool RegisterCollision_Bullet( Bullet* Collision );
	bool DeregisterCollision_Bullet( Bullet* Collision );
	// �R�A
	bool RegisterCollision_CoreObject( CoreObject* Collision );
	bool DeregisterCollision_CoreObject( CoreObject* Collision );
public:
	void CheckCollision( void );
private:
	void CheckBulletVsCoreObj( void );
	// void CheckCollisionPlayerVsStageObj( void ); // �v���C���[ vs �n�` // ���O������
	// void CheckCollisionBulletVsStageObj( void );// �e vs �n�`

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
	ShapeOBB* pPlayer; // �����I�ɕ�����
	ShapeSphere* pBulletCollection[ COLLISION_BULLET_MAX ];
	ShapeSphere* pCoreCollection[ COLLISION_CORE_MAX ];
public: // �o�^���� �ߒlbool����Ȃ��̂ł́H
	bool RegisterCollision_CoreObject( ShapeSphere* Collision );
	bool DeregisterCollision_CoreObject( ShapeSphere* Collision );
	bool RegisterCollision_Bullet( ShapeSphere* Collision );
	bool DeregisterCollison_Bullet( ShapeSphere* Collision );
	
};

#endif