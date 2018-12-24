//
//	CMesh.h
//		Author:IKEDA HIROMASA 	DATE:2018/12/04
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CMESH_H
#define CMESH_H

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"

#include<d3dx9.h>
//Class
#include"Texture.h"
#include"XModel.h"	

//===============================================
//	���O���
//===============================================
namespace NMesh
{
	//===============================================
	//	���ۃN���X AMesh
	//===============================================
	class AMesh
	{
	private:

	public:
		AMesh();
		~AMesh();

	public:
		virtual void Begin() = 0;	//�`��
	};

	//===============================================
	//	��{���b�V�� CStandardMesh
	//===============================================
	//�R���X�g���N�^��Cube��ݒ�
	class CStandardMesh:public AMesh
	{
	public:
		NTexture::ATexture* pTexture;	//�e�N�X�`��
		D3DMATERIAL9 Material;			//�}�e���A��

		DWORD FVF;
		D3DPRIMITIVETYPE PrimitiveType;
		void* Model;
		UINT DataSize;
		UINT PrimitiveCount;

	public:
		CStandardMesh():CStandardMesh(&NTexture::CTexture(),D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)) {};
		CStandardMesh(D3DXCOLOR Color) :CStandardMesh(&NTexture::CTexture(), Color){};
		CStandardMesh(NTexture::ATexture* pTexture):CStandardMesh(pTexture, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)) {};
		CStandardMesh(NTexture::ATexture* pTexture,D3DXCOLOR Color);

		~CStandardMesh();
		
	public:
		virtual void Begin() override;

	public:
		void Set_Texture(NTexture::ATexture* pTexture);
		void Set_Texture(NTexture::ATexture Texture);

	};

	//===============================================
	//	�A�j���[�V�������b�V���@CAnimationMesh	������
	//===============================================
	class CAnimationMesh:public CStandardMesh
	{
	public:
		bool Loop;
		NTexture::CTexture* pTexture;
		NTexture::CAnimation* pAnimation;
		
	public:
		CAnimationMesh();
		~CAnimationMesh();

	public:
		virtual void Begin() override;

	public:
		void Set_Animation(NTexture::CAnimation Animation);
		void Set_Animation(NTexture::CAnimation* pAnimation);

	};

	//===============================================
	//	XModel���b�V��	CXModelMesh
	//===============================================
	class CXModelMesh:public AMesh
	{
	private:

	public:
		NModel::Data* pModel;
	public:
		CXModelMesh();
		CXModelMesh(NModel::Data* pModel);
		~CXModelMesh();

	public:
		void Begin() override;
	};

	//===============================================
	//	XModel�����b�V�� CXModelName
	//===============================================
	class CXModelName:public AMesh
	{
	private:
		NModel::Name ModelName;

	public:
		CXModelName() :CXModelName(NModel::NONE) {};
		CXModelName(NModel::Name name);
		~CXModelName();
	
	public:
		void Begin() override;
	};
}

#endif