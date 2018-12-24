//
//	CMesh.cpp
//		Author:IKEDA HIROMASA 	DATE:2018/12/10
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"

#include<d3dx9.h>
#include"CMesh.h"
#include"Texture.h"
#include"Cube.h"
#include"System.h"

//===============================================
//	名前空間
//===============================================
namespace NMesh
{
	//===============================================
	//	抽象クラス AMesh
	//===============================================

	//コンストラクタ
	AMesh::AMesh()
	{
		
	}

	//デストラクタ
	AMesh::~AMesh()
	{
		
	}

	//描画
	void AMesh::Begin()
	{
		
	}

	//===============================================
	//	基本メッシュ CStandardMesh
	//===============================================

	//コンストラクタ
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

	//デストラクタ
	CStandardMesh::~CStandardMesh()
	{
		
	}

	//描画
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

	//テクスチャ設定
	void CStandardMesh::Set_Texture(NTexture::ATexture Texture)
	{
		this->pTexture = &Texture;
	}

	//テクスチャ設定 
	void CStandardMesh::Set_Texture(NTexture::ATexture* pTexture)
	{
		this->pTexture = pTexture;
	}

	//===============================================
	//	アニメーションメッシュ　CAnimationMesh
	//===============================================

	//コンストラクタ
	CAnimationMesh::CAnimationMesh()
	{
	
	}

	//デストラクタ
	CAnimationMesh::~CAnimationMesh()
	{
	
	}

	//描画
	void CAnimationMesh::Begin()
	{
		CStandardMesh::Begin();
	}

	//アニメーション設定
	void CAnimationMesh::Set_Animation(NTexture::CAnimation Animation)
	{
		this->pAnimation = &Animation;
	}

	//アニメーション設定
	void CAnimationMesh::Set_Animation(NTexture::CAnimation* pAnimation)
	{
		this->pAnimation = pAnimation;
	}

	//===============================================
	//	XModelメッシュ	CXModelMesh
	//===============================================

	//コンストラクタ
	CXModelMesh::CXModelMesh()
	{
		this->pModel = NULL;
	}

	CXModelMesh::CXModelMesh(NModel::Data* pModel)
	{
		this->pModel = pModel;
	}

	//デストラクタ
	CXModelMesh::~CXModelMesh()
	{
		NModel::Release(this->pModel);
	}

	//描画
	void CXModelMesh::Begin()
	{
		NModel::Render(this->pModel);
	}

	//===============================================
	//	XModel名メッシュ CXModelName
	//===============================================

	//コンストラクタ
	CXModelName::CXModelName(NModel::Name name)
	{
		this->ModelName = name;
	}

	//デストラクタ
	CXModelName::~CXModelName()
	{
		
	}

	//描画
	void CXModelName::Begin()
	{
		NModel::Render(this->ModelName);
	}
}