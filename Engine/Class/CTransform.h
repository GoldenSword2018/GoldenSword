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
	//全Transformを格納
	static std::vector<Transform*> pIndex;

private:
	bool bConverted;				//変換したか

public :
	Transform* pParent;				//親
	std::vector<Transform*> pChild;	//子

	D3DXMATRIX MtxWorld;		//変換した行列


	//空間位置(ワールド空間上での位置などを保持します)
	//親の位置などを演算した結果
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;		//Radian
	D3DXVECTOR3 Scale;

	//基本位置(自身の位置などを保持します)
	D3DXVECTOR3 localPosition;
	D3DXVECTOR3 localRotation;
	D3DXVECTOR3 localScale;

	D3DCOLOR	Color;		//色
	
	//方向
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
	//Get

	//Set

//	回転関数
//	forwardなどの方向の値が狂うので基本はこの関数群を使う
public:
	void Rotation(const D3DXVECTOR3 value);
	void RotationAxis(const D3DXVECTOR3 Axis, const float value);

public:

	D3DXMATRIX Convert();					//変換開始
	void Adjustment_Rotation();
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
