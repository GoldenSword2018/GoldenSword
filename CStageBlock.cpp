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

//===============================================
//	�}�N����`		define
//===============================================
#define FVF_VERTEX3D	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// �\����STAGE_BLOCK_VERTEX��FVF�t���O
#define NUM_VERTEX		(24)

//===============================================
//	�\���̐錾	struct
//===============================================
typedef struct STAGE_BLOCK_VERTEX_tag
{
	D3DXVECTOR3 Position;			// ���_���W
	D3DXVECTOR3 Normal;				// �@���x�N�g��
	D3DCOLOR Color;					// ���_�F
	D3DXVECTOR2 TexCoord;			// �e�N�X�`�����W
}STAGE_BLOCK_VERTEX;

//===============================================
//	�O���[�o���ϐ�	global
//===============================================
// ���_���X�g
STAGE_BLOCK_VERTEX g_StageVertex[] = {
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

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;		// ���_�o�b�t�@
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;		// �C���f�b�N�X�o�b�t�@

static STAGE_BLOCK_VERTEX *g_pVertex = NULL;
static WORD *g_pVertexIndex = NULL;


//===============================================
//	�֐�	function
//===============================================


//-------------------------------------
//	������
//-------------------------------------
void StageBlock_Initialize()
{
	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();
	pDevice->CreateVertexBuffer(sizeof(STAGE_BLOCK_VERTEX) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	pDevice->CreateIndexBuffer(sizeof(WORD) * NUM_VERTEX * 3 / 2, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	g_pVertexBuffer->Lock(0, 0, (void **)&g_pVertex, 0);
	g_pIndexBuffer->Lock(0, 0, (void **)&g_pVertexIndex, 0);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		g_pVertex[i] = g_StageVertex[i];
	}

	int Num_Face = NUM_VERTEX / 4;
	for (int i = 0; i < Num_Face; i++)
	{
		g_pVertexIndex[i * 6 + 0] = (WORD)i * 4 + 0;
		g_pVertexIndex[i * 6 + 1] = (WORD)i * 4 + 1;
		g_pVertexIndex[i * 6 + 2] = (WORD)i * 4 + 2;
		g_pVertexIndex[i * 6 + 3] = (WORD)i * 4 + 1;
		g_pVertexIndex[i * 6 + 4] = (WORD)i * 4 + 3;
		g_pVertexIndex[i * 6 + 5] = (WORD)i * 4 + 2;
	}
	g_pVertexBuffer->Unlock();
	g_pIndexBuffer->Unlock();
}

//===============================================
//	StageBlock�N���X		class
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
StageBlock::StageBlock(Transform* pTransform, int TextureIndex) :GameObject(pTransform)
{
	pTexture = Texture_GetTexture(TextureIndex);
}

//-------------------------------------
//	�`��
//-------------------------------------
void StageBlock::Render()
{
	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxTranslation;
	D3DXMATRIX mtxScaling;

	D3DXMatrixTranslation(&mtxTranslation, transform.Position.x, transform.Position.y, transform.Position.z);
	D3DXMatrixScaling(&mtxScaling, transform.Scale.x, transform.Scale.y, transform.Scale.z);

	mtxWorld = mtxScaling * mtxTranslation;

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pDevice->SetTexture(0, pTexture);
	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(STAGE_BLOCK_VERTEX));
	pDevice->SetIndices(g_pIndexBuffer);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_VERTEX * 2 / 4);
}