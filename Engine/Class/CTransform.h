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
//	Transform : 3D専用　クラス
//===============================================
class Transform
{
private:
	static std::vector<Transform*> pIndex;

private:
	bool bConverted;				//変換したか

public :
	Transform* pParent;				//親
	std::vector<Transform*> pChild;	//子

	D3DXMATRIX MtxWorld;		//変換した行列

	//絶対位置
	D3DXVECTOR3 Position;	//位置
	D3DXVECTOR3 Rotation;	//回転
	D3DXVECTOR3 Scale;		//サイズ

	//ワールド空間の情報	
	D3DXVECTOR3 WorldPosition;
	D3DXVECTOR3 WorldRotation;

	//相対位置
	D3DXVECTOR3 localPosition;
	D3DXVECTOR3 localRotation;
	D3DXVECTOR3 lovalScale;

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
	void Set_Parent(Transform* pParent);	//親を設定
	void Release_Parent();					//親と離れる
	void Set_WorldTransform();
	// ワールド座標へのアクセサ
	D3DXVECTOR3 GetWorldPosision( void );
	D3DXMATRIX GetWorldMatrix( void );
	void SetWorldPosition( D3DXVECTOR3 Position );
	void SetLocalPosition( D3DXVECTOR3 Position );
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
