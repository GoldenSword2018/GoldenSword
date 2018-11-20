//
//	TestSpace.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/03
//===============================================

//自由に使って

#include<d3dx9.h>
#include"TestSpace.h"

#include "CStageBlock.h"


StageBlock** g_ppBlock = NULL;
//初期化
void TestSpace_Initialize() 
{
	StageBlock::Initialize();
	g_ppBlock = new StageBlock*[ 100 ];

	for( int bi = 0; bi < 100; bi++ )
	{
		// g_ppBlock[ bi ] = new StageBlock();
	}
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

};

