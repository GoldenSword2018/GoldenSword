//
//	XModel.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	変更者 Changed By 
//		Name:Minoda Takamasa DATE:2018/10/23
//		Name:HIROMASA IKEDA	 DATE:2018/10/31
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"
#include<d3dx9.h>
#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<Windows.h>

#include"XModel.h"
#include"System.h"
#include "Lighting.h"

//Class

//===============================================
//	マクロ定義		define
//===============================================
#define MESH_AMOUNT (1)
#define MESH_MAX (1)

#define MODELS_FILE ("Models/")

//===============================================
//	グローバル変数	global
//===============================================

MeshData g_Mesh[MeshIndexMax]; //メッシュデータリスト

//===============================================
//	関数			function
//===============================================

//-------------------------------------
//	新しい読み込み 引数にはモデルが入ってるファイルを指定。
//-------------------------------------
void NXModel_Load(MeshData *pMesh, char ModelFile[10] , D3DXVECTOR3* pvecPosition)
{
	HRESULT hr;
	char FilePath[60] = {"\0"};				//検索ファイルパス

	strcat(FilePath,MODELS_FILE);			//モデル保存ファイル
	strcat(FilePath,ModelFile);
	strcat(FilePath, "/*.x");

	WIN32_FIND_DATA WindData = {};			//見つかったデータ

	HANDLE hFind = FindFirstFile(FilePath,&WindData);	//データを見つける

	if( hFind == INVALID_HANDLE_VALUE)
	{
		strcat(FilePath,"\nが見つかりません。");
		MessageBox(*System_GethWnd(),FilePath,"エラー",MB_OK);
		DestroyWindow(*System_GethWnd());
		return;
	}

	strcpy(FilePath,"\0");					//文字列初期化

	//モデルのパスを作成
	strcat(FilePath, MODELS_FILE);			
	strcat(FilePath, ModelFile);
	strcat(FilePath, "/");
	strcat(FilePath, WindData.cFileName);

	//	Xモデル 読み込む
	//--------------------------

	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	hr = D3DXLoadMeshFromX(
		FilePath,
		D3DXMESH_SYSTEMMEM,
		System_GetDevice(),
		NULL,
		&pD3DXMtrlBuffer,
		NULL,
		&pMesh->dwNumMaterials,
		&pMesh->pMesh
	);

	if(FAILED(hr))
	{
		char ErrorText[100] = {"\0"};
		strcat(ErrorText,FilePath);
		strcat(ErrorText,"\nモデルデータが読み込めませんでした。");

		MessageBox(*System_GethWnd(),ErrorText,"エラー",MB_OK);
		DestroyWindow(*System_GethWnd());
		return;
	}

	//	モデルテクスチャ　読み込む
	//--------------------------

	strcpy(FilePath,"\0");	//初期化
	strcat(FilePath, MODELS_FILE);			
	strcat(FilePath, ModelFile);
	strcat(FilePath, "/");

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pMesh->pMeshMaterials = new D3DMATERIAL9[pMesh->dwNumMaterials];
	pMesh->pMeshTextures = new LPDIRECT3DTEXTURE9[pMesh->dwNumMaterials];

	D3DXMATERIAL* pD3DXMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	for (DWORD i = 0; i < pMesh->dwNumMaterials; i++)
	{
		pMesh->pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		pMesh->pMeshMaterials[i].Ambient = pMesh->pMeshMaterials[i].Diffuse;
		pMesh->pMeshTextures[i] = NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			//テクスチャのパス
			char TexturePath[200] = { "\0" };
			strcat(TexturePath,FilePath);
			strcat(TexturePath, d3dxMaterials[i].pTextureFilename);

			hr = D3DXCreateTextureFromFile(
				System_GetDevice(),
				TexturePath,
				&pMesh->pMeshTextures[i]
			);

			if (FAILED(hr))
			{
				char ErrorText[200] = { "\0" };
				strcat(ErrorText,TexturePath);
				strcat(ErrorText,"\nテクスチャ読み込みに失敗しました。");

				MessageBox(NULL, ErrorText, "エラー", MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();

	return;
}

//-------------------------------------
//	読み込み
//-------------------------------------
void XModel_Load(MeshData *pMesh, LPSTR szXFileName, D3DXVECTOR3* pvecPosition)
{
	HRESULT hr;

	// メッシュの初期位置
	memcpy(&pMesh->vecPosition, pvecPosition, sizeof(D3DXVECTOR3));

	// Xファイルからメッシュをロードする	
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	hr = D3DXLoadMeshFromX(
		szXFileName,				//読み込むファイル名
		D3DXMESH_SYSTEMMEM,	//容量上げ　D3DXMESH_32BIT
		System_GetDevice(),
		NULL,
		&pD3DXMtrlBuffer,
		NULL,
		&pMesh->dwNumMaterials,
		&pMesh->pMesh
	);

	if(FAILED(hr))
	{
		MessageBox(*System_GethWnd(),"モデルの読み込みに失敗しました。","読み込み失敗",MB_OK);
		DestroyWindow(*System_GethWnd());
		return;
	}

	/*	最適化
	hr = g_pD3DXMesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)g_pD3DXAdjacenecyBuffer->GetBufferPointer(),NULL,NULL,NULL
	);
	*/

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pMesh->pMeshMaterials = new D3DMATERIAL9[pMesh->dwNumMaterials];
	pMesh->pMeshTextures = new LPDIRECT3DTEXTURE9[pMesh->dwNumMaterials];

	D3DXMATERIAL* pD3DXMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	for (DWORD i = 0; i < pMesh->dwNumMaterials; i++)
	{
		pMesh->pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		pMesh->pMeshMaterials[i].Ambient = pMesh->pMeshMaterials[i].Diffuse;
		pMesh->pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(System_GetDevice(),
				d3dxMaterials[i].pTextureFilename,
				&pMesh->pMeshTextures[i])))
			{
				MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();

	return;
}

//-------------------------------------
//	描画
//-------------------------------------	
void XModel_Render(MeshData *pMesh)
{
	MeshData *pMeshData = pMesh;
	System_GetDevice()->SetTransform(D3DTS_WORLD, &pMeshData->matWorld);

	//マテリアルの数だけループさせる
	for (DWORD i = 0; i < pMesh->dwNumMaterials; i++)
	{
		//マテリアル設定
		System_GetDevice()->SetMaterial(&pMesh->pMeshMaterials[i]);
		//テクスチャ設定
		System_GetDevice()->SetTexture(0, pMesh->pMeshTextures[i]);
		//レンダリング
		pMesh->pMesh->DrawSubset(i);
	}
}

void XModel_Render(MeshData *pMesh, D3DXMATRIXA16 mtx)
{
	MeshData *pMeshData = pMesh;
	D3DXMATRIXA16 mtxWorld = pMeshData->matWorld * mtx;
	System_GetDevice()->SetTransform(D3DTS_WORLD, &mtx);

	//マテリアルの数だけループさせる
	for (DWORD i = 0; i < pMesh->dwNumMaterials; i++)
	{
		//マテリアル設定
		System_GetDevice()->SetMaterial(&pMesh->pMeshMaterials[i]);
		//テクスチャ設定
		System_GetDevice()->SetTexture(0, pMesh->pMeshTextures[i]);
		//レンダリング
		pMesh->pMesh->DrawSubset(i);
	}
}

//-------------------------------------
//	初期化
//-------------------------------------
void XModel_Initialize()
{
	NXModel_Load(GetMeshData(BulletIndex), "bullet", &D3DXVECTOR3(0, 0, 0));
	NXModel_Load(GetMeshData(ScrewIndex), "neji", &D3DXVECTOR3(0, 0, 0));
}

//-------------------------------------
//	終了
//-------------------------------------
void XModel_Finalize() 
{
	for (DWORD i = 0; i < MESH_MAX; i++)
	{
		delete g_Mesh[i].pMeshTextures;
		delete g_Mesh[i].pMeshMaterials;
		g_Mesh[i].pMesh->Release();
	}
}

MeshData* GetMeshData(int MeshIndex)
{
	return &g_Mesh[MeshIndex];
}
