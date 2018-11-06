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

#define CUBOID_VECTOR_FORWARD		( 0 )
#define CUBOID_VECTOR_RIGHT			( 1 )
#define CUBOID_VECTOR_UP			( 2 )
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
	: Shape( init_pParentPos, init_ShapeType )
{
	GapPos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}
Shape::Shape( D3DXVECTOR3* init_pParentPos, SHAPE_TYPE init_ShapeType )
	:pParentPos( init_pParentPos ), ShapeType( init_ShapeType )
{

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
// arg0: ������̍��W�|�C���^, arg1: �e���W�����̊p�x(���W�A��) �񂷏��� Roll->Pitch->Yaw
// arg2: x��, y����, z���s, arg3: �����蔻��̍��W�Ƃ̍���
ShapeCuboid::ShapeCuboid( D3DXVECTOR3* init_pParentPos, D3DXVECTOR3* init_pRadian, D3DXVECTOR3* init_pLength, D3DXVECTOR3* init_pGapPos )
	: Shape( init_pParentPos, init_pGapPos, SHAPE_TYPE::CUBOID )
{
	// �O�����̒P�ʃx�N�g�����쐬
	D3DXMATRIX mtxRot;
	D3DXMatrixRotationYawPitchRoll( &mtxRot, init_pRadian->y, init_pRadian->x, init_pRadian->z );
	NormalDirect[ CUBOID_VECTOR_FORWARD ] = D3DXVECTOR3( 1.0f, 1.0f, 0.0f );
	D3DXVec3TransformNormal( &NormalDirect[ CUBOID_VECTOR_FORWARD ], &NormalDirect[ CUBOID_VECTOR_FORWARD ], &mtxRot );
	D3DXVec3Normalize( &NormalDirect[ CUBOID_VECTOR_FORWARD ], &NormalDirect[ CUBOID_VECTOR_FORWARD ] );

	// �E�����̒P�ʃx�N�g�����쐬
	D3DXVec3Cross( &NormalDirect[ CUBOID_VECTOR_RIGHT ], &NormalDirect[ CUBOID_VECTOR_UP ], &NormalDirect[ CUBOID_VECTOR_FORWARD ] );
	D3DXVec3Normalize( &NormalDirect[ CUBOID_VECTOR_RIGHT ], &NormalDirect[ CUBOID_VECTOR_RIGHT ] );

	// ������̒P�ʃx�N�g�����쐬
	D3DXVec3Cross( &NormalDirect[ CUBOID_VECTOR_UP ], &NormalDirect[ CUBOID_VECTOR_FORWARD ], &NormalDirect[ CUBOID_VECTOR_RIGHT ] );
	D3DXVec3Normalize( &NormalDirect[ CUBOID_VECTOR_UP ], &NormalDirect[ CUBOID_VECTOR_UP ] );

	// �e�����̒������w��
	Length[ CUBOID_VECTOR_FORWARD ]	= init_pLength->x / 2.0f;
	Length[ CUBOID_VECTOR_RIGHT ]	= init_pLength->y / 2.0f;
	Length[ CUBOID_VECTOR_UP ]		= init_pLength->z / 2.0f;
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
	FLOAT fLength = D3DXVec3LengthSq(&vecLength); // ��̒��S���W�̋���

	if( ( Sphere0.Radius + Sphere1.Radius ) * ( Sphere0.Radius + Sphere1.Radius )  > fLength )
	{ // hit 
		return true;
	}
	else
	{ // no hit
		return false;
	}
}

bool Collision::CuboidVsCuboid( ShapeCuboid& Cuboid0, ShapeCuboid& Cuboid1 )
{

	// �e�����x�N�g���̊m��
	// �iN***:�W���������x�N�g���j
	D3DXVECTOR3 NAe1 = Cuboid0.NormalDirect[ 0 ], Ae1 = NAe1 * Cuboid0.Length[ 0 ];
	D3DXVECTOR3 NAe2 = Cuboid0.NormalDirect[ 1 ], Ae2 = NAe2 * Cuboid0.Length[ 1 ];
	D3DXVECTOR3 NAe3 = Cuboid0.NormalDirect[ 2 ], Ae3 = NAe3 * Cuboid0.Length[ 2 ];
	D3DXVECTOR3 NBe1 = Cuboid1.NormalDirect[ 0 ], Be1 = NBe1 * Cuboid1.Length[ 0 ];
	D3DXVECTOR3 NBe2 = Cuboid1.NormalDirect[ 1 ], Be2 = NBe2 * Cuboid1.Length[ 1 ];
	D3DXVECTOR3 NBe3 = Cuboid1.NormalDirect[ 2 ], Be3 = NBe3 * Cuboid1.Length[ 2 ];
	D3DXVECTOR3 Interval = Cuboid0.GetEffectivePos() - Cuboid1.GetEffectivePos();

	// ������ : Ae1
	FLOAT rA = D3DXVec3Length( &Ae1 );
	FLOAT rB = LenSegOnSeparateAxis( &NAe1, &Be1, &Be2, &Be3 );
	FLOAT L = fabs( D3DXVec3Dot( &Interval, &NAe1 ) );
	if( L > rA + rB )
		return false; // �Փ˂��Ă��Ȃ�

					  // ������ : Ae2
	rA = D3DXVec3Length( &Ae2 );
	rB = LenSegOnSeparateAxis( &NAe2, &Be1, &Be2, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &NAe2 ) );
	if( L > rA + rB )
		return false;

	// ������ : Ae3
	rA = D3DXVec3Length( &Ae3 );
	rB = LenSegOnSeparateAxis( &NAe3, &Be1, &Be2, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &NAe3 ) );
	if( L > rA + rB )
		return false;

	// ������ : Be1
	rA = LenSegOnSeparateAxis( &NBe1, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be1 );
	L = fabs( D3DXVec3Dot( &Interval, &NBe1 ) );
	if( L > rA + rB )
		return false;

	// ������ : Be2
	rA = LenSegOnSeparateAxis( &NBe2, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be2 );
	L = fabs( D3DXVec3Dot( &Interval, &NBe2 ) );
	if( L > rA + rB )
		return false;

	// ������ : Be3
	rA = LenSegOnSeparateAxis( &NBe3, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &NBe3 ) );
	if( L > rA + rB )
		return false;

	// ������ : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross( &Cross, &NAe1, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// ������ : C12
	D3DXVec3Cross( &Cross, &NAe1, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// ������ : C13
	D3DXVec3Cross( &Cross, &NAe1, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// ������ : C21
	D3DXVec3Cross( &Cross, &NAe2, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// ������ : C22
	D3DXVec3Cross( &Cross, &NAe2, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// ������ : C23
	D3DXVec3Cross( &Cross, &NAe2, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// ������ : C31
	D3DXVec3Cross( &Cross, &NAe3, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// ������ : C32
	D3DXVec3Cross( &Cross, &NAe3, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// ������ : C33
	D3DXVec3Cross( &Cross, &NAe3, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;
}

// �������ɓ��e���ꂽ���������瓊�e���������Z�o
float Collision::LenSegOnSeparateAxis( D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 )
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	FLOAT r1 = fabs( D3DXVec3Dot( Sep, e1 ) );
	FLOAT r2 = fabs( D3DXVec3Dot( Sep, e2 ) );
	FLOAT r3 = e3 ? ( fabs( D3DXVec3Dot( Sep, e3 ) ) ) : 0;
	return r1 + r2 + r3;
}