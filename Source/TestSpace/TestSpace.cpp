//
//	TestSpace.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/03
//===============================================

//自由に使って

#include<d3dx9.h>
#include"TestSpace.h"


#include "TestObj.h"


static TestObj tmp
(
	&Transform
	(
		D3DXVECTOR3( 0.0f, 10.0f, 0.0f ),
		D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f )
	)
);

static TestEnvObj tmpEnv;

//初期化
void TestSpace_Initialize() 
{

};

//前更新
void TestSpace_UpdateBegin() 
{

	if( Collision::OBBVsOBB( tmp.ColShape, tmpEnv.ColShape ) )
	{
		tmp.isOnGround = true;
	}
	else
	{
		tmp.isOnGround = false;
	}
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

