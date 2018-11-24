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

void Collision_PushBack(ShapeOBB *pShapeMovable, ShapeOBB *pShapeStable)
{
	float diffX = (pShapeStable->pParentPos->x - pShapeMovable->pParentPos->x);		// X座標差分
	float diffY = (pShapeStable->pParentPos->y - pShapeMovable->pParentPos->y);		// Y座標差分
	float diffZ = (pShapeStable->pParentPos->z - pShapeMovable->pParentPos->z);		// Z座標差分

	float absX = fabs(diffX);														// X差分絶対値
	float absY = fabs(diffY);														// Y差分絶対値
	float absZ = fabs(diffZ);														// Z差分絶対値

	float lX = (pShapeStable->Length[0] + pShapeMovable->Length[0]) - absX;			// Xめり込み量
	float lY = (pShapeStable->Length[1] + pShapeMovable->Length[1]) - absY;			// Yめり込み量
	float lZ = (pShapeStable->Length[2] + pShapeMovable->Length[2]) - absZ;			// Zめり込み量

	if (lX > lY)
	{
		if (lY > lZ)
		{
			// Zめり込みが一番少ない
			if (diffZ >= 0)
			{
				// 固定物が奥側にある
				pShapeMovable->pParentPos->z = pShapeStable->pParentPos->z - (pShapeStable->Length[2] + pShapeMovable->Length[2]);
			}
			else
			{
				// 固定物が手前側にある
				pShapeMovable->pParentPos->z = pShapeStable->pParentPos->z + (pShapeStable->Length[2] + pShapeMovable->Length[2]);
			}
		}
		else
		{
			// Yめり込みが一番少ない
			if (diffY >= 0)
			{
				// 固定物が上側にある
				pShapeMovable->pParentPos->y = pShapeStable->pParentPos->y - (pShapeStable->Length[1] + pShapeMovable->Length[1]);
			}
			else
			{
				// 固定物が下側にある
				pShapeMovable->pParentPos->y = pShapeStable->pParentPos->y + (pShapeStable->Length[1] + pShapeMovable->Length[1]);
			}
		}
	}
	else
	{
		if (lX > lZ)
		{
			// Zめり込みが一番少ない
			if (diffZ >= 0)
			{
				// 固定物が奥側にある
				pShapeMovable->pParentPos->z = pShapeStable->pParentPos->z - (pShapeStable->Length[2] + pShapeMovable->Length[2]);
			}
			else
			{
				// 固定物が手前側にある
				pShapeMovable->pParentPos->z = pShapeStable->pParentPos->z + (pShapeStable->Length[2] + pShapeMovable->Length[2]);
			}
		}
		else
		{
			// Xめり込みが一番少ない
			if (diffZ >= 0)
			{
				// 固定物が右側にある
				pShapeMovable->pParentPos->x = pShapeStable->pParentPos->x - (pShapeStable->Length[0] + pShapeMovable->Length[0]);
			}
			else
			{
				// 固定物が左側にある
				pShapeMovable->pParentPos->x = pShapeStable->pParentPos->x + (pShapeStable->Length[0] + pShapeMovable->Length[0]);
			}
		}
	}
}
