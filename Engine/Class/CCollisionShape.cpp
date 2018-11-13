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
//		Name: Yuto Hashimoto DATE: 2018/11/06
//	ShapeSphere�N���X������( ? )
//  Collision�N���X��OBBvsOBB�̏Փ˔��������

//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"

//class
#include "CCollisionShape.h"
#include "Debug_Collision.h"
//===============================================
//	�}�N����`		define
//===============================================

#define COLLISION_SHAPE_DEFAULT_POS	( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) )
#define COLLISION_SHAPE_DEFAULT_COLOR ( D3DCOLOR_RGBA( 255, 255, 255, 255 ))
//===============================================
//	�O���[�o���ϐ�	global
//===============================================


//===============================================
//	Shape �N���X
//===============================================

//-------------------------------------
//  �R���X�g���N�^ �f�X�g���N�^
//-------------------------------------
Shape::Shape()
	: Shape( &COLLISION_SHAPE_DEFAULT_POS, &COLLISION_SHAPE_DEFAULT_POS,NO_TYPE )
{

}
Shape::Shape( D3DXVECTOR3* init_pParentPos, D3DXVECTOR3* init_pGapPos, SHAPE_TYPE init_ShapeType, D3DCOLOR init_Color )
:
	pParentPos( init_pParentPos ),
	GapPos( *init_pGapPos ),
	ShapeType( init_ShapeType ),
	Color( init_Color )
{

}
Shape::Shape( D3DXVECTOR3* init_pParentPos, D3DXVECTOR3* init_GapPos, SHAPE_TYPE init_ShapeType )
: 
	Shape( init_pParentPos, init_GapPos, init_ShapeType, COLLISION_SHAPE_DEFAULT_COLOR )
{

}
Shape::Shape( D3DXVECTOR3* init_pParentPos, SHAPE_TYPE init_ShapeType )
:
	Shape( init_pParentPos, &COLLISION_SHAPE_DEFAULT_POS, init_ShapeType, COLLISION_SHAPE_DEFAULT_COLOR )
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
ShapeSphere::ShapeSphere()
	: Shape(),
	Radius( 0.0f )
{

}
ShapeSphere::ShapeSphere( D3DXVECTOR3* init_pParentPos, float init_Radius, D3DXVECTOR3* init_GapPos )
	: Shape( init_pParentPos, init_GapPos, SHAPE_TYPE::SPHERE ),
	Radius( init_Radius )
{

}
ShapeSphere::~ShapeSphere()
{
	// null
}


//-------------------------------------
//  �f�o�b�O�`��
//-------------------------------------
void ShapeSphere::DebugDraw()
{
	DebugCollisionModule::BatchDrawSphere( this );
}
//===============================================
//	ShapeOBB �N���X
//===============================================

