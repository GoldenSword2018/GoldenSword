//
//	Main.cpp
//		Author:HIROMASA IKEDA		Date:2018/09/13
//================================================
#include"common.h"
#include<time.h>
#include"System.h"

#include"Cube.h"
#include"Lighting.h"

#include"SecondWindow.h"
#include"CTeamProt.h"
#include"Player.h"
#include"Bullet.h"
#include"XModel.h"
#include"Screwdrop.h"

#include"CTransform.h"

#include"TestSpace.h"

#include "MeshField_Ground.h"
//Class
#include"CUI.h"

#include"MeshField_Ground.h"

//===============================================
//	�O���[�o���ϐ�
//===============================================

//UI�\��
static UI uiSprite(
	&Transform2
	(
		D3DXVECTOR2(WINDOWSCREEN_WIDTH*0.5f,WINDOWSCREEN_HEIGHT * 0.5f),
		D3DXVECTOR2(5.0f, 5.0f),
		0,
		D3DCOLOR_RGBA(255, 255, 0, 255)
	),
	&Texture
	(
		CubeTexture,
		{ 0,0 },
		{ 256,256 }
	)
);

//=============================================================
//	����������
//=============================================================
void Main_Initialize(void)
{
	Lighting_Initialize();

	MeshField_Ground_Initialize();	//MeshField�d�l�ύX
	XModel_Initialize();			//XModel�d�l�ύX
	Bullet_Initialize();			//Bullet�̏����� (��菈��)
	Screwdrop_Init();				//�l�W��������
	CTeamProt_Initialize();
	TestSpace_Initialize();	//�e�X�g�X�y�[�X
	Player_Initialize();			
	Cube_Initialize();				//Cube�F��Material�ŊǗ�

	uiSprite = uiSprite;

	srand((UINT)time(NULL));
	
	//XModel_Load("Models/Ps4_Controller2.x");
}

//=============================================================
//	�O �X�V����
//=============================================================
void Main_UpdateBegin(void)
{
	WinSock_Receiver();	//�f�[�^����M���܂��B
	Bullet_Update();	//�e�̍X�V
	Screwdrop_Update();		//�e���Ƃ�����
	//Player_Update();		//GameObject�ōX�V��������
	CTeamProt_Update();		//CTeam�ł̍X�V����
	TestSpace_UpdateBegin();//�e�X�g�X�y�[�X����

}

//=============================================================
//	�`�揈��
//=============================================================
void Main_Render(void)
{
	MeshField_Ground_Render( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), MeshGroundTexture1 );
	CTeamProt_Render();
	TestSpace_Render();

	uiSprite.render.Begin(R2D_SPRITE_ROTATE);
	Bullet_Render();
	Screwdrop_Render();
	//Player_Render();			GameObject�ŕ`���������
	
}


//=============================================================
//	�� ����
//=============================================================
void Main_UpdateEnd()
{
	TestSpace_UpdateEnd();
}

//=============================================================
//	�I������
//=============================================================
void Main_Finalize(void)
{
	TestSpace_Finalize();
	CTeamProt_Finalize();

	MeshField_Ground_Finalize();

}
