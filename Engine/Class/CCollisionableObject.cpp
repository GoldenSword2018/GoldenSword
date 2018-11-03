//
//	CCollisionableObject.cpp
//		Author:HASHIMOTO	DATE:2018/10/19
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//		Name: Yuto Hashimoto DATE: 2018/11/02
//	ShapeSphere�N���X�̃����o,�R���X�g���N�^������
//  ���S���W��������̃A�h���X�Q�ƂɕύX����.
//	GapPos�ɂ��Ă͖������p����.
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"

//class
#include "CCollisionableObject.h"

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================


//===============================================
//	Shape �N���X
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
//	ShapeSphere �N���X
//===============================================

//-------------------------------------
//  �R���X�g���N�^ �f�X�g���N�^
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
//	ShapeCuboid �N���X
//===============================================

//-------------------------------------
//  �R���X�g���N�^ �f�X�g���N�^
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
//	Collision �N���X
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