//-------------------------------------
//  �R���X�g���N�^ �f�X�g���N�^
//-------------------------------------
ShapeOBB::ShapeOBB()
	:Shape( &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), SHAPE_TYPE::OBB )
{
	NormalDirect[ 0 ] = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	NormalDirect[ 1 ] = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	NormalDirect[ 2 ] = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	
	Length[ 0 ] = 0.0f;
	Length[ 1 ] = 0.0f;
	Length[ 2 ] = 0.0f;
}
// arg0: ������̍��W�|�C���^, arg1: �e���W�����̊p�x(���W�A��) �񂷏��� Roll->Pitch->Yaw
// arg2: x��, y����, z���s, arg3: �����蔻��̍��W�Ƃ̍���
ShapeOBB::ShapeOBB( D3DXVECTOR3* init_pParentPos, D3DXVECTOR3* init_pRadian, D3DXVECTOR3* init_pLength, D3DXVECTOR3* init_pGapPos )
	: Shape( init_pParentPos, init_pGapPos, SHAPE_TYPE::OBB )
{
	D3DXMATRIX mtxRot;
	D3DXMatrixRotationYawPitchRoll( &mtxRot, D3DXToRadian( init_pRadian->y ), D3DXToRadian( init_pRadian->x ), D3DXToRadian( init_pRadian->z ) );

	// �O�����̒P�ʃx�N�g�����쐬
	NormalDirect[ OBB_VECTOR_FORWARD ] = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	D3DXVec3TransformNormal( &NormalDirect[ OBB_VECTOR_FORWARD ], &NormalDirect[ OBB_VECTOR_FORWARD ], &mtxRot );
	D3DXVec3Normalize( &NormalDirect[ OBB_VECTOR_FORWARD ], &NormalDirect[ OBB_VECTOR_FORWARD ] );


	// �E�����̒P�ʃx�N�g�����쐬
	NormalDirect[ OBB_VECTOR_RIGHT ] = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	D3DXVec3TransformNormal( &NormalDirect[ OBB_VECTOR_RIGHT ], &NormalDirect[ OBB_VECTOR_RIGHT ], &mtxRot );
	D3DXVec3Normalize( &NormalDirect[ OBB_VECTOR_RIGHT ], &NormalDirect[ OBB_VECTOR_RIGHT ] );

	// ������̒P�ʃx�N�g�����쐬
	NormalDirect[ OBB_VECTOR_UP ] = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	D3DXVec3TransformNormal( &NormalDirect[ OBB_VECTOR_UP ], &NormalDirect[ OBB_VECTOR_UP ], &mtxRot );
	D3DXVec3Normalize( &NormalDirect[ OBB_VECTOR_UP ], &NormalDirect[ OBB_VECTOR_UP ] );


	// �e�����̒������w��
	Length[ OBB_VECTOR_FORWARD ] = init_pLength->z / 2.0f;
	Length[ OBB_VECTOR_RIGHT ] = init_pLength->x / 2.0f;
	Length[ OBB_VECTOR_UP ] = init_pLength->y / 2.0f;
}

ShapeOBB::~ShapeOBB()
{
	// null
}

//-------------------------------------
//  �f�o�b�O�`��
//-------------------------------------
void ShapeOBB::DebugDraw()
{
	DebugCollisionModule::BatchDrawCuboid( this );
}
//===============================================
//	Collision �N���X
//===============================================


bool Collision::SphereVsSphere( ShapeSphere& Sphere0, ShapeSphere& Sphere1 )
{
	D3DXVECTOR3 vecLength =Sphere1.GetEffectivePos() - Sphere0.GetEffectivePos();
	float fLength = D3DXVec3LengthSq(&vecLength); // ��̒��S���W�̋���

	if( ( Sphere0.Radius + Sphere1.Radius ) * ( Sphere0.Radius + Sphere1.Radius )  > fLength )
	{ // hit 
		return true;
	}
	else
	{ // no hit
		return false;
	}
}

bool Collision::OBBVsOBB( ShapeOBB& OBB0, ShapeOBB& OBB1 )
{

	// �e�����x�N�g���̊m��
	// �iN***:�W���������x�N�g���j
	D3DXVECTOR3 NAe1 = OBB0.NormalDirect[ 0 ], Ae1 = NAe1 * OBB0.Length[ 0 ];
	D3DXVECTOR3 NAe2 = OBB0.NormalDirect[ 1 ], Ae2 = NAe2 * OBB0.Length[ 1 ];
	D3DXVECTOR3 NAe3 = OBB0.NormalDirect[ 2 ], Ae3 = NAe3 * OBB0.Length[ 2 ];
	D3DXVECTOR3 NBe1 = OBB1.NormalDirect[ 0 ], Be1 = NBe1 * OBB1.Length[ 0 ];
	D3DXVECTOR3 NBe2 = OBB1.NormalDirect[ 1 ], Be2 = NBe2 * OBB1.Length[ 1 ];
	D3DXVECTOR3 NBe3 = OBB1.NormalDirect[ 2 ], Be3 = NBe3 * OBB1.Length[ 2 ];
	D3DXVECTOR3 Interval = OBB0.GetEffectivePos() - OBB1.GetEffectivePos();

	// ������ : Ae1
	float rA = D3DXVec3Length( &Ae1 );
	float rB = LenSegOnSeparateAxis( &NAe1, &Be1, &Be2, &Be3 );
	float L = fabs( D3DXVec3Dot( &Interval, &NAe1 ) );
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
	float r1 = fabs( D3DXVec3Dot( Sep, e1 ) );
	float r2 = fabs( D3DXVec3Dot( Sep, e2 ) );
	float r3 = e3 ? ( fabs( D3DXVec3Dot( Sep, e3 ) ) ) : 0;
	return r1 + r2 + r3;
}