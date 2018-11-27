//
//	CStageBlockList.cpp
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
#include"CStageBlockList.h"

//Class

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================


//===============================================
//	�֐�			function
//===============================================


//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
StageBlockList::StageBlockList(D3DXVECTOR3 DefaultPosition, ARMOR_DISCHARGING_TYPE DefaultType, int DefaultTextureIndex)
{
	pTop = NULL;
	this->DefaultPosition = DefaultPosition;
	this->DefaultType = DefaultType;
	this->DefaultTexture = DefaultTextureIndex;
}

//-------------------------------------
//	�u���b�N�ǉ��i��Έʒu�j
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
		pCurrent = pCurrent->pNext;		// �����Ɉړ�
	}
	pCurrent->pNext = pNewBlock;
	pNewBlock->pPrev = pCurrent;
}

//-------------------------------------
//	�u���b�N�ǉ��i���Έʒu�j
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
		pCurrent = pCurrent->pNext;		// �����Ɉړ�
	}
	pCurrent->pNext = pNewBlock;
	pNewBlock->pPrev = pCurrent;
}


//-------------------------------------
//	�u���b�N�ǉ��i��������j
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
		pCurrent = pCurrent->pNext;		// �����Ɉړ�
	}
	pCurrent->pNext = pNewBlock;
	pNewBlock->pPrev = pCurrent;
}

//-------------------------------------
//	�l�W�Ƀ��X�g�S�̂�o�^
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
