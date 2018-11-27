//
//	CStageBlockList.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CSTAGE_BLOCK_LIST_H
#define CSTAGE_BLOCK_LIST_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include"CStageBlock.h"
#include"CCoreObject.h"

//Class

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


//-------------------------------------
//	�N���X��
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