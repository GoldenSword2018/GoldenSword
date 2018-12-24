//
//	XModel.h
//		Author:HIROMASA IKEDA	DATE:2018/12/05
//===============================================
//	�ύX�� Changed By
//		Name:Minoda Takamasa	DATE:2018/10/23
//
//-----------------------------------------------

#pragma once
#ifndef XMODEL_H
#define XMODEL_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>

//================================================
//	�}�N����`	define
//================================================
#define MODEL_FILENAME_MAX (64)

#define MODEL_ADDRESS_LENGTH (60)		//Models/�t�H���_���̃��f���t�H���_�ւ̃A�h���X��
#define MODEL_NAME_LENGTH (30)			//���f���t�@�C������
#define MODEL_TEXTURE_LENGTH (60)		//���f���t�@�C�����ł̃e�N�X�`������

#define MODELS_FILE ("Models/")

//================================================
//	XModel ���O���
//================================================
namespace NModel
{
	//���f����
	const enum Name
	{
		BulletIndex,
		ScrewIndex,
		NAME_END,
		NONE
	};

	//Model�f�[�^
	struct Data
	{
		LPD3DXMESH pMesh;
		D3DMATERIAL9* pMaterials;
		LPDIRECT3DTEXTURE9* pTextures;
		DWORD dwNumMaterials;
	};

	//Path [Models/]���̃��f�����w�肵�āB
	struct Path
	{
		Name name;
		const char Address[MODEL_ADDRESS_LENGTH];	//���f���̓����Ă���t�H���_
		const char Models[MODEL_NAME_LENGTH];		//���f���t�@�C����
	};

	//��{�֐�
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
//	�񋓌^		enum
//================================================
enum MeshIndex
{
	BulletIndex=0,
	ScrewIndex,
	MeshIndexMax
};

//================================================
//	�\����		struct/typedef
//================================================
typedef struct MeshTag
{
	LPD3DXMESH pMesh;
	D3DMATERIAL9* pMeshMaterials;
	LPDIRECT3DTEXTURE9* pMeshTextures;
	DWORD dwNumMaterials;

	D3DXVECTOR3 vecPosition;		//Mesh�̒��S�ʒu�H
	D3DXMATRIXA16 matWorld;

}MeshData;

//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�֐�		function
//================================================
void XModel_Initialize();	//������
void XModel_Finalize();		//�I��

void NXModel_Load(MeshData *pMesh, char ModelFile[10], D3DXVECTOR3* pvecPosition);
void XModel_Load(MeshData *pMesh, LPSTR szXFileName, D3DXVECTOR3* pvecPosition);		//���f���ǂݍ���
void XModel_Render(MeshData *pMesh);	//�`��
void XModel_Render(MeshData *pMesh, D3DXMATRIXA16 mtx);
MeshData* GetMeshData(int MeshIndex);  //���b�V���f�[�^�̎擾
*/

#endif