//
//	CMesh.cpp
//		Author:IKEDA HIROMASA 	DATE:2018/12/10
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
#include"CMesh.h"
#include"Texture.h"
#include"Cube.h"
#include"System.h"

//===============================================
//	���O���
//===============================================
namespace NMesh
{
	//===============================================
	//	���ۃN���X AMesh
	//===============================================

	//�R���X�g���N�^
	AMesh::AMesh()
	{
		
	}

	//�f�X�g���N�^
	AMesh::~AMesh()
	{
		
	}

	//�`��
	void AMesh::Begin()
	{
		
	}

	//===============================================
	//	��{���b�V�� CStandardMesh
	//===============================================

	//�R���X�g���N�^
	CStandardMesh::CStandardMesh(NTexture::ATexture* pTexture,D3DXCOLOR Color)
	{
		this->pTexture = pTexture;
		this->Material.Diffuse = this->Material.Ambient = Color;
		this->FVF = FVF_CUBE_VERTEX3D;
		this->PrimitiveType = CUBE_PRIMITIVE_TYPE;
		this->Model = GetModel_Cube();
		this->DataSize = sizeof(CubeVertex3D);
		this->PrimitiveCount = CUBE_PRIMITIVE_NUM;
	}

	//�f�X�g���N�^
	CStandardMesh::~CStandardMesh()
	{
		
	}

	//�`��
	void CStandardMesh::Begin()
	{
		LPDIRECT3DDEVICE9 Device = System_GetDevice();

		Device->SetMaterial(&this->Material);

		Device->SetFVF(this->FVF);

		if (this->pTexture->name == NTexture::NONE || this->pTexture->name == NTexture::NAME_END)
		{
			Device->SetTexture(0,NULL);
		}
		else
		{
			Device->SetTexture(0, pTexture->Get_Texture());
		}

		Device->DrawPrimitiveUP(this->PrimitiveType, this->PrimitiveCount, this->Model, this->DataSize);

		return;
	}

	//�e�N�X�`���ݒ�
	void CStandardMesh::Set_Texture(NTexture::ATexture Texture)
	{
		this->pTexture = &Texture;
	}

	//�e�N�X�`���ݒ� 
	void CStandardMesh::Set_Texture(NTexture::ATexture* pTexture)
	{
		this->pTexture = pTexture;
	}

	//===============================================
	//	�A�j���[�V�������b�V���@CAnimationMesh
	//===============================================

	//�R���X�g���N�^
	CAnimationMesh::CAnimationMesh()
	{
	
	}

	//�f�X�g���N�^
	CAnimationMesh::~CAnimationMesh()
	{
	
	}

	//�`��
	void CAnimationMesh::Begin()
	{
		CStandardMesh::Begin();
	}

	//�A�j���[�V�����ݒ�
	void CAnimationMesh::Set_Animation(NTexture::CAnimation Animation)
	{
		this->pAnimation = &Animation;
	}

	//�A�j���[�V�����ݒ�
	void CAnimationMesh::Set_Animation(NTexture::CAnimation* pAnimation)
	{
		this->pAnimation = pAnimation;
	}

	//===============================================
	//	XModel���b�V��	CXModelMesh
	//===============================================

	//�R���X�g���N�^
	CXModelMesh::CXModelMesh()
	{
		this->pModel = NULL;
	}

	CXModelMesh::CXModelMesh(NModel::Data* pModel)
	{
		this->pModel = pModel;
	}

	//�f�X�g���N�^
	CXModelMesh::~CXModelMesh()
	{
		NModel::Release(this->pModel);
	}

	//�`��
	void CXModelMesh::Begin()
	{
		NModel::Render(this->pModel);
	}

	//===============================================
	//	XModel�����b�V�� CXModelName
	//===============================================

	//�R���X�g���N�^
	CXModelName::CXModelName(NModel::Name name)
	{
		this->ModelName = name;
	}

	//�f�X�g���N�^
	CXModelName::~CXModelName()
	{
		
	}

	//�`��
	void CXModelName::Begin()
	{
		NModel::Render(this->ModelName);
	}
}