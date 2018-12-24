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

public:
	static void g_Convert();

private:
	bool m_bEnable_Convert;			//変換が有効
	bool m_bConverted;				//変換したか

private:
	Transform* m_pParent;				//親
	std::vector<Transform*> m_pChild;	//子

	//行列
	D3DXMATRIX m_MtxTransform;
	D3DXMATRIX m_MtxScale;
	D3DXMATRIX m_MtxRotation;
	D3DXMATRIX m_MtxWorld;

	//ローカル情報
	D3DXVECTOR3 m_Position;			//位置
	D3DXVECTOR3 m_Rotation;			//回転　Radian
	D3DXVECTOR3 m_Scale;				//大きさ

public:
	//コンストラクタ
	Transform() :Transform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }) {};
	Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation);

	//デストラクタ
	~Transform();

private:
	D3DXMATRIX Convert();					//行列変換開始

public: //方向

	D3DXVECTOR3 Get_Up();				//上方向
	D3DXVECTOR3 Get_Forward();			//前方向
	D3DXVECTOR3 Get_Right();			//右方向

public:	//行列

	//ポインター型
	D3DXMATRIX* MtxTransform();
	D3DXMATRIX* MtxScale();
	D3DXMATRIX* MtxRotation();
	D3DXMATRIX* MtxWorld();

	D3DXMATRIX Get_MtxTransform();		//位置行列
	D3DXMATRIX Get_MtxScale();			//回転行列
	D3DXMATRIX Get_MtxRotation();		//大きさ行列
	D3DXMATRIX Get_MtxWorld();			//空間行列

	void Set_MtxTransform(D3DXMATRIX MtxTransform);
	void Set_MtxScale(D3DXMATRIX MtxScale);
	void Set_MtxRotation(D3DXMATRIX MtxRotation);
	void Set_MtxWorld(D3DXMATRIX MtxWorld);

	D3DXMATRIX Get_localMtxTransform();	//位置行列
	D3DXMATRIX Get_localMtxScale();		//回転行列
	D3DXMATRIX Get_localMtxRotation();	//大きさ行列
	D3DXMATRIX Get_localMtxWorld();		//空間行列

public:	//ワールド情報
	
	//ポインター型
	D3DXVECTOR3* Position();
	D3DXVECTOR3* Rotation();
	D3DXVECTOR3* Scale();

	D3DXVECTOR3 Get_Position();		//位置情報
	D3DXVECTOR3 Get_Rotation();		//回転情報
	D3DXVECTOR3 Get_Scale();		//大きさ情報

	void Set_Position(D3DXVECTOR3 Position);
	void Set_Rotation(D3DXVECTOR3 Rotation);
	void Set_Scale(D3DXVECTOR3 Scale);

public:	//相対情報

	D3DXVECTOR3 Get_localPosition();
	D3DXVECTOR3 Get_localRotation();
	D3DXVECTOR3 Get_localScale();

	void Set_localPosition(D3DXVECTOR3 position);
	void Set_localRotation(D3DXVECTOR3 rotation);
	void Set_localScale(D3DXVECTOR3 scale);

public:	//親子関係
	void Set_Parent(Transform* pParent);	//親を設定
	Transform* Get_Parent();
	void Release_Parent();					//親と離れる

public://	回転関数
	void RotationVec3(const D3DXVECTOR3 value);
	void RotationAxis(const D3DXVECTOR3 Axis, const float value);

public:
	//変換の有効・無効
	void ConvertEnable(bool enable);

	//親を持つか
	bool Have_a_Parent();

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
