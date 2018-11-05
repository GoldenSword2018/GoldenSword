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

//-------------------------------------
//  �R���X�g���N�^ �f�X�g���N�^
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
//  �������W��߂��֐�
//-------------------------------------

D3DXVECTOR3 Shape::GetEffectivePos( void )const
{
	return *pParentPos + GapPos;
}

//===============================================
//	ShapeSphere �N���X
//===============================================

//-------------------------------------
//  �R���X�g���N�^ �f�X�g���N�^
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
//	ShapeCuboid �N���X
//===============================================

//-------------------------------------
//  �R���X�g���N�^ �f�X�g���N�^
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
//	Collision �N���X
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