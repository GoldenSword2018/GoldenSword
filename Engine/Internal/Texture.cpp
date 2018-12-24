//
//	Texture.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/13
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#include<d3dx9.h>
#include"Texture.h"
#include"System.h"

namespace NTexture
{
	int g_FrameCounter;				//フレームカウント

	Data Index[Name::NAME_END];		//テクスチャデータ

	//==============================================
	//	基礎関数
	//==============================================

	//読み込み
	void Load(Path path,Data* pIndex)
	{
		HRESULT hr;

		char FilePath[TEXTURE_ADDRESS_LENGTH + 20] = {"\0"};
		strcat(&FilePath[0], TEXTURE_FILE);
		strcat(&FilePath[0], path.Address);

		hr = D3DXCreateTextureFromFile(System_GetDevice(), FilePath,&pIndex->pTexture);

		if(FAILED(hr))
		{
			//エラーテキスト
			MessageBox(*System_GethWnd(), FilePath, "読み込み失敗", MB_OK);
			DestroyWindow(*System_GethWnd());
			return;
		}
		else
		{
			D3DXIMAGE_INFO Info;	//画像情報
			D3DXGetImageInfoFromFile(FilePath,&Info);
			pIndex->height = Info.Height;
			pIndex->width = Info.Width;
		}
	}

	//投棄
	void Release(Data* pIndex)
	{
		const int IndexSize = sizeof(pIndex) / sizeof(Data);
		for(int i = 0; i < IndexSize; i++)
		{
			if (pIndex[i].pTexture != NULL)
			{
				pIndex[i].pTexture->Release();
				pIndex[i].pTexture = NULL;
			}
		}
	}

	//初期化
	void Initialize()
	{
		//読み込み
		Load({ CubeTexture,"StageBlockTexture.png" },&Index[CubeTexture]);
		Load({ EroTexture1,"ero1.jpg" }, &Index[EroTexture1]);
		Load({ EroTexture2,"ero2.jpg" }, &Index[EroTexture2]);
		Load({ MeshGroundTexture1, "FieldTex1.jpg" }, &Index[MeshGroundTexture1]);

		g_FrameCounter = 0;
	}

	//終了
	void Finalize()
	{
		Release(&Index[0]);
	}

	//テクスチャ取得
	LPDIRECT3DTEXTURE9 Get_Texture(const Name name)
	{
		if (name == NONE || name ==  NAME_END) return NULL;
		return Index[name].pTexture;
	}

	//非推奨
	LPDIRECT3DTEXTURE9 Get_Texture(const int name)
	{
		if (name == NONE || name == NAME_END) return NULL;
		return Index[name].pTexture;
	}

	//データ取得
	Data* Get_Data(const Name name)
	{
		if (name == NONE || name == NAME_END) return NULL;
		return &Index[name];
	}

	//テクスチャ幅
	UINT Get_Width(const Name name)
	{
		if (name == NONE || name == NAME_END) return NULL;
		return Index[name].width;
	}

	//テクスチャ高さ
	UINT Get_Height(const Name name)
	{
		if (name == NONE || name == NAME_END) return NULL;
		return Index[name].height;
	}

	//==============================================
	//	ATexture	抽象クラス
	//==============================================

	//コンストラクタ
	ATexture::ATexture(Name name)
	{
		this->name = name;
	}

	//デストラクタ
	ATexture::~ATexture()
	{
	
	}

	//Get_Width
	UINT ATexture::Get_Width()
	{
		return NTexture::Get_Width(this->name);
	}

	//Get_Height
	UINT ATexture::Get_Height()
	{
		return NTexture::Get_Height(this->name);
	}

	//Get_Texture
	LPDIRECT3DTEXTURE9 ATexture::Get_Texture()
	{
		return NTexture::Get_Texture(this->name);
	}


	//==============================================
	//	CTexture	基本クラス
	//==============================================

	//コンストラクタ
	CTexture::CTexture(Name name, D3DXVECTOR2 Coord, D3DXVECTOR2 Scale) :ATexture(name)
	{
		this->Coord = Coord;
		this->Scale = Scale;
	}

	//デストラクタ
	CTexture::~CTexture()
	{

	}

	//Get_Coord
	D3DXVECTOR2 CTexture::Get_Coord()
	{
		return this->Coord;
	}

	//Get_Size
	D3DXVECTOR2 CTexture::Get_Scale()
	{
		return this->Scale;
	}

	//Set_Coord
	void CTexture::Set_Coord(D3DXVECTOR2 Coord)
	{
		this->Coord = Coord;
		return;
	}

	//Set_Scale
	void CTexture::Set_Scale(D3DXVECTOR2 Scale)
	{
		this->Scale = Scale;
		return;
	}

	//==============================================
	//	CAnimation
	//==============================================

	//コンストラクタ
	CAnimation::CAnimation(int AnimaPatern, int MaxPatern, int YMaxPatern, int Waitframe)
	{
		this->AnimaPatern = AnimaPatern;
		this->MaxPatern = MaxPatern;
		this->YMaxPatern = YMaxPatern;
		this->Waitframe = Waitframe;
		this->Createframe = g_FrameCounter;
	}

