//
//	TestSpace.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/03
//===============================================

//自由に使って

#include<d3dx9.h>
#include"TestSpace.h"
#include"CArmorObject.h"
#include"CStageBlock.h"
#include"CCoreObject.h"

StageBlock **g_ppStageBlocks = NULL;
CoreObject *g_pScrew = NULL;

#include "CStageBlock.h"


StageBlock** g_ppBlock = NULL;
//初期化
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
		D3DXVECTOR3(0.0f, -1.0f, 0.0f)
		);
//	g_pScrew->Set_JudgeType(CoreObject::CORE_JUDGE_TYPE_0);
	/*
	for (int i = 0; i < 100; i++)
	{
		g_pScrew->Set(g_ppStageBlocks[i]);
	}
	*/
};

//前更新
void TestSpace_UpdateBegin() 
{

};

//描画
void TestSpace_Render()
{

};

//後更新
void TestSpace_UpdateEnd() 
{

};

//終了
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