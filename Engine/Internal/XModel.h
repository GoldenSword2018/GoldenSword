//
//	XModel.h
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	変更者 Changed By
//		Name:Minoda Takamasa	DATE:2018/10/23
//
//-----------------------------------------------

#pragma once
#ifndef IKEDA_TEMPSOURCE_H
#define IKEDA_TEMPSOURCE_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>

//================================================
//	マクロ定義	define
//================================================
#define MODEL_FILENAME_MAX (64)

//================================================
//	列挙型		enum
//================================================
enum MeshIndex
{
	BulletIndex=0,
	ScrewIndex,
	MeshIndexMax
};

//================================================
//	構造体		struct/typedef
//================================================
typedef struct MeshTag
{
	LPD3DXMESH pMesh;
	D3DMATERIAL9* pMeshMaterials;
	LPDIRECT3DTEXTURE9* pMeshTextures;
	DWORD dwNumMaterials;

	D3DXVECTOR3 vecPosition;
	D3DXMATRIXA16 matWorld;

}MeshData;

//================================================
//	グローバル変数　global
//================================================


//================================================
//	関数		function
//================================================
void XModel_Initialize();	//初期化
void XModel_Finalize();		//終了

void NXModel_Load(MeshData *pMesh, char ModelFile[10], D3DXVECTOR3* pvecPosition);
void XModel_Load(MeshData *pMesh, LPSTR szXFileName, D3DXVECTOR3* pvecPosition);		//モデル読み込み
void XModel_Render(MeshData *pMesh);	//描画
void XModel_Render(MeshData *pMesh, D3DXMATRIXA16 mtx);
MeshData* GetMeshData(int MeshIndex);  //メッシュデータの取得


#endif