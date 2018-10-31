//
//	XModel.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	�ύX�� Changed By 
//		Name:Minoda Takamasa DATE:2018/10/23
//		Name:HIROMASA IKEDA	 DATE:2018/10/31
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
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
//	�}�N����`		define
//===============================================
#define MESH_AMOUNT (1)
#define MESH_MAX (1)

#define MODELS_FILE ("Models/")

//===============================================
//	�O���[�o���ϐ�	global
//===============================================

MeshData g_Mesh[MeshIndexMax]; //���b�V���f�[�^���X�g

//===============================================
//	�֐�			function
//===============================================

//-------------------------------------
//	�V�����ǂݍ��� �����ɂ̓��f���������Ă�t�@�C�����w��B
//-------------------------------------
void NXModel_Load(MeshData *pMesh, char ModelFile[10] , D3DXVECTOR3* pvecPosition)
{
	HRESULT hr;
	char FilePath[60] = {"\0"};				//�����t�@�C���p�X

	strcat(FilePath,MODELS_FILE);			//���f���ۑ��t�@�C��
	strcat(FilePath,ModelFile);
	strcat(FilePath, "/*.x");

	WIN32_FIND_DATA WindData = {};			//���������f�[�^

	HANDLE hFind = FindFirstFile(FilePath,&WindData);	//�f�[�^��������

	if( hFind == INVALID_HANDLE_VALUE)
	{
		strcat(FilePath,"\n��������܂���B");
		MessageBox(*System_GethWnd(),FilePath,"�G���[",MB_OK);
		DestroyWindow(*System_GethWnd());
		return;
	}

	strcpy(FilePath,"\0");					//�����񏉊���

	//���f���̃p�X���쐬
	strcat(FilePath, MODELS_FILE);			
	strcat(FilePath, ModelFile);
	strcat(FilePath, "/");
	strcat(FilePath, WindData.cFileName);

	//	X���f�� �ǂݍ���
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
		strcat(ErrorText,"\n���f���f�[�^���ǂݍ��߂܂���ł����B");

		MessageBox(*System_GethWnd(),ErrorText,"�G���[",MB_OK);
		DestroyWindow(*System_GethWnd());
		return;
	}

	//	���f���e�N�X�`���@�ǂݍ���
	//--------------------------

	strcpy(FilePath,"\0");	//������
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
			//�e�N�X�`���̃p�X
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
				strcat(ErrorText,"\n�e�N�X�`���ǂݍ��݂Ɏ��s���܂����B");

				MessageBox(NULL, ErrorText, "�G���[", MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();

	return;
}

//-------------------------------------
//	�ǂݍ���
//-------------------------------------
void XModel_Load(MeshData *pMesh, LPSTR szXFileName, D3DXVECTOR3* pvecPosition)
{
	HRESULT hr;

	// ���b�V���̏����ʒu
	memcpy(&pMesh->vecPosition, pvecPosition, sizeof(D3DXVECTOR3));

	// X�t�@�C�����烁�b�V�������[�h����	
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	hr = D3DXLoadMeshFromX(
		szXFileName,				//�ǂݍ��ރt�@�C����
		D3DXMESH_SYSTEMMEM,	//�e�ʏグ�@D3DXMESH_32BIT
		System_GetDevice(),
		NULL,
		&pD3DXMtrlBuffer,
		NULL,
		&pMesh->dwNumMaterials,
		&pMesh->pMesh
	);

	if(FAILED(hr))
	{
		MessageBox(*System_GethWnd(),"���f���̓ǂݍ��݂Ɏ��s���܂����B","�ǂݍ��ݎ��s",MB_OK);
		DestroyWindow(*System_GethWnd());
		return;
	}

	/*	�œK��
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
				MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();

	return;
}

//-------------------------------------
//	�`��
//-------------------------------------	
void XModel_Render(MeshData *pMesh)
{
	MeshData *pMeshData = pMesh;
	System_GetDevice()->SetTransform(D3DTS_WORLD, &pMeshData->matWorld);

	//�}�e���A���̐��������[�v������
	for (DWORD i = 0; i < pMesh->dwNumMaterials; i++)
	{
		//�}�e���A���ݒ�
		System_GetDevice()->SetMaterial(&pMesh->pMeshMaterials[i]);
		//�e�N�X�`���ݒ�
		System_GetDevice()->SetTexture(0, pMesh->pMeshTextures[i]);
		//�����_�����O
		pMesh->pMesh->DrawSubset(i);
	}
}

void XModel_Render(MeshData *pMesh, D3DXMATRIXA16 mtx)
{
	MeshData *pMeshData = pMesh;
	D3DXMATRIXA16 mtxWorld = pMeshData->matWorld * mtx;
	System_GetDevice()->SetTransform(D3DTS_WORLD, &mtx);

	//�}�e���A���̐��������[�v������
	for (DWORD i = 0; i < pMesh->dwNumMaterials; i++)
	{
		//�}�e���A���ݒ�
		System_GetDevice()->SetMaterial(&pMesh->pMeshMaterials[i]);
		//�e�N�X�`���ݒ�
		System_GetDevice()->SetTexture(0, pMesh->pMeshTextures[i]);
		//�����_�����O
		pMesh->pMesh->DrawSubset(i);
	}
}

//-------------------------------------
//	������
//-------------------------------------
void XModel_Initialize()
{
	NXModel_Load(GetMeshData(BulletIndex), "bullet", &D3DXVECTOR3(0, 0, 0));
	NXModel_Load(GetMeshData(ScrewIndex), "neji", &D3DXVECTOR3(0, 0, 0));
}

//-------------------------------------
//	�I��
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
