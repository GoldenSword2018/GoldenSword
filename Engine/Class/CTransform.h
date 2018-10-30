//
//	Transform.h
//		Author:HIROMASA IKEDA	DATE:2018/09/28
//===============================================
#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<d3dx9.h>

//===============================================
//	MatrixTransform : 行列 クラス
//===============================================
class MatrixTransform
{
private:
	D3DXMATRIX MtxWorld;					//ワールド変換行列
	D3DXMATRIX MtxTransform;				//位置
	D3DXMATRIX MtxRotation;					//回転
	D3DXMATRIX MtxScale;					//拡大・縮小
public:
	MatrixTransform();
};

//===============================================
//	Transform : 3D専用　クラス
//===============================================
class Transform
{
private:
	D3DXMATRIX* pParent_Matrix = NULL;	//親変換行列
public :
	//基本情報
	D3DXVECTOR3 Position;	//位置
	D3DXVECTOR3 Scale;		//サイズ
	D3DXVECTOR3 Rotation;	//回転
	D3DCOLOR	Color;		//色
	
	//軸方向
	D3DXVECTOR3 up;			//上
	D3DXVECTOR3 forward;	//前
	D3DXVECTOR3 right;		//右

	//コンストラクタ
	Transform() :Transform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, D3DCOLOR_RGBA(255, 255, 255, 255)){};
	Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation) :Transform(Position, Scale, Rotation, D3DCOLOR_RGBA(255, 255, 255, 255)) {};
	Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation, D3DCOLOR Color);

	~Transform();

	void Set_ParentMatrix(D3DXMATRIX Matrix);
};

//===============================================
//	Transform2 : 2D専用　クラス
//===============================================
class Transform2
{
private:

public:
	D3DXVECTOR2 Position;	//位置
	D3DXVECTOR2 Scale;		//サイズ
	float Rotation;			//回転
	D3DCOLOR Color;			//色

	//コンストラクタ
	Transform2();
	Transform2(D3DXVECTOR2 Position,D3DXVECTOR2 Scale,float Rotation);
	Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation,D3DCOLOR Color);
	
};

#endif
