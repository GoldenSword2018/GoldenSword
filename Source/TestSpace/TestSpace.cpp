//
//	TestSpace.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/03
//===============================================

//���R�Ɏg����

#include<d3dx9.h>
#include"TestSpace.h"

#include "CStageBlock.h"


StageBlock** g_ppBlock = NULL;
//������
void TestSpace_Initialize() 
{
	StageBlock::Initialize();
	g_ppBlock = new StageBlock*[ 100 ];

	for( int bi = 0; bi < 100; bi++ )
	{
		// g_ppBlock[ bi ] = new StageBlock();
	}
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

};

