//
//	CEnemy.h
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CENEMY_H
#define CENEMY_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include<vector>

//Class
#include"CGameObject.h"
#include"CCoreObject.h"
#include"CArmorObject.h"
#include"CBodyObject.h"

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


//-------------------------------------
//	Enemy クラス
//-------------------------------------
class Enemy:public GameObject
{
private:
	std::vector<BodyObject*> pBody_Index;
public:

	Enemy(Transform* pTransform) :Enemy(pTransform, &Texture()) {};
	Enemy(Transform* pTransform,Texture* pTexture);

	~Enemy();

	void Add_Body(BodyObject* pBodyObject);
};

#endif