//
//	ArmorObject.h
//		Author:HIROMASA IEKDA	DATE:2018/10/13
//===============================================
#pragma once
#ifndef ARMOROBJECT_H
#define ARMOROBJECT_H

#include<d3dx9.h>
#include<vector>
#include"common.h"

using namespace std;

//Class
#include"CGameObject.h"
#include"CCollisionShape.h"

//===============================================
//	アーマー飛ばすやつ
//===============================================
enum ARMOR_DISCHARGING_TYPE
{
	FALL = 0,
	RADIALLY,
	// enum max
	ARMOR_DIS_TYPE_MAX
};

//===============================================
//	ArmarObject クラス
//===============================================
class ArmorObject :public GameObject
{
private: // 一般
	D3DXVECTOR3 Speed;
public:
	bool bBreak;		//バラバラフラグ　True(バラバラになる)
	
public:
	ARMOR_DISCHARGING_TYPE Discharging_Type;	//飛ぶタイプ
	

public: // バラバラ
	void Break();
	void Break( D3DXVECTOR3 Speed, unsigned int DelayFrameForDrop );

public: // 一般関数
	void SetSpeed( D3DXVECTOR3 Vector );
	void Set_DischargingType(ARMOR_DISCHARGING_TYPE Type);

public: // コンストラクタ | デストラクタ
	ArmorObject(Transform* pTransform) :ArmorObject(pTransform, &Texture(),FALL) {};
	ArmorObject(Transform* pTransform, Texture* pTexture) :ArmorObject(pTransform, pTexture, FALL) {};
	ArmorObject(Transform* pTransform, ARMOR_DISCHARGING_TYPE Type) :ArmorObject(pTransform,&Texture(),Type) {};
	ArmorObject(Transform* pTransform, Texture* pTexture,ARMOR_DISCHARGING_TYPE Type);

public:
	void Update();		//更新処理

public: // バラバラ イベント用
	int DelayFrameForDrop;
	
};


#endif // !ARMOROBJECT_H

