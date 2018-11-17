//
//	TestObj.cpp
//		Author: Yuto Hashimoto	DATE: 11/13/2018
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"

#include "TestObj.h"

//class
#include<d3dx9.h>
#include"input.h"
#include"joycon_input.h"
#include"Debug_font.h"
#include "Debug_Collision.h"
#include"Bullet.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================


//===============================================
//	クラス名		class
//===============================================


//-------------------------------------
//	TestObj
//-------------------------------------

TestObj::TestObj( Transform* pTransform )
:
	GameObject( pTransform, &Texture() ),
	ColShape( &transform.Position, &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), &D3DXVECTOR3( 1.0f, 1.0f, 1.0f ) ),
	Velocity( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) ),
	isOnGround( false )
{

}

void TestObj::Update( void )
{
	if( isOnGround )
	{
		ColShape.Color = D3DCOLOR_RGBA( 255, 0, 0, 255 );
		Velocity.y = 0.0f;
	}
	else
	{
		ColShape.Color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
		Velocity += D3DXVECTOR3( 0.0f, -0.0001f, 0.0f );
	}

	transform.Position += Velocity;

}

void TestObj::Render( void )
{
	DebugCollisionModule::GetInstance()->BatchDraw( &ColShape );
}




//-------------------------------------
//	TestEnvObj
//-------------------------------------



TestEnvObj::TestEnvObj()
:
	GameObject( &Transform( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXVECTOR3( 1.0f, 1.0f, 1.0f ), D3DXVECTOR3( 1.0f, 1.0f, 1.0f ) ), &Texture() ),
	ColShape( &transform.Position, &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), &D3DXVECTOR3( 100.0f, 0.30f, 100.0f ) )
{

}


void TestEnvObj::Update( void )
{
	
}

void TestEnvObj::Render( void )
{
	DebugCollisionModule::GetInstance()->BatchDraw( &ColShape );
}