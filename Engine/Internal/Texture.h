//
//	Texture.h
//		Auther:HIROMASA IKEDA	Date:2018/12/04
//===============================================
#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include<d3dx9.h>
#include"common.h"

//===============================================
//	�}�N����`
//===============================================
#define TEXTURE_FILENAME_MAX (64)
#define TEXTURE_ADDRESS_LENGTH (60)		//�A�h���X��

#define TEXTURE_FILE ("Texture/")

//===============================================
//	���O���
//===============================================

namespace NTexture
{
	//�e�N�X�`����
	enum Name
	{
		CubeTexture,
		EroTexture1,
		EroTexture2,
		MeshGroundTexture1,
		NAME_END,	//�e�N�X�`���I���
		NONE		//�w�薳���ꍇ
	};

	//�e�N�X�`���f�[�^
	struct Data
	{
		LPDIRECT3DTEXTURE9 pTexture;
		UINT width;
		UINT height;
	};

	//Path
	struct Path
	{
		Name name;
		const char Address[TEXTURE_ADDRESS_LENGTH];
	};

	//Index (������)
	struct TextureIndex
	{
		Data data;
		Path path;
	};

	//==============================================
	//	��{�֐�
	//==============================================
	void Release(Data* pIndex);
	void Initialize();		//������
	void Finalize();		//�I������
	LPDIRECT3DTEXTURE9 Get_Texture(const Name name);	//�e�N�X�`���擾
	LPDIRECT3DTEXTURE9 Get_Texture(const int name);		//�e�N�X�`���擾�@�񐄏�
	Data* Get_Data(const Name name);		//�f�[�^�擾
	UINT Get_Width(const Name name);		//���e�N�X�`����
	UINT Get_Height(const Name name);		//���e�N�X�`������

	//==============================================
	//	���ۃN���X
	//==============================================
	class ATexture
	{
	public:
		Name name;

	public:
		ATexture() :ATexture(Name::NONE) {};
		ATexture(Name name);

		~ATexture();

	public:
		UINT Get_Width();
		UINT Get_Height();
		LPDIRECT3DTEXTURE9 Get_Texture();
	};

	//==============================================
	//	��{�e�N�X�`��
	//==============================================
	class CTexture:public ATexture
	{
	public:
		D3DXVECTOR2 Coord;
		D3DXVECTOR2 Scale;

	public:
		CTexture() :CTexture(Name::NONE, { 0.0f,0.0f }, {0.0f,0.0f}) {};
		CTexture(Name name) :CTexture(name, { 0.0f,0.0f }, {(float)NTexture::Get_Width(name),(float)NTexture::Get_Height(name)}) {};
		CTexture(Name name, D3DXVECTOR2 Coord, D3DXVECTOR2 Scale);

		~CTexture();
	public:
		//Get
		D3DXVECTOR2 Get_Coord();
		D3DXVECTOR2 Get_Scale();

		//Set
		void Set_Coord(D3DXVECTOR2 Coord);
		void Set_Scale(D3DXVECTOR2 Scale);
	};

	//==============================================
	//	�A�j���[�V����
	//==============================================
	class CAnimation
	{
	public:
		int AnimaPatern;
		int MaxPatern;
		int YMaxPatern;
		int Waitframe;
		int Createframe;

	public:
		CAnimation():CAnimation(0,0,0,1) {};
		CAnimation(int MaxPatern, int YMaxPatern, int Waitframe) :CAnimation(0, MaxPatern, YMaxPatern, Waitframe) {};
		CAnimation(int AnimaPatern, int MaxPatern, int YMaxPatern, int Waitframe);
		~CAnimation();

	public:
		bool Loop();
		bool NoLoop();
	};
}

////===============================================
////	��
////===============================================
//
////-------------------------------------
////	�e�N�X�`�������X�g
////-------------------------------------
//typedef enum TEXTURE_NAME
//{
//	CubeTexture,
//	EroTexture1,
//	EroTexture2,
//	MeshGroundTexture1,
//	TEXTURE_NAME_END,	//�e�N�X�`���I���
//	TEXTURE_NONE		//�w�薳���ꍇ
//}TEXTURE_NAME;
//
////===============================================
////	�\����
////===============================================
//
////-------------------------------------
////	TexScale
////-------------------------------------
//typedef struct TEXSCALE
//{
//	int width;
//	int height;
//}TEXSCALE;
//
////-------------------------------------
////	TexCoord
////-------------------------------------
//typedef struct TEXCOORD
//{
//	int x;
//	int y;
//}TEXCOORD;
//
////===============================================
////	�֐�
////===============================================
//
//void Texture_Initialize();							//�e�N�X�`��������
//void Texture_Finalize();							//�e�N�X�`���I��
//
//LPDIRECT3DTEXTURE9 Texture_GetTexture(int index);	//�e�N�X�`���|�C���^�擾
//int Texture_GetWidth(int index);					//�e�N�X�`�����擾 
//int Texture_GetHeight(int index);					//�e�N�X�`�������擾

#endif
