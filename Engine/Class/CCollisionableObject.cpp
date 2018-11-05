//
//	CCollisionableObject.cpp
//		Author:HASHIMOTO	DATE:2018/10/19
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//		Name: Yuto Hashimoto DATE: 2018/11/02
//	ShapeSphereクラスのメンバ,コンストラクタを改変
//  中心座標を持ち主のアドレス参照に変更した.
//	GapPosについては未だ活用せず.
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"

//class
#include "CCollisionableObject.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================


//===============================================
//	Shape クラス
//===============================================

//-------------------------------------
//  コンストラクタ デストラクタ
//-------------------------------------

Shape::Shape( D3DXVECTOR3* init_pParentPos, D3DXVECTOR3* init_GapPos, SHAPE_TYPE init_ShapeType )
{
	pParentPos = init_pParentPos;
	GapPos = *init_GapPos;
	ShapeType = init_ShapeType;
}
Shape::~Shape()
{
	// null
}

//-------------------------------------
//  実効座標を戻す関数
//-------------------------------------

D3DXVECTOR3 Shape::GetEffectivePos( void )const
{
	return *pParentPos + GapPos;
}

//===============================================
//	ShapeSphere クラス
//===============================================

//-------------------------------------
//  コンストラクタ デストラクタ
//-------------------------------------

ShapeSphere::ShapeSphere( D3DXVECTOR3* init_pParentPos, float init_Radius, D3DXVECTOR3* init_GapPos )
	: Shape( init_pParentPos, init_GapPos, SHAPE_TYPE::SPHERE )
{
	Radius = init_Radius;
}
ShapeSphere::~ShapeSphere()
{
	// null
}

//===============================================
//	ShapeCuboid クラス
//===============================================

//-------------------------------------
//  コンストラクタ デストラクタ
//-------------------------------------

ShapeCuboid::ShapeCuboid( D3DXVECTOR3* init_pParentPos, D3DXVECTOR3 init_Length, D3DXVECTOR3 init_Radian )
	: Shape( init_pParentPos, &init_Length, SHAPE_TYPE::CUBOID )
{
	Length = init_Length;
	Angle = init_Radian;
}

ShapeCuboid::~ShapeCuboid()
{
	// null
}

//===============================================
//	Collision クラス
//===============================================


bool Collision::SphereVsSphere( ShapeSphere& Sphere0, ShapeSphere& Sphere1 )
{
	D3DXVECTOR3 vecLength =Sphere1.GetEffectivePos() - Sphere0.GetEffectivePos();
	FLOAT fLength = D3DXVec3LengthSq(&vecLength);
	if( ( Sphere0.Radius + Sphere1.Radius ) * ( Sphere0.Radius + Sphere1.Radius )  > fLength )
	{ // hit 
		return true;
	}
	else
	{ // no hit
		return false;
	}
}