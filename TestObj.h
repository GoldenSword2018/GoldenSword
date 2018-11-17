//
//	TestObj.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef _TESTOBJ_H_
#define _TESTOBJ_H_

//================================================
//	インクルード	include
//================================================
#include"common.h"

//Class
#include "CGameObject.h"
#include "CTransform.h"
#include "CCollisionShape.h"
//================================================
//	マクロ定義	define
//================================================


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
//	クラス名
//-------------------------------------

#endif