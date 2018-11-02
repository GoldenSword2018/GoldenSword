//
//	CCoreObject.cpp	
//		Author:HIROMASA IKEDA	DATE:2018/10/13
//===============================================
#include<d3dx9.h>
#include<vector>

//Class
#include"Cube.h"
#include"CCoreObject.h"
#include"CCollisionableObject.h"
#include"Bullet.h"
#include"Screwdrop.h"
#include"XModel.h"

#include "Debug_Sphere.h"

//===============================================
//	CoreObject	クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
// コンストラクタでのShape系クラスの初期化はCoreObject自身のtransformのアドレスを与えること. 引数のpTransformはコンストラクタ終了後,破棄される.
CoreObject::CoreObject(Transform* pTransform, Texture* pTexture, CORE_DISCHARGE_JUDGE_TYPE Type) :GameObject(pTransform, pTexture), ColShape(&transform.Position, 0.5f), CorrectSphere( &transform.Position, 1.0f)
{
	this->Type = Type;
	this->face = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
}

CoreObject::CoreObject(Transform* pTransform, Texture* pTexture, CORE_DISCHARGE_JUDGE_TYPE Type, D3DXVECTOR3 face) : GameObject(pTransform, pTexture), ColShape( &transform.Position, 0.5f), CorrectSphere( &transform.Position, 1.0f)
{
	this->face = face;
}

void CoreObject::Set(ArmorObject* pArmorObject)
{
	this->pArmor_Index.push_back(pArmorObject);
}

void CoreObject::Set(ArmorObject* pArmorObject,BodyObject* pBodyObject)
{
	this->pArmor_Index.push_back(pArmorObject);
	this->pBodyObject = pBodyObject;
	this->Set_Parent(this->pBodyObject);
}


//-------------------------------------
//	デストラクタ
//-------------------------------------
CoreObject::~CoreObject()
{

}


//-------------------------------------
//	弾に当たった
//-------------------------------------
void CoreObject::Hit()
{
	this->bHit = true;
	if(this->pArmor_Index.size() > 0)
	{
		DischargeArmor( 11.0f, 20.0f);
	}
}

//-------------------------------------
//	更新処理
//-------------------------------------
void CoreObject::Update()
{
	for (int i = 0; i<BULLET_MAX; i++)
	{
		if (Bullet_IsEnable(i))
		{
			//引き寄せる	
			if (Collision::SphereVsSphere(CorrectSphere, Bullet_ColShape(i))&& this->pArmor_Index.size() > 0)
			{
				const D3DXVECTOR3* bullet_face = Bullet_GetBullet(i)->GetFace();
				D3DXVECTOR3 vec = *(CorrectSphere.pParentPos) - *(Bullet_ColShape(i).pParentPos);		// ネジと弾の中心間ベクトル
				float Angle = acosf(D3DXVec3Dot(bullet_face, &vec));				// 弾の進行方向とvecの成す角

				if (Angle <= D3DX_PI / 4 && Angle > 0.0f)
				{
					Bullet_GetBullet(i)->CorrectFace(vec);
				}
			}
		}
	}

	for (int i = 0; i<BULLET_MAX; i++)
	{
		
		if (Bullet_IsEnable(i))
		{
			if (Collision::SphereVsSphere(ColShape, Bullet_ColShape(i)) && this->pArmor_Index.size() > 0)
			{
				Hit();
				Bullet_GetBullet(i)->SetFace(face);
				Bullet_GetBullet(i)->SetPos(this->transform.Position - ColShape.Radius * face * 1.0f);
				Screwdrop_Create(*(Bullet_GetBullet(i)->ColSphape.pParentPos),*( CorrectSphere.pParentPos ), BULLET_NORMAL, *Bullet_GetBullet(i)->GetFace());
				Bullet_GetBullet(i)->DisEnable();
			}
		}
		
	}

}

//-------------------------------------
//	描画
//-------------------------------------
void CoreObject::Render()
{
	if (this->pArmor_Index.size() > 0)
	{
		DebugBufferManager::Sphere_BatchBegin();

		D3DXMATRIXA16 mtxWorld;
		D3DXMATRIXA16 mtxTranslation;
		D3DXMATRIXA16 mtxTranslation2;
		D3DXMATRIXA16 mtxRotation;
		D3DXMATRIXA16 mtxScaling;
		D3DXMatrixTranslation(&mtxTranslation, this->transform.Position.x, this->transform.Position.y, this->transform.Position.z);
		D3DXMatrixTranslation(&mtxTranslation2, 0.0f, -0.5f, 0.0f);
		D3DXMatrixRotationY(&mtxRotation, D3DX_PI);
		D3DXMatrixScaling(&mtxScaling, 0.4f, 0.4f, 0.4f);
		mtxWorld = mtxTranslation2*mtxRotation*mtxScaling*mtxTranslation;
		XModel_Render(GetMeshData(ScrewIndex), mtxWorld);

		DebugBufferManager::BatchDrawSphere(&this->ColShape);
		DebugBufferManager::BatchDrawSphere(&this->CorrectSphere);

		DebugBufferManager::Sphere_BatchRun();
	}
}

//-------------------------------------
//	ネジの向きの取得
//-------------------------------------
D3DXVECTOR3 CoreObject::GetFace()
{
	return face;
}

//-------------------------------------
//	判定設定
//-------------------------------------
void CoreObject::Set_JudgeType(CORE_DISCHARGE_JUDGE_TYPE Type)
{
	this->Type = Type;
}

//-------------------------------------
//	アーマー飛ばす
//-------------------------------------
void CoreObject::DischargeArmor( float MaxDist, float Weight, float SpeedRatio )
{
	for(int i = 0; i < pArmor_Index.size(); i++ )
	{
		const D3DXVECTOR3* pInitSpeed;
		// そのアーマーとの距離を計算
		const float SquaredDist = D3DXVec3LengthSq( &( pArmor_Index.at( i )->transform.Position - transform.Position ) );
		// アーマー破棄イベントまでの遅延フレームを算出
		// 得たフレーム数が最大値より低ければアーマー破棄を実行

		float DelayFrame;

		if( SquaredDist < MaxDist * MaxDist )
		{
			switch (this->Type)
			{
			case CORE_JUDGE_TYPE_0:	//距離
				DelayFrame = SquaredDist * Weight;
				break;
			case CORE_JUDGE_TYPE_1:	//範囲
				DelayFrame = MaxDist * Weight;
				break;
			default:
				//NULL
				break;
			}

			
			const ARMOR_DISCHARGING_TYPE Type = pArmor_Index.at(i)->Discharging_Type;

			switch( Type )
			{

				case FALL:	//ずれて落ちる
					pInitSpeed = new D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
					break;
				case RADIALLY: //放射状に広がる
					D3DXVECTOR3 Vec = pArmor_Index.at( i )->transform.Position - transform.Position;
					D3DXVec3Normalize( &Vec, &Vec );
					Vec *= SpeedRatio;
					pInitSpeed = new D3DXVECTOR3( Vec );
					break;
			}

			pArmor_Index.at(i)->Break(*pInitSpeed, (unsigned int)DelayFrame);			
		}

	}

	this->pArmor_Index.clear();
}