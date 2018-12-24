//
//	CArmorObject.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/16
//===============================================
#include<d3dx9.h>
#include<math.h>
#include<vector>

//Class
#include"CArmorObject.h"
#include"Cube.h"

//===============================================
//	定数
//===============================================
 // とりあえず
const D3DXVECTOR3 GRAVITY( 0.0f, -0.02f, 0.0f );	//重力
//===============================================
//	関数
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
ArmorObject::ArmorObject(Transform* pTransform, NMesh::AMesh* pModel,ARMOR_DISCHARGING_TYPE Type) :GameObject(pTransform,pModel)
{
	bBreak = false;
	this->Discharging_Type = Type;
	this->Speed = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->DelayFrameForDrop = -1;
}

//-------------------------------------
//	更新処理
//-------------------------------------
void ArmorObject::Update()
{
	//--------------------------
	//	バラバラ
	//--------------------------
	if(bBreak && DelayFrameForDrop <= 0 )
	{
		*this->transform.Position() += this->Speed;
		this->Speed += GRAVITY;
	}

	// 
	if( bBreak && 0 < DelayFrameForDrop )
	{
		DelayFrameForDrop--;
	}

}


//-------------------------------------
//	速度ベクトルセット
//-------------------------------------
void ArmorObject::SetSpeed( D3DXVECTOR3 InitVec )
{
	Speed = InitVec;
}


//-------------------------------------
//	速度ベクトルセット
//-------------------------------------
void ArmorObject::Break()
{
	bBreak = true;
}

//-------------------------------------
//	速度ベクトルセット
//-------------------------------------
void ArmorObject::Break( D3DXVECTOR3 InitVec, unsigned int InitDelay )
{
	Break();
	SetSpeed( InitVec );
	DelayFrameForDrop = InitDelay;

}

//-------------------------------------
//	タイプをセット
//-------------------------------------
void ArmorObject::Set_DischargingType(ARMOR_DISCHARGING_TYPE Type)
{
	this->Discharging_Type = Type;
}


