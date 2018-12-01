//
//	CStageBlock.cpp
//		Author:YU NISHIMAKI		DATE:2018/11/13
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"
#include<d3dx9.h>
#include"System.h"
#include"Texture.h"

//class
#include"CStageBlock.h"
#include "CCollisionChecker.h"

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�\���̐錾	struct
//===============================================

//===============================================
//	�O���[�o���ϐ�	global
//===============================================

// ���_���X�g
const StageBlockVertex g_StageVertex[] = {
	{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2(0.0f / 6, 0.0f) }, // ���
	{ D3DXVECTOR3(0.5f , 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2(1.0f / 6, 0.0f) },
	{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2(0.0f / 6, 1.0f) },
	{ D3DXVECTOR3(0.5f , 0.5f, -0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2(1.0f / 6, 1.0f) },

	{ D3DXVECTOR3(-0.5f, 0.5f , -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 1.0f) / 6, 0.0f) }, // ��O��
	{ D3DXVECTOR3(0.5f , 0.5f , -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 1.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 1.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(0.5f , -0.5f, -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 1.0f) / 6, 1.0f) },

	{ D3DXVECTOR3(0.5f, 0.5f, -0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 2.0f) / 6, 0.0f) }, // �E��
	{ D3DXVECTOR3(0.5f, 0.5f, 0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 2.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 2.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 2.0f) / 6, 1.0f) },

	{ D3DXVECTOR3(0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 3.0f) / 6, 0.0f) }, // ����
	{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 3.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 3.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 3.0f) / 6, 1.0f) },

	{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 4.0f) / 6, 0.0f) }, // ����
	{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 4.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 4.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 4.0f) / 6, 1.0f) },

	{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 5.0f) / 6, 0.0f) }, // ����
	{ D3DXVECTOR3(0.5f , -0.5f, -0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 5.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 5.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(0.5f , -0.5f, 0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 5.0f) / 6, 1.0f) },
};


//===============================================
//	StageBlock�N���X		class
//===============================================

//-------------------------------------
//	�ÓI�����o�ϐ��̏�����	static
//-------------------------------------
LPDIRECT3DVERTEXBUFFER9 StageBlock::pVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 StageBlock::pIndexBuffer = NULL;

StageBlockVertex *StageBlock::pVertex = NULL;
WORD *StageBlock::pVertexIndex = NULL;

//-------------------------------------
//	�������i���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̊m�ہj
//-------------------------------------
void StageBlock::Initialize()
{
	if (pVertexBuffer || pIndexBuffer)
		return;

	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();
	pDevice->CreateVertexBuffer(sizeof(StageBlockVertex) * NUM_STAGE_VERTEX, D3DUSAGE_WRITEONLY, FVF_STAGE_BLOCK_VERTEX, D3DPOOL_MANAGED, &pVertexBuffer, NULL);
	pDevice->CreateIndexBuffer(sizeof(WORD) * NUM_STAGE_VERTEX * 3 / 2, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL);
	pVertexBuffer->Lock(0, 0, (void **)&pVertex, 0);
	pIndexBuffer->Lock(0, 0, (void **)&pVertexIndex, 0);

	for (int i = 0; i < NUM_STAGE_VERTEX; i++)
	{
		pVertex[i] = g_StageVertex[i];
	}

	int Num_Face = NUM_STAGE_VERTEX / 4;
	for (int i = 0; i < Num_Face; i++)
	{
		pVertexIndex[i * 6 + 0] = (WORD)i * 4 + 0;
		pVertexIndex[i * 6 + 1] = (WORD)i * 4 + 1;
		pVertexIndex[i * 6 + 2] = (WORD)i * 4 + 2;
		pVertexIndex[i * 6 + 3] = (WORD)i * 4 + 1;
		pVertexIndex[i * 6 + 4] = (WORD)i * 4 + 3;
		pVertexIndex[i * 6 + 5] = (WORD)i * 4 + 2;
	}
	pVertexBuffer->Unlock();
	pIndexBuffer->Unlock();
}

//-------------------------------------
//	�I�������i���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̉���j
//-------------------------------------
void StageBlock::Finalize()
{
	if (pVertexBuffer)
	{
		pVertexBuffer->Release();
		pVertexBuffer = NULL;
	}
	if (pIndexBuffer)
	{
		pIndexBuffer->Release();
		pIndexBuffer = NULL;
	}
}


//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
StageBlock::StageBlock(Transform* pTransform, int TextureIndex) 
:
	ArmorObject(pTransform, FALL),
	ColShape( &transform, &transform.Rotation, &transform.Scale )
{
	pTexture = Texture_GetTexture(TextureIndex);
	TmpCollisionChecker::GetInstance()->RegisterCollision_StageBlock( this );
	pPrev = NULL;
	pNext = NULL;
}

StageBlock::StageBlock(Transform* pTransform, int TextureIndex, ARMOR_DISCHARGING_TYPE type)
	: 
	ArmorObject(pTransform, type),
	ColShape(&transform, &transform.Rotation, &transform.Scale)
{
	pTexture = Texture_GetTexture(TextureIndex);
	TmpCollisionChecker::GetInstance()->RegisterCollision_StageBlock( this );
	pPrev = NULL;
	pNext = NULL;
}

//-------------------------------------
//	�`��
//-------------------------------------
void StageBlock::Render()
{ 
	// 11/28����q���e�̃X�P�[�����󂯌p���ł��܂��̂ō��W�𑊑Έʒu�ɐݒ肷�邾���ł͕s�\��. 
	// �e��Scale�i�Ȃ����A��]�Ȃǈꕔ�̗v�f�j�̉e�����󂯂Ȃ��悤�ɂ���K�v������i�H�j
	LPDIRECT3DDEVICE9 pDevice = System_GetDevice(); 

	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxTranslation;
	D3DXMATRIX mtxScaling;

	D3DXMatrixTranslation(&mtxTranslation, transform.GetWorldPosision().x, transform.GetWorldPosision().y, transform.GetWorldPosision().z);
	D3DXMatrixScaling(&mtxScaling, transform.Scale.x, transform.Scale.y, transform.Scale.z);

	mtxWorld = mtxScaling * mtxTranslation;

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pDevice->SetTexture(0, pTexture);
	pDevice->SetFVF(FVF_STAGE_BLOCK_VERTEX);
	pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(StageBlockVertex));
	pDevice->SetIndices(pIndexBuffer);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_STAGE_VERTEX, 0, NUM_STAGE_VERTEX * 2 / 4);
	ColShape.DebugDraw();
}