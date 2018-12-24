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
//	マクロ定義
//===============================================
#define TEXTURE_FILENAME_MAX (64)
#define TEXTURE_ADDRESS_LENGTH (60)		//アドレス長

#define TEXTURE_FILE ("Texture/")

//===============================================
//	名前空間
//===============================================

namespace NTexture
{
	//テクスチャ名
	enum Name
	{
		CubeTexture,
		EroTexture1,
		EroTexture2,
		MeshGroundTexture1,
		NAME_END,	//テクスチャ終わり
		NONE		//指定無い場合
	};

	//テクスチャデータ
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

	//Index (将来像)
	struct TextureIndex
	{
		Data data;
		Path path;
	};

	//==============================================
	//	基本関数
	//==============================================
	void Release(Data* pIndex);
	void Initialize();		//初期化
	void Finalize();		//終了処理
	LPDIRECT3DTEXTURE9 Get_Texture(const Name name);	//テクスチャ取得
	LPDIRECT3DTEXTURE9 Get_Texture(const int name);		//テクスチャ取得　非推奨
	Data* Get_Data(const Name name);		//データ取得
	UINT Get_Width(const Name name);		//元テクスチャ幅
	UINT Get_Height(const Name name);		//元テクスチャ高さ

	//==============================================
	//	抽象クラス
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
	//	基本テクスチャ
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
	//	アニメーション
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
////	列挙
////===============================================
//
////-------------------------------------
////	テクスチャ名リスト
////-------------------------------------
//typedef enum TEXTURE_NAME
//{
//	CubeTexture,
//	EroTexture1,
//	EroTexture2,
//	MeshGroundTexture1,
//	TEXTURE_NAME_END,	//テクスチャ終わり
//	TEXTURE_NONE		//指定無い場合
//}TEXTURE_NAME;
//
////===============================================
////	構造体
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
////	関数
////===============================================
//
//void Texture_Initialize();							//テクスチャ初期化
//void Texture_Finalize();							//テクスチャ終了
//
//LPDIRECT3DTEXTURE9 Texture_GetTexture(int index);	//テクスチャポインタ取得
//int Texture_GetWidth(int index);					//テクスチャ幅取得 
//int Texture_GetHeight(int index);					//テクスチャ高さ取得

#endif