	//デストラクタ
	CAnimation::~CAnimation()
	{

	}

	//Loop
	bool CAnimation::Loop()
	{
		this->AnimaPatern = (g_FrameCounter / this->Waitframe) % this->MaxPatern;
		return this->AnimaPatern >= this->MaxPatern;
	}

	//NoLoop
	bool CAnimation::NoLoop()
	{
		this->AnimaPatern = min((g_FrameCounter / this->Waitframe), this->MaxPatern);
		return this->AnimaPatern >= this->MaxPatern;
	}

}

//
////===============================================
////	構造体
////===============================================
//
////-------------------------------------
////	テクスチャデータ
////-------------------------------------
//typedef struct TEXTUREDATA_INDEX
//{
//	int TexName;								//テクスチャ名
// 	const char FileAddress[TEXTURE_FILENAME_MAX];		//アドレス
//	UINT width;									//テクスチャ幅
//	UINT height;								//テクスチャ高さ
//}TEXTUREDATA_INDEX;
//
////===============================================
////	グローバル変数
////===============================================
//#if !defined(DISABLE_TEXTURE)
//
////-------------------------------------
////	テクスチャ
////-------------------------------------
//static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_NAME_END];
//
////-------------------------------------
////	テクスチャインデックス *サイズは自動取得
////-------------------------------------
//static TEXTUREDATA_INDEX Texture_Index[] = 
//{
//	{CubeTexture,"Texture/StageBlockTexture.png"},
//	{EroTexture1,"Texture/ero1.jpg"},
//	{EroTexture2,"Texture/ero2.jpg"},
//	{MeshGroundTexture1, "Texture/FieldTex1.jpg"}
//};
//
//#endif
//
////===============================================
////	関数
////===============================================
//void Texture_Load(TEXTUREDATA_INDEX* pTextureData_Index, LPDIRECT3DTEXTURE9* plpTexture, const int nListEnd);
//
////-------------------------------------
////	テクスチャ初期化
////-------------------------------------
//void Texture_Initialize()
//{
//#if !defined(DISABLE_TEXTURE)
//
//	Texture_Load(&Texture_Index[0],&g_pTextures[0],TEXTURE_NAME_END);
//
//#endif
//}
//
////-------------------------------------
////	テクスチャの読み込み [先頭ファイルデータ] [先頭テクスチャ] [テクスチャ名の最終番目]
////-------------------------------------
//void Texture_Load(TEXTUREDATA_INDEX *pTextureData_Index,LPDIRECT3DTEXTURE9 *plpTexture, const int nListEnd)
//{
//	HRESULT hr;
//	char ErrorText[256] = {};
//	int failded_Count = 0;
//
//	for (int i = 0; i < nListEnd; i++)
//	{
//		D3DXIMAGE_INFO Texture_Info;	//画像データ情報
//
//		//読み込みが失敗した時にはg_pTexture[i]にnullが置かれる
//		hr = D3DXCreateTextureFromFile(System_GetDevice(), pTextureData_Index->FileAddress, plpTexture);
//
//		if (FAILED(hr))
//		{
//			//エラーの表示
//			strcat(ErrorText, pTextureData_Index->FileAddress);
//			strcat(ErrorText, "\n");
//			failded_Count++;
//		}
//		else
//		{
//			//画像データ取得
//			D3DXGetImageInfoFromFile(pTextureData_Index->FileAddress, &Texture_Info);
//			pTextureData_Index->height = Texture_Info.Height;
//			pTextureData_Index->width = Texture_Info.Width;
//		}
//
//		plpTexture ++;
//		pTextureData_Index ++;
//	}
//
//	//読み込みに失敗している
//	if (failded_Count != 0)
//	{
//		MessageBox(*System_GethWnd(), ErrorText, "読み込み失敗", MB_OK);
//		DestroyWindow(*System_GethWnd());
//	}
//
//	return;
//}
//
////-------------------------------------
////	終了処理
////-------------------------------------
//void Texture_Finalize() 
//{
//#if !defined(DISABLE_TEXTURE)
//	for (int i = 0; i < TEXTURE_NAME_END; i++)
//	{
//		if (g_pTextures[i] != NULL)
//		{
//			g_pTextures[i]->Release();
//			g_pTextures[i] = NULL;
//		}
//	}
//#endif
//}
//
////-------------------------------------
////	テクスチャポインタの取得
////-------------------------------------
//LPDIRECT3DTEXTURE9 Texture_GetTexture(int index) 
//{
//#if !defined(DISABLE_TEXTURE)
//	return g_pTextures[index];
//#else
//	return NULL;
//#endif
//}
//
////-------------------------------------
////	テクスチャ幅の取得
////-------------------------------------
//int Texture_GetWidth(int index) 
//{
//#if !defined(DISABLE_TEXTURE)
//	return Texture_Index[index].width;
//#else
//	return 0;
//#endif
//}
//
////-------------------------------------
////	テクスチャ縦の取得
////-------------------------------------
//int Texture_GetHeight(int index) 
//{
//#if !defined(DISABLE_TEXTURE)
//	return Texture_Index[index].height;
//#else
//	return 0;
//#endif
//}
