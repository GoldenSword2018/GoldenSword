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
	int g_FrameCounter;				//�t���[���J�E���g

	Data Index[Name::NAME_END];		//�e�N�X�`���f�[�^

	//==============================================
	//	��b�֐�
	//==============================================

	//�ǂݍ���
	void Load(Path path,Data* pIndex)
	{
		HRESULT hr;

		char FilePath[TEXTURE_ADDRESS_LENGTH + 20] = {"\0"};
		strcat(&FilePath[0], TEXTURE_FILE);
		strcat(&FilePath[0], path.Address);

		hr = D3DXCreateTextureFromFile(System_GetDevice(), FilePath,&pIndex->pTexture);

		if(FAILED(hr))
		{
			//�G���[�e�L�X�g
			MessageBox(*System_GethWnd(), FilePath, "�ǂݍ��ݎ��s", MB_OK);
			DestroyWindow(*System_GethWnd());
			return;
		}
		else
		{
			D3DXIMAGE_INFO Info;	//�摜���
			D3DXGetImageInfoFromFile(FilePath,&Info);
			pIndex->height = Info.Height;
			pIndex->width = Info.Width;
		}
	}

	//����
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

	//������
	void Initialize()
	{
		//�ǂݍ���
		Load({ CubeTexture,"StageBlockTexture.png" },&Index[CubeTexture]);
		Load({ EroTexture1,"ero1.jpg" }, &Index[EroTexture1]);
		Load({ EroTexture2,"ero2.jpg" }, &Index[EroTexture2]);
		Load({ MeshGroundTexture1, "FieldTex1.jpg" }, &Index[MeshGroundTexture1]);

		g_FrameCounter = 0;
	}

	//�I��
	void Finalize()
	{
		Release(&Index[0]);
	}

	//�e�N�X�`���擾
	LPDIRECT3DTEXTURE9 Get_Texture(const Name name)
	{
		if (name == NONE || name ==  NAME_END) return NULL;
		return Index[name].pTexture;
	}

	//�񐄏�
	LPDIRECT3DTEXTURE9 Get_Texture(const int name)
	{
		if (name == NONE || name == NAME_END) return NULL;
		return Index[name].pTexture;
	}

	//�f�[�^�擾
	Data* Get_Data(const Name name)
	{
		if (name == NONE || name == NAME_END) return NULL;
		return &Index[name];
	}

	//�e�N�X�`����
	UINT Get_Width(const Name name)
	{
		if (name == NONE || name == NAME_END) return NULL;
		return Index[name].width;
	}

	//�e�N�X�`������
	UINT Get_Height(const Name name)
	{
		if (name == NONE || name == NAME_END) return NULL;
		return Index[name].height;
	}

	//==============================================
	//	ATexture	���ۃN���X
	//==============================================

	//�R���X�g���N�^
	ATexture::ATexture(Name name)
	{
		this->name = name;
	}

	//�f�X�g���N�^
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
	//	CTexture	��{�N���X
	//==============================================

	//�R���X�g���N�^
	CTexture::CTexture(Name name, D3DXVECTOR2 Coord, D3DXVECTOR2 Scale) :ATexture(name)
	{
		this->Coord = Coord;
		this->Scale = Scale;
	}

	//�f�X�g���N�^
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

	//�R���X�g���N�^
	CAnimation::CAnimation(int AnimaPatern, int MaxPatern, int YMaxPatern, int Waitframe)
	{
		this->AnimaPatern = AnimaPatern;
		this->MaxPatern = MaxPatern;
		this->YMaxPatern = YMaxPatern;
		this->Waitframe = Waitframe;
		this->Createframe = g_FrameCounter;
	}

	//�f�X�g���N�^
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
////	�\����
////===============================================
//
////-------------------------------------
////	�e�N�X�`���f�[�^
////-------------------------------------
//typedef struct TEXTUREDATA_INDEX
//{
//	int TexName;								//�e�N�X�`����
// 	const char FileAddress[TEXTURE_FILENAME_MAX];		//�A�h���X
//	UINT width;									//�e�N�X�`����
//	UINT height;								//�e�N�X�`������
//}TEXTUREDATA_INDEX;
//
////===============================================
////	�O���[�o���ϐ�
////===============================================
//#if !defined(DISABLE_TEXTURE)
//
////-------------------------------------
////	�e�N�X�`��
////-------------------------------------
//static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_NAME_END];
//
////-------------------------------------
////	�e�N�X�`���C���f�b�N�X *�T�C�Y�͎����擾
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
////	�֐�
////===============================================
//void Texture_Load(TEXTUREDATA_INDEX* pTextureData_Index, LPDIRECT3DTEXTURE9* plpTexture, const int nListEnd);
//
////-------------------------------------
////	�e�N�X�`��������
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
////	�e�N�X�`���̓ǂݍ��� [�擪�t�@�C���f�[�^] [�擪�e�N�X�`��] [�e�N�X�`�����̍ŏI�Ԗ�]
////-------------------------------------
//void Texture_Load(TEXTUREDATA_INDEX *pTextureData_Index,LPDIRECT3DTEXTURE9 *plpTexture, const int nListEnd)
//{
//	HRESULT hr;
//	char ErrorText[256] = {};
//	int failded_Count = 0;
//
//	for (int i = 0; i < nListEnd; i++)
//	{
//		D3DXIMAGE_INFO Texture_Info;	//�摜�f�[�^���
//
//		//�ǂݍ��݂����s�������ɂ�g_pTexture[i]��null���u�����
//		hr = D3DXCreateTextureFromFile(System_GetDevice(), pTextureData_Index->FileAddress, plpTexture);
//
//		if (FAILED(hr))
//		{
//			//�G���[�̕\��
//			strcat(ErrorText, pTextureData_Index->FileAddress);
//			strcat(ErrorText, "\n");
//			failded_Count++;
//		}
//		else
//		{
//			//�摜�f�[�^�擾
//			D3DXGetImageInfoFromFile(pTextureData_Index->FileAddress, &Texture_Info);
//			pTextureData_Index->height = Texture_Info.Height;
//			pTextureData_Index->width = Texture_Info.Width;
//		}
//
//		plpTexture ++;
//		pTextureData_Index ++;
//	}
//
//	//�ǂݍ��݂Ɏ��s���Ă���
//	if (failded_Count != 0)
//	{
//		MessageBox(*System_GethWnd(), ErrorText, "�ǂݍ��ݎ��s", MB_OK);
//		DestroyWindow(*System_GethWnd());
//	}
//
//	return;
//}
//
////-------------------------------------
////	�I������
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
////	�e�N�X�`���|�C���^�̎擾
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
////	�e�N�X�`�����̎擾
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
////	�e�N�X�`���c�̎擾
////-------------------------------------
//int Texture_GetHeight(int index) 
//{
//#if !defined(DISABLE_TEXTURE)
//	return Texture_Index[index].height;
//#else
//	return 0;
//#endif
//}
