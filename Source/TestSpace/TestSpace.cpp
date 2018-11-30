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
#include "CStageBlockList.h"

StageBlockList* g_pBlockA;
StageBlockList* g_pBlockB;
StageBlockList* g_pBlockC;
StageBlockList* g_pBlockD;
StageBlockList* g_pBlockE;
StageBlockList* g_pBlockF;
StageBlockList* g_pBlockG;
StageBlockList* g_pBlockH;
StageBlockList* g_pBlockI;
StageBlockList* g_pBlockJ;
StageBlockList* g_pBlockK;
StageBlockList* g_pBlockL;
StageBlockList* g_pBlockM;
StageBlockList* g_pBlockN;
StageBlockList* g_pBlockO;
StageBlockList* g_pBlockP;
StageBlockList* g_pBlockQ;
StageBlockList* g_pBlockR;

CoreObject *g_pScrewA = NULL;
CoreObject *g_pScrewB = NULL;
CoreObject *g_pScrewC = NULL;
CoreObject *g_pScrewD = NULL;
CoreObject *g_pScrewE = NULL;
CoreObject *g_pScrewF = NULL;
CoreObject *g_pScrewG = NULL;
CoreObject *g_pScrewH = NULL;
CoreObject *g_pScrewI = NULL;
CoreObject *g_pScrewJ = NULL;
CoreObject *g_pScrewK = NULL;
CoreObject *g_pScrewL = NULL;
CoreObject *g_pScrewM = NULL;
CoreObject *g_pScrewN = NULL;
CoreObject *g_pScrewO = NULL;
CoreObject *g_pScrewP = NULL;
CoreObject *g_pScrewQ = NULL;
CoreObject *g_pScrewR = NULL;


StageBlock** g_ppBlock = NULL;

