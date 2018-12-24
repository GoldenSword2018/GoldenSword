//
//	CRender.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
#include<d3dx9.h>
#include<math.h>
#include<vector>

#include"CTransform.h"
#include"CRender.h"
#include"System.h"
#include"Texture.h"
#include"Sprite.h"
#include"Animation.h"

#include"Cube.h"

//===============================================
//	グローバル変数
//===============================================

//===============================================
//	名前空間
//===============================================
namespace NRender
{
	//==============================================
	//	Render3D
	//==============================================

	//コンストラクタ
	Render3D::Render3D()
	{
		this->pModel = new NMesh::CStandardMesh();
		this->bRender = true;
		return;
	}

	//デストラクタ
	Render3D::~Render3D()
	{
		if(this->pModel != NULL)
		{
			delete this->pModel;
			this->pModel = NULL;
		}
		return;
	}

	//Set_Mesh()
	void Render3D::Set_Mesh(NMesh::AMesh* pModel)
	{
		if (this->pModel != NULL) delete this->pModel;
		this->pModel = pModel;
		return;
	}

	//描画
	void Render3D::Begin(D3DXMATRIX* MtxWorld)
	{
		if (this->pModel == NULL || this->bRender == false) return;
		System_GetDevice()->SetTransform(D3DTS_WORLD,MtxWorld);
		pModel->Begin();
		return;
	}

	//==============================================
	//	Render2D
	//==============================================

	//コンストラクタ
	Render2D::Render2D(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation)
	{
		this->pTransform = pTransform;
		this->pTexture = pTexture;
		this->pAnimation = pAnimation;
	}

	//デストラクタ
	Render2D::~Render2D()
	{
		
	}

	//描画
	bool Render2D::Begin(RENDER2D_TYPE R2D_TYPE)
	{
		if (this->pTransform == NULL || this->pTexture == NULL) return false;

		switch (R2D_TYPE)
		{
		case R2D_PORIGON:
			Render2D_Porigon(pTransform);
			break;
		case R2D_PORIGON_ROTATE:
			Render2D_Porigon_Rotate(pTransform);
			break;
		case R2D_TEXTURE_SIZE:
			Render2D_Texture_Size(pTransform, pTexture);
			break;
		case R2D_TEXTURE_FILL:
			Render2D_Texture_Fill(pTransform, pTexture);
			break;
		case R2D_TEXTURE_CLIP:
			Render2D_Texture_Clip(pTransform, pTexture);
			break;
		case R2D_SPRITE:
			Render2D_Sprite(pTransform, pTexture);
			break;
		case R2D_SPRITE_ROTATE:
			Render2D_Sprite_Rotate(pTransform, pTexture);
			break;
		default:
			return false;
		}

		return true;
	}

	//描画
	bool Render2D::Begin(RENDER2DANIMA_TYPE R2DA_TYPE)
	{
		if (this->pTransform == NULL || this->pTexture == NULL || this->pAnimation == NULL) return false;

		switch (R2DA_TYPE)
		{
		case R2DA_NOLOOP:
			Animation_NoLoop(pTransform, pTexture, pAnimation);
			break;
		case R2DA_LOOP:
			Animation_Loop(pTransform, pTexture, pAnimation);
			break;
		case R2DA_LOOP_ROTATE:
			Animation_Loop_Rotate(pTransform, pTexture, pAnimation);
			break;
		default:
			return false;
		}

		return true;
	}
}

/*
//===============================================
//	Render3D　クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Render3D::Render3D()
{
	bRender = true;
}

//-------------------------------------
//	コンストラクタ	ポインタ型
//-------------------------------------
Render3D::Render3D(Transform* pTransform, Texture* pTexture)
{
	this->pTransform = pTransform;
	this->pTexture = pTexture;
	this->bRender = true;
}

//-------------------------------------
//	描画
//-------------------------------------
bool Render3D::Begin(DWORD SetFVF, D3DPRIMITIVETYPE PrimitiveType, void* Model, UINT DataSize, UINT PrimitiveCount)
{
	if (pTransform == NULL && bRender == false) return false;

	System_GetDevice()->SetTransform(D3DTS_WORLD, &this->pTransform->Convert());	//デバイスへ登録
	System_GetDevice()->SetFVF(SetFVF);

	//色が設定されいるなら
	if(SetFVF & D3DFVF_DIFFUSE)
	{
		if(Model == GetModel_Cube())
		{
			Set_CubeColor(this->pTransform->Color);
		}
	}

	if (pTexture == NULL || pTexture->Texture_index == TEXTURE_NONE)
	{
		System_GetDevice()->SetTexture(0, NULL);
	}
	else
	{
		System_GetDevice()->SetTexture(0, Texture_GetTexture(pTexture->Texture_index));
	}

	System_GetDevice()->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, Model, DataSize);

	return true;
}

//===============================================
//	Render2D クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Render2D::Render2D()
{
	pTransform = NULL;
	pTexture = NULL;
	pAnimation = NULL;
}

//-------------------------------------
//	コンストラクタ	ポインタ型
//-------------------------------------
Render2D::Render2D(Transform2* pTransform, Texture* pTexture)
{
	this->pTransform = pTransform;
	this->pTexture = pTexture;
	pAnimation = NULL;
}

Render2D::Render2D(Transform2* pTransform, Texture* pTexture, Animation* pAnimation)
{
	this->pTransform = pTransform;
	this->pTexture = pTexture;
	this->pAnimation = pAnimation;
}

//-------------------------------------
//	描画　スプライト
//-------------------------------------
bool Render2D::Begin(RENDER2D_TYPE R2D_TYPE)
{
	if (pTransform == NULL || pTexture == NULL) return false;

	switch (R2D_TYPE)
	{
	case R2D_PORIGON:
		Render2D_Porigon(pTransform);
		break;
	case R2D_PORIGON_ROTATE:
		Render2D_Porigon_Rotate(pTransform);
		break;
	case R2D_TEXTURE_SIZE:
		Render2D_Texture_Size(pTransform, pTexture);
		break;
	case R2D_TEXTURE_FILL:
		Render2D_Texture_Fill(pTransform, pTexture);
		break;
	case R2D_TEXTURE_CLIP:
		Render2D_Texture_Clip(pTransform, pTexture);
		break;
	case R2D_SPRITE:
		Render2D_Sprite(pTransform, pTexture);
		break;
	case R2D_SPRITE_ROTATE:
		Render2D_Sprite_Rotate(pTransform, pTexture);
		break;
	default:
		return false;
	}

	return true;
}

//-------------------------------------
//	描画　スプライトアニメーション
//-------------------------------------
bool Render2D::Begin(RENDER2DANIMA_TYPE R2DA_TYPE)
{
	if (pTransform == NULL || pTexture == NULL || pAnimation == NULL) return false;

	switch (R2DA_TYPE)
	{
	case R2DA_NOLOOP:
		Animation_NoLoop(pTransform, pTexture, pAnimation);
		break;
	case R2DA_LOOP:
		Animation_Loop(pTransform, pTexture, pAnimation);
		break;
	case R2DA_LOOP_ROTATE:
		Animation_Loop_Rotate(pTransform, pTexture, pAnimation);
		break;
	default:
		return false;
	}

	return true;
}
*/


