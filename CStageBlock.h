//
//	CStageBlock.h
//		Author:YU NISHIMAKI		DATE:2018/11/13
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CSTAGE_BLOCK_H
#define CSTAGE_BLOCK_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>

//Class
#include"CGameObject.h"
#include"CArmorObject.h"


// 当たり判定
class ShapeOBB;

//================================================
//	マクロ定義	define
//================================================
#define NUM_STAGE_VERTEX		(24)
#define FVF_STAGE_BLOCK_VERTEX	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// 構造体StageBlockVertexのFVFフラグ


//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================
typedef struct StageBlockVertex_tag
{
	D3DXVECTOR3 Position;			// 頂点座標
	D3DXVECTOR3 Normal;				// 法線ベクトル
	D3DCOLOR Color;					// 頂点色
	D3DXVECTOR2 TexCoord;			// テクスチャ座標
}StageBlockVertex;


//================================================
//	グローバル変数　global
//================================================


//================================================
//	クラス		class
//================================================


//-------------------------------------
//	StageBlockクラス
//-------------------------------------
class StageBlock:public ArmorObject
{
private:
	LPDIRECT3DTEXTURE9 pTexture;

	static LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;			// 頂点バッファ
	static LPDIRECT3DINDEXBUFFER9 pIndexBuffer;				// インデックスバッファ

	static StageBlockVertex *pVertex;
	static WORD *pVertexIndex;
public:
	// コンストラクタ
	StageBlock(Transform *pTransform, int TextureIndex);
	StageBlock(Transform* pTransform, int TextureIndex, ARMOR_DISCHARGING_TYPE type);

	static void Initialize();								// 初期化(頂点バッファ、インデックスバッファの確保)
	static void Finalize();									// 終了処理(頂点バッファ、インデックスバッファの解放)
public:
	void Render();
	ShapeOBB ColShape;

};


#endif