//
//	CCollisionableObject.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CCOLLISIONABLEOBJECT_H
#define CCOLLISIONABLEOBJECT_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"

//Class
#include "CGameObject.h"

//================================================
//	�}�N����`	define
//================================================


//================================================
//	�񋓌^		enum
//================================================


//================================================
//	�\����		struct/typedef
//================================================


//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�N���X		class
//================================================

/*
 * Shape Crustor
 */
class Shape
{
public:
	enum SHAPE_TYPE
	{
		SPHERE = 0,
		CUBOID,
		/* MAX ENUM */
		COLLISION_SHAPE_TYPE_ENUM_MAX
	};
public:
	SHAPE_TYPE ShapeType;
private:
	Shape(){}
public:
	Shape( D3DXVECTOR3* pParentPos, D3DXVECTOR3* pGapPos, SHAPE_TYPE ShapeType );
	virtual ~Shape();
public:
	D3DXVECTOR3* pParentPos; // ������̈ʒu�|�C���^ ( �I�u�W�F�N�g������z�� ) // ����v���C�x�[�g�ɂ���H
	D3DXVECTOR3 GapPos; // ������Ƃ̈ʒu�̕␳�i�I�u�W�F�N�g�������炸�炷�j
public:
	D3DXVECTOR3 GetEffectivePos( void )const;
};

//-------------------------------------
class ShapeSphere : public Shape
{
public:
	float Radius;
public:
	ShapeSphere( D3DXVECTOR3* pParentPos, float Radius, D3DXVECTOR3* pGapPos = &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ));
public:
	~ShapeSphere();
};

//-------------------------------------
class ShapeCuboid : public Shape
{
public:
	D3DXVECTOR3 Pos; // �d�S�̍��W
	D3DXVECTOR3 Length;
	D3DXVECTOR3 Angle;
public:
	ShapeCuboid( D3DXVECTOR3* init_pParentPos, D3DXVECTOR3 init_Length, D3DXVECTOR3 init_Radian );
	~ShapeCuboid();
};

/*
 * Collsion Class
 */

class Collision
{
private:
	
public:
	static bool SphereVsSphere( ShapeSphere& Sphere0, ShapeSphere& Sphere1 );
	static bool CuboidVsSphere(ShapeCuboid& Cuboid, ShapeSphere& Sphere) {};
	static bool CuboidVsCuboid(ShapeCuboid& Cuboid0, ShapeCuboid& Cuboid1) {};
};
//-------------------------------------
//	�N���X��
//-------------------------------------

#endif