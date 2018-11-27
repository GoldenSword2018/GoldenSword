//
//	TestSpace.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/03
//===============================================

//���R�Ɏg����

#include<d3dx9.h>
#include"TestSpace.h"
#include"CArmorObject.h"
#include"CStageBlock.h"
#include"CCoreObject.h"
#include"CStageBlockList.h"

StageBlock **g_ppStageBlocks = NULL;
CoreObject *g_pScrew = NULL;

StageBlockList* g_pBlockList = NULL;

StageBlock** g_ppBlock = NULL;
//������
void TestSpace_Initialize() 
{
	StageBlock::Initialize();
	g_ppStageBlocks = new StageBlock*[100];
	int index = 0;
	for (int z = 0; z < 10; z++)
	{
		for (int x = 0; x < 10; x++)
		{
			g_ppStageBlocks[index] = new StageBlock(
				&Transform(
					D3DXVECTOR3(x - 5.0f, 0.0f, z - 5.0f),
					D3DXVECTOR3(1.0f, 1.0f, 1.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f)
					),
				0,
				RADIALLY
				);

			index++;
		}
	}
	g_pScrew = new CoreObject(
		&Transform(
			D3DXVECTOR3(0.0f, 0.5f, 0.0f),
			D3DXVECTOR3(1.0f, 1.0f, 1.5f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
		), &Texture(),
		CoreObject::CORE_JUDGE_TYPE_0,
		D3DXVECTOR3(0.0f, 1.0f, 0.0f)
		);
//	g_pScrew->Set_JudgeType(CoreObject::CORE_JUDGE_TYPE_0);
	/*
	for (int i = 0; i < 100; i++)
	{
		g_pScrew->Set(g_ppStageBlocks[i]);
	}
<<<<<<< HEAD

	g_pBlockList = new StageBlockList(D3DXVECTOR3(10.0f, 0.0f, 0.0f), RADIALLY, 0);

	for (int z = 0; z < 10; z++)
	{
		for (int y = 0; y < 10; y++)
		{
			g_pBlockList->CreateBlockRel(D3DXVECTOR3(0, y, z));
		}
	}
=======
	*/
>>>>>>> 35340806847935d02ab1b61f517a16e5226858a6
};

//�O�X�V
void TestSpace_UpdateBegin() 
{

};

//�`��
void TestSpace_Render()
{

};

//��X�V
void TestSpace_UpdateEnd() 
{

};

//�I��
void TestSpace_Finalize() 
{
	if (g_pScrew)
	{
		delete g_pScrew;
		g_pScrew = NULL;
	}
	for (int i = 0; i < 100; i++)
		delete g_ppStageBlocks[i];
	delete[] g_ppStageBlocks;
	StageBlock::Finalize();
};
