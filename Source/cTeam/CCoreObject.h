//
//	CCoreObject.h
//		Author:HIROMASA IKEDA	DATE:2018/10/13
//===============================================
#pragma once
#ifndef COREOBJECT_H
#define COREOBJECT_H

#include<d3dx9.h>
#include<vector>
#include"common.h"

using namespace std;


#include"CGameObject.h"
#include"CBodyObject.h"
#include"CArmorObject.h"

//===============================================
//	列挙
//===============================================



//===============================================
//	CoreObject クラス
//===============================================
class CoreObject:public GameObject
{
public: 
	//判定タイプ
	enum CORE_DISCHARGE_JUDGE_TYPE
	{
		CORE_JUDGE_TYPE_0 = 0,
		CORE_JUDGE_TYPE_1,
		// enum max
		CORE_JUDGE__MAX
	};

private:
	vector<ArmorObject*> pArmor_Index;	//アーマーオブジェクト
	BodyObject*	pBodyObject;			//ボディオブジェクト
	
	CORE_DISCHARGE_JUDGE_TYPE Type;		//飛び方判定タイプ
	D3DXVECTOR3 face;					//飛ぶ向き

public:
	bool bHit;							//当たった
	ShapeSphere ColShape;				//ネジ自身
	ShapeSphere CorrectSphere;			//補正球

public:
	CoreObject(Transform* pTransform, Texture* pTexture) :CoreObject(pTransform, pTexture, CORE_JUDGE_TYPE_0) {};
	CoreObject(Transform* pTransform, CORE_DISCHARGE_JUDGE_TYPE Type) :CoreObject(pTransform, &Texture(), Type) {};
	CoreObject(Transform* pTransform, Texture* pTexture, CORE_DISCHARGE_JUDGE_TYPE Type) :CoreObject(pTransform, pTexture, Type, { 0.0f,0.0f,-1.0f }) {};
	CoreObject(Transform* pTransform, Texture* pTexture, CORE_DISCHARGE_JUDGE_TYPE Type, D3DXVECTOR3 face);
	~CoreObject();

public:
	void Hit();

	void SetBody(BodyObject* pBodyObject);
	void Set(ArmorObject* pArmorObject);
	void Set(ArmorObject* pArmorObject, BodyObject* pBodyObject);
	void Set_JudgeType(CORE_DISCHARGE_JUDGE_TYPE Type);
	void Update();
	void Render();
	D3DXVECTOR3 GetFace();

	void DischargeArmor( float MaxDistance, float Weight, float SpeedRatio = 1.0f ); // Dist^2 * Weight = DelayFrame

};

#endif // !CCOREOBJECT_H