StageBlockList* g_pBlockTest = NULL;
//初期化
void TestSpace_Initialize() 
{
	StageBlock::Initialize();

	//g_ppStageBlocks = new StageBlock*[100];
	//int index = 0;
	//for (int z = 0; z < 10; z++)
	//{
	//	for (int x = 0; x < 10; x++)
	//	{
	//		g_ppStageBlocks[index] = new StageBlock(
	//			&Transform(
	//				D3DXVECTOR3(x - 5.0f, 0.0f, z - 5.0f),
	//				D3DXVECTOR3(1.0f, 1.0f, 1.0f),
	//				D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//				),
	//			0,
	//			RADIALLY
	//			);

	//		index++;
	//	}
	//}

	g_pScrew = new CoreObject(
		&Transform(
			D3DXVECTOR3(0.0f, 0.5f, 0.0f),
			D3DXVECTOR3(1.0f, 1.0f, 1.5f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
		), &Texture(),
		CoreObject::CORE_JUDGE_TYPE_0,
		D3DXVECTOR3(0.0f, -1.0f, 0.0f)
		);

	
	//for (int i = 0; i < 100; i++)
	//{
	//	g_pScrew->Set(g_ppStageBlocks[i]);
	//}
	

	//以下失敗・・・
	g_pBlockA = new StageBlockList(D3DXVECTOR3(-34, 1, 23), RADIALLY, 0);

	for (float x = 0; x < 2; x++)
	{
		for (float z = 0; z < 2; z++)
		{
			for (float y = 0; y < 15; y++)
			{

				g_pBlockA->CreateBlockRel(D3DXVECTOR3(x, y, z));
			}
		}

	}
	g_pScrewA = new CoreObject(
		&Transform(
			D3DXVECTOR3(-32.5, 6, 23),
			D3DXVECTOR3(1.0f, 1.0f, 1.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
		), &Texture(),
		CoreObject::CORE_JUDGE_TYPE_0,
		D3DXVECTOR3(1.0f, 0.0f, 0.0f)
	);
	g_pBlockA->SetAll(g_pScrewA);

	//g_pBlockB = new StageBlockList(D3DXVECTOR3(-34, 1, 12), RADIALLY, 0);
	//for (int x = 0; x < 4; x++)
	//{
	//	for (int z = 0; z < 4; z++)
	//	{
	//		for (int y = 0; y < 14; y++)
	//		{
	//			g_pBlockB->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//g_pScrewB = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(-30.5, 6, 14),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(1.0f, 0.0f, 0.0f)
	//);
	//g_pBlockB->SetAll(g_pScrewB);

	//g_pBlockC = new StageBlockList(D3DXVECTOR3(-42, 1, -24), RADIALLY, 0);
	//for (int x = 0; x < 7; x++)
	//{
	//	for (int z = 0; z < 20; z++)
	//	{
	//		for (int y = 0; y < 4; y++)
	//		{
	//			g_pBlockC->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//for (int x = 0; x < 7; x++)
	//{
	//	for (int z = 0; z < 5; z++)
	//	{
	//		for (int y = 4; y < 7; y++)
	//		{
	//			g_pBlockC->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//for (int x = 0; x < 7; x++)
	//{
	//	for (int z = 14; z < 20; z++)
	//	{
	//		for (int y = 4; y < 7; y++)
	//		{
	//			g_pBlockC->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//g_pScrewC = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(-35.5, 4, -22),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(1.0f, 0.0f, 0.0f)
	//);
	//g_pBlockC->SetAll(g_pScrewC);

	//g_pBlockD = new StageBlockList(D3DXVECTOR3(-23, 1, 27), RADIALLY, 0);
	//for (int x = 0; x < 14; x++)
	//{
	//	for (int z = 0; z < 4; z++)
	//	{
	//		for (int y = 0; y < 11; y++)
	//		{
	//			g_pBlockD->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//g_pScrewD = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(-23.5f, 6.0f, 28.5f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(-1.0f, 0.0f, 0.0f)
	//);
	//g_pBlockD->SetAll(g_pScrewD);


	//g_pBlockE = new StageBlockList(D3DXVECTOR3(-12, 1, 12), RADIALLY, 0);
	//for (int x = 0; x < 11; x++)
	//{
	//	for (int z = 0; z < 34; z++)
	//	{
	//		for (int y = 0; y < 13; y++)
	//		{
	//			g_pBlockE->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//g_pScrewE = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(-1.5f, 6.5f, 35.0f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(1.0f, 0.0f, 0.0f)
	//);
	//g_pBlockE->SetAll(g_pScrewE);

	//g_pBlockF = new StageBlockList(D3DXVECTOR3(-8, 1, -4), RADIALLY, 0);

	//for (int z = 0; z < 18; z++)
	//{
	//	for (int y = 0; y < 10; y++)
	//	{
	//		g_pBlockF->CreateBlockRel(D3DXVECTOR3(0, y, z));
	//	}
	//}

	//g_pScrewF = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(-8.5f, 5.5f, 4.5f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(-1.0f, 0.0f, 0.0f)
	//);
	//g_pBlockF->SetAll(g_pScrewF);


	//g_pBlockG = new StageBlockList(D3DXVECTOR3(-8, 1, -34), RADIALLY, 0);

	//for (int z = 0; z < 17; z++)
	//{
	//	for (int y = 0; y < 10; y++)
	//	{
	//		g_pBlockG->CreateBlockRel(D3DXVECTOR3(0, y, z));
	//	}
	//}

	//g_pScrewG = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(-8.5f, 5.5f, -26.0f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(-1.0f, 0.0f, 0.0f)
	//);
	//g_pBlockG->SetAll(g_pScrewG);

	//g_pBlockH = new StageBlockList(D3DXVECTOR3(-17, 1, -41), RADIALLY, 0);
	//for (int x = 0; x < 17; x++)
	//{
	//	for (int z = 0; z < 4; z++)
	//	{
	//		for (int y = 0; y < 6; y++)
	//		{
	//			g_pBlockH->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}

	//g_pScrewH = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(-9.0f, 3.5f, -41.5f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(0.0f, 0.0f, -1.0f)
	//);
	//g_pBlockH->SetAll(g_pScrewH);

	//g_pBlockI = new StageBlockList(D3DXVECTOR3(-1, 1, 26), RADIALLY, 0);
	//for (int x = 0; x < 19; x++)
	//{
	//	for (int y = 0; y < 8; y++)
	//	{
	//		g_pBlockI->CreateBlockRel(D3DXVECTOR3(x, y, 0));
	//	}
	//}
	//g_pScrewI = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(17.0f, 4.5f, 25.5f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(0.0f, 0.0f, -1.0f)
	//);
	//g_pBlockI->SetAll(g_pScrewI);

	//g_pBlockJ = new StageBlockList(D3DXVECTOR3(6, 1, -3), RADIALLY, 0);
	//for (int x = 0; x < 10; x++)
	//{
	//	for (int y = 0; y < 8; y++)
	//	{
	//		g_pBlockJ->CreateBlockRel(D3DXVECTOR3(x, y, 0));
	//	}
	//}
	//for (int z = 1; z < 5; z++)
	//{
	//	for (int y = 0; y < 8; y++)
	//	{
	//		g_pBlockJ->CreateBlockRel(D3DXVECTOR3(0, y, z));
	//	}
	//}
	//for (int z = 10; z < 15; z++)
	//{
	//	for (int y = 0; y < 8; y++)
	//	{
	//		g_pBlockJ->CreateBlockRel(D3DXVECTOR3(0, y, z));
	//	}
	//}
	//for (int x = 0; x < 10; x++)
	//{
	//	for (int y = 0; y < 8; y++)
	//	{
	//		g_pBlockJ->CreateBlockRel(D3DXVECTOR3(x, y, 15));
	//	}
	//}
	//for (int z = 1; z < 15; z++)
	//{
	//	for (int y = 0; y < 8; y++)
	//	{
	//		g_pBlockJ->CreateBlockRel(D3DXVECTOR3(9, y, z));
	//	}
	//}
	//for (int x = 0; x < 10; x++)
	//{
	//	for (int z = 0; z < 16; z++)
	//	{
	//		g_pBlockJ->CreateBlockRel(D3DXVECTOR3(x, 8, z));
	//	}
	//}
	//g_pScrewJ = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(15.5f, 4.5f, 4.5f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(1.0f, 0.0f, 0.0f)
	//);
	////g_pBlockJ->SetAll(g_pScrewJ);

	//g_pBlockK = new StageBlockList(D3DXVECTOR3(8, 9, -23), RADIALLY, 0);
	//for (int x = 0; x < 4; x++)
	//{
	//	for (int z = 0; z < 20; z++)
	//	{
	//		g_pBlockK->CreateBlockRel(D3DXVECTOR3(x, 0, z));
	//	}
	//}
	//for (int x = 0; x < 4; x++)
	//{
	//	for (int z = 15; z < 23; z++)
	//	{
	//		g_pBlockK->CreateBlockRel(D3DXVECTOR3(x, 1, z));
	//	}
	//}
	//g_pScrewK = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(11.5f, 9.0f, -12.0f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(1.0f, 0.0f, 0.0f)
	//);
	//g_pBlockK->SetAll(g_pScrewK);


	//g_pBlockL = new StageBlockList(D3DXVECTOR3(6, 1, -27), RADIALLY, 0);
	//for (int x = 0; x < 8; x++)
	//{
	//	for (int z = 0; z < 9; z++)
	//	{
	//		for (int y = 0; y < 8; y++)
	//		{
	//			g_pBlockL->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//int nL = 7;
	//for (int x = 8; x < 15; x++)
	//{
	//	for (int z = 0; z < 9; z++)
	//	{
	//		for (int y = 0; y < nL; y++)
	//		{
	//			g_pBlockL->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//	nL--;
	//}
	//g_pScrewL = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(5.5f, 5.0f, -23.0f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(-1.0f, 0.0f, 0.0f)
	//);
	//g_pBlockL->SetAll(g_pScrewL);

	//g_pBlockM = new StageBlockList(D3DXVECTOR3(10, 1, -38), RADIALLY, 0);
	//for (int x = 0; x < 8; x++)
	//{
	//	for (int z = 0; z < 14; z++)
	//	{
	//		for (int y = 0; y < 11; y++)
	//		{
	//			g_pBlockM->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//g_pScrewM = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(9.5f, 6.0f, -34.0f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(-1.0f, 0.0f, 0.0f)
	//);
	//g_pBlockM->SetAll(g_pScrewM);

	//g_pBlockN = new StageBlockList(D3DXVECTOR3(15, 1, -47), RADIALLY, 0);
	//for (int x = 0; x < 8; x++)
	//{
	//	for (int z = 0; z < 11; z++)
	//	{
	//		for (int y = 0; y < 8; y++)
	//		{
	//			g_pBlockN->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//g_pScrewN = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(18.5f, 4.5f, -47.5f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(0.0f, 0.0f, -1.0f)
	//);
	//g_pBlockN->SetAll(g_pScrewN);


	//g_pBlockO = new StageBlockList(D3DXVECTOR3(26, 1, 24), RADIALLY, 0);
	//for (int x = 0; x < 10; x++)
	//{
	//	for (int y = 0; y < 8; y++)
	//	{
	//		g_pBlockO->CreateBlockRel(D3DXVECTOR3(x, y, 0));
	//	}
	//}
	//for (int z = 1; z < 8; z++)
	//{
	//	for (int y = 0; y < 8; y++)
	//	{
	//		g_pBlockO->CreateBlockRel(D3DXVECTOR3(0, y, z));
	//	}
	//}
	//for (int z = 12; z < 18; z++)
	//{
	//	for (int y = 0; y < 8; y++)
	//	{
	//		g_pBlockO->CreateBlockRel(D3DXVECTOR3(0, y, z));
	//	}
	//}
	//for (int x = 0; x < 10; x++)
	//{
	//	for (int y = 0; y < 8; y++)
	//	{
	//		g_pBlockO->CreateBlockRel(D3DXVECTOR3(x, y, 18));
	//	}
	//}
	//for (int z = 1; z < 18; z++)
	//{
	//	for (int y = 0; y < 8; y++)
	//	{
	//		g_pBlockO->CreateBlockRel(D3DXVECTOR3(9, y, z));
	//	}
	//}
	//for (int x = 0; x < 10; x++)
	//{
	//	for (int z = 0; z < 19; z++)
	//	{
	//		g_pBlockO->CreateBlockRel(D3DXVECTOR3(x, 8, z));
	//	}
	//}
	//g_pScrewO = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(25.5f, 9.0f, 33.5f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(-1.0f, 0.0f, 0.0f)
	//);
	//g_pBlockO->SetAll(g_pScrewO);

	//g_pBlockP = new StageBlockList(D3DXVECTOR3(32, 1, -16), RADIALLY, 0);
	//int nP1 = 0;
	//for (int z = 0; z < 8; z++)
	//{
	//	for (int x = 0; x < 7; x++)
	//	{
	//		for (int y = 0; y <= nP1; y++)
	//		{
	//			g_pBlockP->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//	nP1++;
	//}
	//for (int x = 0; x < 7; x++)
	//{
	//	for (int z = 7; z < 18; z++)
	//	{
	//		for (int y = 0; y < 8; y++)
	//		{
	//			g_pBlockP->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//int nP2 = 7;
	//for (int z = 18; z < 25; z++)
	//{
	//	for (int x = 0; x < 7; x++)
	//	{
	//		for (int y = 0; y < nP2; y++)
	//		{
	//			g_pBlockP->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//	nP2--;
	//}
	//for (int z = 8; z < 18; z++)
	//{
	//	for (int y = 8; y < 12; y++)
	//	{
	//		g_pBlockP->CreateBlockRel(D3DXVECTOR3(0, y, z));
	//	}
	//}
	//g_pScrewP = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(31.5f, 5.0f, -4.0f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(-1.0f, 0.0f, 0.0f)
	//);
	//g_pBlockP->SetAll(g_pScrewP);

	//g_pBlockQ = new StageBlockList(D3DXVECTOR3(31, 1, -38), RADIALLY, 0);
	//for (int x = 0; x < 6; x++)
	//{
	//	for (int z = 0; z < 8; z++)
	//	{
	//		for (int y = 0; y < 8; y++)
	//		{
	//			g_pBlockQ->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//for (int x = 1; x < 4; x++)
	//{
	//	for (int z = 1; z < 7; z++)
	//	{
	//		for (int y = 8; y < 10; y++)
	//		{
	//			g_pBlockQ->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//for (int x = 0; x < 6; x++)
	//{
	//	for (int z = 0; z < 8; z++)
	//	{
	//		for (int y = 10; y < 16; y++)
	//		{
	//			g_pBlockQ->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//for (int x = 1; x < 4; x++)
	//{
	//	for (int z = 1; z < 7; z++)
	//	{
	//		for (int y = 16; y < 18; y++)
	//		{
	//			g_pBlockQ->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//for (int x = 0; x < 6; x++)
	//{
	//	for (int z = 0; z < 8; z++)
	//	{
	//		for (int y = 18; y < 23; y++)
	//		{
	//			g_pBlockQ->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//for (int x = 1; x < 4; x++)
	//{
	//	for (int z = 1; z < 7; z++)
	//	{
	//		for (int y = 23; y < 25; y++)
	//		{
	//			g_pBlockQ->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//for (int x = 0; x < 6; x++)
	//{
	//	for (int z = 0; z < 8; z++)
	//	{
	//		for (int y = 25; y < 29; y++)
	//		{
	//			g_pBlockQ->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//for (int x = 1; x < 5; x++)
	//{
	//	for (int z = 2; z < 6; z++)
	//	{
	//		g_pBlockQ->CreateBlockRel(D3DXVECTOR3(x, 29, z));
	//	}
	//}
	//for (int x = 2; x < 4; x++)
	//{
	//	for (int z = 3; z < 5; z++)
	//	{
	//		for (int y = 30; y < 32; y++)
	//		{
	//			g_pBlockQ->CreateBlockRel(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//}
	//g_pScrewQ = new CoreObject(
	//	&Transform(
	//		D3DXVECTOR3(30.5f, 15.0f, -34.5f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.5f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	//	), &Texture(),
	//	CoreObject::CORE_JUDGE_TYPE_0,
	//	D3DXVECTOR3(-1.0f, 0.0f, 0.0f)
	//);
	//g_pBlockQ->SetAll(g_pScrewQ);

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
	}/*
	for (int i = 0; i < 100; i++)
		delete g_ppStageBlocks[i];
	delete[] g_ppStageBlocks;*/
	StageBlock::Finalize();
};