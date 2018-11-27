//
//	Transform.h
//		Author:HIROMASA IKEDA	DATE:2018/09/28
//===============================================
#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<d3dx9.h>
#include<vector>

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
	
	static std::vector<Transform*> pIndex;
public :
	bool bConverted;			//変換したか
	Transform* pParent;		//親
	std::vector<Transform*> pChild;	//子
	D3DXMATRIX MtxWorld;		//変換した行列

	//基本情報
	D3DXVECTOR3 Position;	//位置
	D3DXVECTOR3 Scale;		//サイズ
	D3DXVECTOR3 Rotation;	//回転

	//ワールド空間の情報	
	//	pParent->transform.position + this->transform.position;
	D3DXVECTOR3 WorldPosition;
	D3DXVECTOR3 WorldRotation;

	D3DCOLOR	Color;		//色
	
	//軸方向
	D3DXVECTOR3 up;			//上
	D3DXVECTOR3 forward;	//前
	D3DXVECTOR3 right;		//右

public:
	static void ResetConvert();

public:
	
	//コンストラクタ
	Transform() :Transform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, D3DCOLOR_RGBA(255, 255, 255, 255)){};
	Transform(D3DCOLOR Color) :Transform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, Color) {};
	Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation) :Transform(Position, Scale, Rotation, D3DCOLOR_RGBA(255, 255, 255, 255)) {};
	Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation, D3DCOLOR Color);

	//デストラクタ
	~Transform();

public:

	D3DXMATRIX Convert();					//変換開始
	void Set_Parent(Transform* pParent);		//親を設定
	void Release_Parent();					//親と離れる
	void Set_WorldTransform();
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
