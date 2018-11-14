//
//	TestSpace.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/03
//===============================================

//���R�Ɏg����

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

//������
void TestSpace_Initialize() 
{

};

//�O�X�V
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

