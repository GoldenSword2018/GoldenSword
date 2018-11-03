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
Shape::Shape( SHAPE_TYPE init_ShapeType )
{
	ShapeType = init_ShapeType;
}
Shape::~Shape()
{
	// null
}

//===============================================
//	ShapeSphere クラス
//===============================================

//-------------------------------------
//  コンストラクタ デストラクタ
//-------------------------------------

ShapeSphere::ShapeSphere( D3DXVECTOR3* init_pParentPos, float init_Radius, D3DXVECTOR3 init_GapPos )
	: Shape( SHAPE_TYPE::SPHERE ),
	 Radius( init_Radius ), GapPos( init_GapPos )
{
	pParentPos = init_pParentPos;
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

ShapeCuboid::ShapeCuboid( D3DXVECTOR3 init_Pos, D3DXVECTOR3 init_Length, D3DXVECTOR3 init_Radian )
	: Shape( SHAPE_TYPE::CUBOID ),
	Pos( init_Pos ), Length( init_Length ), Angle( init_Radian )
{

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
	D3DXVECTOR3 vecLength = *(Sphere0.pParentPos) - *(Sphere1.pParentPos);
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