//
//	TestObj.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef _TESTOBJ_H_
#define _TESTOBJ_H_

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"

//Class
#include "CGameObject.h"
#include "CTransform.h"
#include "CCollisionShape.h"
//================================================
//	�}�N����`	define
//================================================


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

class TestObj : public GameObject
{
public:
	ShapeOBB ColShape;
	D3DXVECTOR3 Velocity;
	bool isOnGround;
public:
	TestObj( Transform* pTransform );
public:
	void Update( void );
	void Render( void );
};

class TestEnvObj : public GameObject
{
public:
	ShapeOBB ColShape;
public:
	TestEnvObj( );
public:
	void Update( void );
	void Render( void );
};
//-------------------------------------
//	�N���X��
//-------------------------------------

#endif