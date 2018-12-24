//
//	XModel.h
//		Author:HIROMASA IKEDA	DATE:2018/12/05
//===============================================
//	変更者 Changed By
//		Name:Minoda Takamasa	DATE:2018/10/23
//
//-----------------------------------------------

#pragma once
#ifndef XMODEL_H
#define XMODEL_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>

//================================================
//	マクロ定義	define
//================================================
#define MODEL_FILENAME_MAX (64)

#define MODEL_ADDRESS_LENGTH (60)		//Models/フォルダ内のモデルフォルダへのアドレス長
#define MODEL_NAME_LENGTH (30)			//モデルファイル名長
#define MODEL_TEXTURE_LENGTH (60)		//モデルファイル内でのテクスチャ名長

#define MODELS_FILE ("Models/")

//================================================
//	XModel 名前空間
//================================================
namespace NModel
{
	//モデル名
	const enum Name
	{
		BulletIndex,
		ScrewIndex,
		NAME_END,
		NONE
	};

	//Modelデータ
	struct Data
	{
		LPD3DXMESH pMesh;
		D3DMATERIAL9* pMaterials;
		LPDIRECT3DTEXTURE9* pTextures;
		DWORD dwNumMaterials;
	};

	//Path [Models/]内のモデルを指定して。
	struct Path
	{
		Name name;
		const char Address[MODEL_ADDRESS_LENGTH];	//モデルの入っているフォルダ
		const char Models[MODEL_NAME_LENGTH];		//モデルファイル名
	};

	//基本関数
	void Initialize();
	void Finalize();
	void Load(Path Path, Data* pIndex);
	void Release(Data* pIndex);
	void Render(const Data* pData);
	void Render(const Name name);
	void Render(const int name, Data* pIndex);
	Data* Get_Data(const Name name);
}
/*

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

	D3DXVECTOR3 vecPosition;		//Meshの中心位置？
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
*/

#endif