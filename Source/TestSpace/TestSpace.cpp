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

StageBlock **g_ppStageBlocks = NULL;
CoreObject *g_pScrew = NULL;

#include "CStageBlock.h"


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

void Collision_PushBack(ShapeOBB *pShapeMovable, ShapeOBB *pShapeStable)
{
	float diffX = (pShapeStable->pParentPos->x - pShapeMovable->pParentPos->x);		// X���W����
	float diffY = (pShapeStable->pParentPos->y - pShapeMovable->pParentPos->y);		// Y���W����
	float diffZ = (pShapeStable->pParentPos->z - pShapeMovable->pParentPos->z);		// Z���W����

	float absX = fabs(diffX);														// X������Βl
	float absY = fabs(diffY);														// Y������Βl
	float absZ = fabs(diffZ);														// Z������Βl

	float lX = (pShapeStable->Length[0] + pShapeMovable->Length[0]) - absX;			// X�߂荞�ݗ�
	float lY = (pShapeStable->Length[1] + pShapeMovable->Length[1]) - absY;			// Y�߂荞�ݗ�
	float lZ = (pShapeStable->Length[2] + pShapeMovable->Length[2]) - absZ;			// Z�߂荞�ݗ�

	if (lX > lY)
	{
		if (lY > lZ)
		{
			// Z�߂荞�݂���ԏ��Ȃ�
			if (diffZ >= 0)
			{
				// �Œ蕨�������ɂ���
				pShapeMovable->pParentPos->z = pShapeStable->pParentPos->z - (pShapeStable->Length[2] + pShapeMovable->Length[2]);
			}
			else
			{
				// �Œ蕨����O���ɂ���
				pShapeMovable->pParentPos->z = pShapeStable->pParentPos->z + (pShapeStable->Length[2] + pShapeMovable->Length[2]);
			}
		}
		else
		{
			// Y�߂荞�݂���ԏ��Ȃ�
			if (diffY >= 0)
			{
				// �Œ蕨���㑤�ɂ���
				pShapeMovable->pParentPos->y = pShapeStable->pParentPos->y - (pShapeStable->Length[1] + pShapeMovable->Length[1]);
			}
			else
			{
				// �Œ蕨�������ɂ���
				pShapeMovable->pParentPos->y = pShapeStable->pParentPos->y + (pShapeStable->Length[1] + pShapeMovable->Length[1]);
			}
		}
	}
	else
	{
		if (lX > lZ)
		{
			// Z�߂荞�݂���ԏ��Ȃ�
			if (diffZ >= 0)
			{
				// �Œ蕨�������ɂ���
				pShapeMovable->pParentPos->z = pShapeStable->pParentPos->z - (pShapeStable->Length[2] + pShapeMovable->Length[2]);
			}
			else
			{
				// �Œ蕨����O���ɂ���
				pShapeMovable->pParentPos->z = pShapeStable->pParentPos->z + (pShapeStable->Length[2] + pShapeMovable->Length[2]);
			}
		}
		else
		{
			// X�߂荞�݂���ԏ��Ȃ�
			if (diffZ >= 0)
			{
				// �Œ蕨���E���ɂ���
				pShapeMovable->pParentPos->x = pShapeStable->pParentPos->x - (pShapeStable->Length[0] + pShapeMovable->Length[0]);
			}
			else
			{
				// �Œ蕨�������ɂ���
				pShapeMovable->pParentPos->x = pShapeStable->pParentPos->x + (pShapeStable->Length[0] + pShapeMovable->Length[0]);
			}
		}
	}
}
