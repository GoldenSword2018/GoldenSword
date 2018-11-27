//
//	CStageBlockList.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CSTAGE_BLOCK_LIST_H
#define CSTAGE_BLOCK_LIST_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include"CStageBlock.h"
#include"CCoreObject.h"

//Class

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
//	クラス名
//-------------------------------------
class StageBlockList
{
private:
	StageBlock* pTop;
	D3DXVECTOR3 DefaultPosition;
	ARMOR_DISCHARGING_TYPE DefaultType;
	int DefaultTexture;

public:
	StageBlockList(D3DXVECTOR3 DefaultPosition, ARMOR_DISCHARGING_TYPE DefaultType, int DefaultTextureIndex);
	void CreateBlockAbs(D3DXVECTOR3 position);
	void CreateBlockRel(D3DXVECTOR3 position);
	void CreateBlock(Transform* pTransform, int TextureIndex, ARMOR_DISCHARGING_TYPE type);
	void SetAll(CoreObject* pScrew);
};

#endif