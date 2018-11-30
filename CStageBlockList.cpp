//
//	CStageBlockList.cpp
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
#include"CStageBlockList.h"

//Class

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================


//===============================================
//	関数			function
//===============================================


//-------------------------------------
//	コンストラクタ
//-------------------------------------
StageBlockList::StageBlockList(D3DXVECTOR3 DefaultPosition, ARMOR_DISCHARGING_TYPE DefaultType, int DefaultTextureIndex)
{
	pTop = NULL;
	this->DefaultPosition = DefaultPosition;
	this->DefaultType = DefaultType;
	this->DefaultTexture = DefaultTextureIndex;
}

//-------------------------------------
//	ブロック追加（絶対位置）
//-------------------------------------
void StageBlockList::CreateBlockAbs(D3DXVECTOR3 position)
{
	if (pTop == NULL)
	{
		pTop = new StageBlock(&Transform(position, D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)), DefaultTexture, DefaultType);
		return;
	}

	StageBlock* pNewBlock = new StageBlock(&Transform(position, D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)), DefaultTexture, DefaultType);
	StageBlock* pCurrent = pTop;
	while (pCurrent->pNext != NULL)
	{
		pCurrent = pCurrent->pNext;		// 末尾に移動
	}
	pCurrent->pNext = pNewBlock;
	pNewBlock->pPrev = pCurrent;
}

//-------------------------------------
//	ブロック追加（相対位置）
//-------------------------------------
void StageBlockList::CreateBlockRel(D3DXVECTOR3 position)
{
	if (pTop == NULL)
	{
		pTop = new StageBlock(&Transform(this->DefaultPosition + position, D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)), DefaultTexture, DefaultType);
		return;
	}

	StageBlock* pNewBlock = new StageBlock(&Transform(this->DefaultPosition + position, D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)), DefaultTexture, DefaultType);
	StageBlock* pCurrent = pTop;
	while (pCurrent->pNext != NULL)
	{
		pCurrent = pCurrent->pNext;		// 末尾に移動
	}
	pCurrent->pNext = pNewBlock;
	pNewBlock->pPrev = pCurrent;
}


//-------------------------------------
//	ブロック追加（しっかり）
//-------------------------------------
void StageBlockList::CreateBlock(Transform* pTransform, int TextureIndex, ARMOR_DISCHARGING_TYPE type)
{
	if (pTop == NULL)
	{
		pTop = new StageBlock(pTransform, TextureIndex, type);
		return;
	}

	StageBlock* pNewBlock = new StageBlock(pTransform, TextureIndex, type);
	StageBlock* pCurrent = pTop;
	while (pCurrent->pNext != NULL)
	{
		pCurrent = pCurrent->pNext;		// 末尾に移動
	}
	pCurrent->pNext = pNewBlock;
	pNewBlock->pPrev = pCurrent;
}

//-------------------------------------
//	ネジにリスト全体を登録
//-------------------------------------
void StageBlockList::SetAll(CoreObject* pScrew)
{
	if (pTop == NULL)
		return;

	pScrew->SetArmor(pTop);
	pTop->transform.Position = pTop->transform.Position - pScrew->transform.GetWorldPosision();

	StageBlock *pCurrent = pTop;
	while (pCurrent->pNext != NULL)
	{
		pScrew->SetArmor(pCurrent->pNext);
		pCurrent->pNext->transform.Position = pCurrent->pNext->transform.Position - pScrew->transform.GetWorldPosision();
		pCurrent = pCurrent->pNext;
	}
}
