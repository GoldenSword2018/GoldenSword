//
//	CStageBlock.h
//		Author:YU NISHIMAKI		DATE:2018/11/13
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CSTAGE_BLOCK_H
#define CSTAGE_BLOCK_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>

//Class
#include"CGameObject.h"
#include"CArmorObject.h"


// �����蔻��
class ShapeOBB;

//================================================
//	�}�N����`	define
//================================================
#define NUM_STAGE_VERTEX		(24)
#define FVF_STAGE_BLOCK_VERTEX	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// �\����StageBlockVertex��FVF�t���O


//================================================
//	�񋓌^		enum
//================================================


//================================================
//	�\����		struct/typedef
//================================================
typedef struct StageBlockVertex_tag
{
	D3DXVECTOR3 Position;			// ���_���W
	D3DXVECTOR3 Normal;				// �@���x�N�g��
	D3DCOLOR Color;					// ���_�F
	D3DXVECTOR2 TexCoord;			// �e�N�X�`�����W
}StageBlockVertex;


//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�N���X		class
//================================================


//-------------------------------------
//	StageBlock�N���X
//-------------------------------------
class StageBlock:public ArmorObject
{
private:
	LPDIRECT3DTEXTURE9 pTexture;

	static LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;			// ���_�o�b�t�@
	static LPDIRECT3DINDEXBUFFER9 pIndexBuffer;				// �C���f�b�N�X�o�b�t�@

	static StageBlockVertex *pVertex;
	static WORD *pVertexIndex;
public:
	// �R���X�g���N�^
	StageBlock(Transform *pTransform, int TextureIndex);
	StageBlock(Transform* pTransform, int TextureIndex, ARMOR_DISCHARGING_TYPE type);

	static void Initialize();								// ������(���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̊m��)
	static void Finalize();									// �I������(���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̉��)
public:
	void Render();
	ShapeOBB ColShape;

};


#endif