//
//	XModel.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	�ύX�� Changed By 
//		Name:Minoda Takamasa DATE:2018/10/23
//		Name:HIROMASA IKEDA	 DATE:2018/12/05
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#include"common.h"
#include<d3dx9.h>
#include<string.h>
#include<Windows.h>

#include"XModel.h"
#include"System.h"

//Class

//===============================================
//	�}�N����`		define
//===============================================
#define MESH_AMOUNT (1)
#define MESH_MAX (1)

//===============================================
//	�O���[�o���ϐ�	global
//===============================================

//MeshData g_Mesh[MeshIndexMax]; //���b�V���f�[�^���X�g

//================================================
//	XModel ���O���
//================================================
namespace NModel
{
	//�f�[�^�ۑ�
	Data Index[Name::NAME_END];

	//===============================================
	//	��{�֐�
	//===============================================

	//�ǂݍ���
	void Load(Path path,Data* pIndex)
	{
		HRESULT hr;
		char FilePath[MODEL_ADDRESS_LENGTH + 20] = {"\0"};

		strcat(FilePath,MODELS_FILE);
		strcat(FilePath,path.Address);
		strcat(FilePath, "/");
		strcat(FilePath,path.Models);

		LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

		hr = D3DXLoadMeshFromX(
			FilePath,
			D3DXMESH_SYSTEMMEM,
			System_GetDevice(),
			NULL,
			&pD3DXMtrlBuffer,
			NULL,
			&pIndex->dwNumMaterials,
			&pIndex->pMesh
		);

		if (FAILED(hr))
		{
			char ErrorText[100] = { "\0" };
			strcat(ErrorText, FilePath);
			strcat(ErrorText, "\n���f���f�[�^���ǂݍ��߂܂���ł����B");

			MessageBox(*System_GethWnd(), ErrorText, "�G���[", MB_OK);
			DestroyWindow(*System_GethWnd());
			return;
		}

		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		pIndex->pMaterials = new D3DMATERIAL9[pIndex->dwNumMaterials];
		pIndex->pTextures = new LPDIRECT3DTEXTURE9[pIndex->dwNumMaterials];
		D3DXMATERIAL* pD3DXMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

		for (DWORD i = 0; i < pIndex->dwNumMaterials; i++)
		{
			pIndex->pMaterials[i] = d3dxMaterials[i].MatD3D;
			pIndex->pMaterials[i].Ambient = pIndex->pMaterials[i].Diffuse;
			pIndex->pTextures[i] = NULL;

			if (d3dxMaterials[i].pTextureFilename != NULL && lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
			{
				//�e�N�X�`���̃p�X
				char TexturePath[MODEL_ADDRESS_LENGTH + MODEL_TEXTURE_LENGTH] = { "\0" };
				strcat(TexturePath, MODELS_FILE);
				strcat(TexturePath, path.Address);
				strcat(TexturePath,"/");
				strcat(TexturePath, d3dxMaterials[i].pTextureFilename);

				hr = D3DXCreateTextureFromFile(
					System_GetDevice(),
					TexturePath,
					&pIndex->pTextures[i]
				);

				if (FAILED(hr))
				{
					char ErrorText[200] = { "\0" };
					strcat(ErrorText, TexturePath);
					strcat(ErrorText, "\n�e�N�X�`���ǂݍ��݂Ɏ��s���܂����B");

					MessageBox(NULL, ErrorText, "�G���[", MB_OK);
				}
			}
		}
		pD3DXMtrlBuffer->Release();

	}

	//�J��
	void Release(Data* pIndex)
	{
		for(DWORD i = 0; i < sizeof(pIndex)/sizeof(Data); i++)
		{
			delete pIndex[i].pTextures;
			delete pIndex[i].pMaterials;
			pIndex[i].pMesh->Release();
		}
	}

	//������
	void Initialize() 
	{
		Load({BulletIndex,"bullet","bullet.x"},&Index[BulletIndex]);
		Load({ScrewIndex,"neji" ,"neji.x"},&Index[ScrewIndex]);
	}

	//�I������
	void Finalize()
	{
		Release(&Index[0]);
	}

	//�`��
	void Render(const Data* pData)
	{
		for (DWORD i = 0; i < pData->dwNumMaterials; i++)
		{
			LPDIRECT3DDEVICE9 Device = System_GetDevice();
			//�}�e���A���ݒ�
			Device->SetMaterial(&pData->pMaterials[i]);
			//�e�N�X�`���ݒ�
			Device->SetTexture(0, pData->pTextures[i]);
			//�����_�����O
			pData->pMesh->DrawSubset(i);
		}
	}

	//�`��
	void Render(const Name name)
	{
		//�}�e���A���̐��������[�v������
		for (DWORD i = 0; i < Index[name].dwNumMaterials; i++)
		{
			LPDIRECT3DDEVICE9 Device = System_GetDevice();
			//�}�e���A���ݒ�
			Device->SetMaterial(&Index[name].pMaterials[i]);
			//�e�N�X�`���ݒ�
			Device->SetTexture(0, Index[name].pTextures[i]);
			//�����_�����O
			Index[name].pMesh->DrawSubset(i);
		}

		return;
	}
	
	//�`��
	void Render(const int name,Data* pIndex)
	{
		for(DWORD i = 0; i < pIndex[name].dwNumMaterials; i++)
		{
			LPDIRECT3DDEVICE9 Device = System_GetDevice();
			//�}�e���A���ݒ�
			Device->SetMaterial(&Index[name].pMaterials[i]);
			//�e�N�X�`���ݒ�
			Device->SetTexture(0, Index[name].pTextures[i]);
			//�����_�����O
			Index[name].pMesh->DrawSubset(i);
		}
	}

	//�f�[�^�擾
	Data* Get_Data(const Name name)
	{
		return &Index[name];
	}

}

/*
//===============================================
//	�֐�			function
//===============================================

//-------------------------------------
//	�V�����ǂݍ��� �����ɂ̓��f���������Ă�t�@�C�����w��B
//-------------------------------------
void NXModel_Load(MeshData *pMesh, char ModelFile[30] , D3DXVECTOR3* pvecPosition)
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
	*//*

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
*/
