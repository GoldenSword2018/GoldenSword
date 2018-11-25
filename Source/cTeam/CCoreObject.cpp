//
//	CCoreObject.cpp	
//		Author:HIROMASA IKEDA	DATE:2018/10/13
//===============================================
#include<d3dx9.h>
#include<vector>

//Class
#include"Cube.h"
#include"CCoreObject.h"
#include"CCollisionShape.h"
#include"Bullet.h"
#include"Screwdrop.h"
#include"XModel.h"

#include "Debug_Collision.h"

// 当たり判定登録 ------------------------------------------------------------------------------------------------------------------- TMP!>
#include "CCollisionChecker.h"
//===============================================
//	CoreObject	クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
// コンストラクタでのShape系クラスの初期化はCoreObject自身のtransformのアドレスを与えること. 引数のpTransformはコンストラクタ終了後,破棄される.
CoreObject::CoreObject(Transform* pTransform, Texture* pTexture, CORE_DISCHARGE_JUDGE_TYPE Type, D3DXVECTOR3 face)
: 
	GameObject(pTransform, pTexture),
	ColShape(&transform.WorldPosition, 0.5f),
	CorrectSphere(&transform.WorldPosition, 1.0f)
{
	this->face = face;
	TmpCollisionChecker::GetInstance()->RegisterCollision_CoreObject( this );
	this->Type = Type;
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
CoreObject::~CoreObject()
{
	TmpCollisionChecker::GetInstance()->DeregisterCollision_CoreObject( this );
}

//-------------------------------------
//	胴体オブジェクト登録
//-------------------------------------
void CoreObject::SetBody(BodyObject* pBodyObject)
{
	this->pBodyObject = pBodyObject;
	this->Set_Parent(this->pBodyObject);
}

//-------------------------------------
//	アーマーオブジェクトを登録
//-------------------------------------
void CoreObject::SetArmor(ArmorObject* pArmorObject)
{
	this->pArmor_Index.push_back(pArmorObject);
	pArmorObject->transform.Set_Parent(&this->transform);
}

//--------------------------------------
//	アーマーオブジェクトと胴体を同時に登録
//--------------------------------------
void CoreObject::Set(ArmorObject* pArmorObject,BodyObject* pBodyObject)
{
	this->SetBody(pBodyObject);
	this->SetArmor(pArmorObject);
}

//-------------------------------------
//	弾に当たった
//-------------------------------------
void CoreObject::Hit()
{
	this->bHit = true;

	if(this->pArmor_Index.size() > 0)
	{
		DischargeArmor( 120.0f, 1.0f, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) ); // ここ引数をメンバにして持つなりする！ -------------------------------------------------------------------------- CAUTION!>
	}
}

//-------------------------------------
//	更新処理
//-------------------------------------
void CoreObject::Update()
{
	//弾との当たり判定
	for (int i = 0; i<BULLET_MAX; i++)
	{
		//弾が有効
		if (Bullet_IsEnable(i))
		{
			//引き寄せる	
			if ( CollisionCheck::SphereVsSphere(CorrectSphere, Bullet_ColShape(i))&& this->pArmor_Index.size() > 0)
			{
				const D3DXVECTOR3* bullet_face = Bullet_GetBullet(i)->GetFace();
				D3DXVECTOR3 vec = *(CorrectSphere.pParentPos) - *(Bullet_ColShape(i).pParentPos);		// ネジと弾の中心間ベクトル
				float Angle = acosf(D3DXVec3Dot(bullet_face, &vec));				// 弾の進行方向とvecの成す角

				if (Angle <= D3DX_PI / 4 && Angle > 0.0f)
				{
					Bullet_GetBullet(i)->CorrectFace(vec);
				}
			}
			/*
			//ネジ本体の当たり判定
			if ( CollisionCheck::SphereVsSphere(ColShape, Bullet_ColShape(i)) && this->pArmor_Index.size() > 0)
			{
				Hit();
				Bullet_GetBullet(i)->SetFace(face);
				Bullet_GetBullet(i)->SetPos(this->transform.Position - ColShape.Radius * face * 1.0f);
				Screwdrop_Create(*(Bullet_GetBullet(i)->ColSphape.pParentPos),*( CorrectSphere.pParentPos ), Bullet::NORMAL, *Bullet_GetBullet(i)->GetFace());
				Bullet_GetBullet(i)->DisEnable();
			}
			*/
		}
	}


}

//-------------------------------------
//	描画
//-------------------------------------
void CoreObject::Render()
{
	//アーマーオブジェクトを持っている。
	if (this->pArmor_Index.size() > 0)
	{

		//Xモデルの行列変換
		D3DXMATRIXA16 mtxBaseTransform;		// 基準変換行列
		D3DXMATRIXA16 mtxBaseTranslation;
		D3DXMATRIXA16 mtxBaseRotation;	
		D3DXMATRIXA16 mtxBaseScaling;	

		D3DXMATRIXA16 mtxWorld;
		D3DXMATRIXA16 mtxTranslation;
		D3DXMATRIXA16 mtxRotation;
		/*
		D3DXMATRIXA16 mtxRotation2;
		D3DXMATRIXA16 mtxScaling;

		this->transform.Set_WorldTransform();
		D3DXMatrixTranslation(&mtxTranslation, this->transform.WorldPosition.x, this->transform.WorldPosition.y, this->transform.WorldPosition.z);
		D3DXMatrixTranslation(&mtxTranslation2, 0.0f, -0.5f, 0.0f);
		//D3DXMatrixRotationY(&mtxRotation, D3DX_PI);
		D3DXMatrixRotationYawPitchRoll(&mtxRotation2,this->transform.WorldRotation.y,this->transform.WorldRotation.x,this->transform.WorldRotation.z);
		D3DXMatrixScaling(&mtxScaling, 0.4f, 0.4f, 0.4f);
		

		//合成
		mtxWorld = (mtxTranslation2*mtxScaling)*mtxTranslation;
		*/


		D3DXMATRIXA16 mtxRotationY;
		D3DXMATRIXA16 mtxRotationAxis;
		D3DXVECTOR3 vecFaceGroud;
		D3DXVECTOR3 vecRight;

		D3DXMatrixTranslation(&mtxBaseTranslation, 0.0f, -0.5f, 0.0f);	// 原点に平行移動
		D3DXMatrixRotationY(&mtxBaseRotation, D3DX_PI);					// Y軸周りに半回転して正面に向ける
		D3DXMatrixScaling(&mtxBaseScaling, 0.4f, 0.4f, 0.4f);			// サイズ調整

		mtxBaseTransform = mtxBaseTranslation * mtxBaseRotation * mtxBaseScaling;	// 基準変換行列の設定

		if (this->face == D3DXVECTOR3(0.0f, 1.0f, 0.0f))
		{
			D3DXMatrixRotationX(&mtxRotation, -D3DX_PI / 2);
		}
		else if (this->face == D3DXVECTOR3(0.0f, -1.0f, 0.0f))
		{
			D3DXMatrixRotationX(&mtxRotation, D3DX_PI / 2);
		}
		else
		{
			vecFaceGroud = this->face;
			vecFaceGroud.y = 0.0f;
			D3DXVec3Normalize(&vecFaceGroud, &vecFaceGroud);
			vecRight.x = vecFaceGroud.z;
			vecRight.y = 0.0f;
			vecRight.z = -vecFaceGroud.x;
			D3DXMatrixRotationY(&mtxRotationY, atan2f(vecFaceGroud.x, vecFaceGroud.z));
			D3DXMatrixRotationAxis(&mtxRotationAxis, &vecRight, acosf(D3DXVec3Dot(&this->face, &vecFaceGroud)));
			mtxRotation = mtxRotationY * mtxRotationAxis;
		}


		this->transform.Set_WorldTransform();
		D3DXMATRIX MtxRotation;
		D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->transform.WorldRotation.y, this->transform.WorldRotation.x, this->transform.WorldRotation.z);
		D3DXVec3TransformNormal(&this->transform.WorldPosition, &this->transform.WorldPosition,&MtxRotation);

		D3DXMatrixTranslation(&mtxTranslation, this->transform.WorldPosition.x, this->transform.WorldPosition.y, this->transform.WorldPosition.z);		// 平行移動

		//合成
		mtxWorld = mtxBaseTransform * mtxRotation * mtxTranslation;

		//ネジの描画
		XModel_Render(GetMeshData(ScrewIndex), mtxWorld);

		//当たり判定の描画
		ColShape.DebugDraw();
		CorrectSphere.DebugDraw();
	}
}

//-------------------------------------
//	ネジの向きの取得
//-------------------------------------
D3DXVECTOR3 CoreObject::GetFace()
{
	return this->face;
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
void CoreObject::DischargeArmor( float Margin, float Weight, D3DXVECTOR3 AddUnitVec, float SpeedRatio )
{
	for( int i = 0; i < pArmor_Index.size(); i++ )
	{
		// アーマー破棄イベントまでの遅延フレームを算出
		float DelayFrame;

		float SquaredDist = D3DXVec3LengthSq( &( pArmor_Index.at( i )->transform.Position - transform.Position ) );

		switch( this->Type )
		{
			case CORE_JUDGE_TYPE_0:	//距離
				DelayFrame = SquaredDist * Weight + Margin;
				break;
			case CORE_JUDGE_TYPE_1:	// 子Armor全て一度に
				DelayFrame = Weight + Margin;
				break;
			default:
				DelayFrame = Weight + Margin; // 仮置きでType1をデフォルトに
				break;
		}

		// 速度を指定
		D3DXVECTOR3* pInitSpeed;
		const ARMOR_DISCHARGING_TYPE Type = pArmor_Index.at( i )->Discharging_Type;

		switch( Type )
		{

			case FALL:	//ずれて落ちる
				pInitSpeed = new D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
				*pInitSpeed += AddUnitVec;
				break;
			case RADIALLY: //放射状に広がる
				pInitSpeed = new D3DXVECTOR3( pArmor_Index.at( i )->transform.Position - transform.Position );
				D3DXVec3Normalize( pInitSpeed, pInitSpeed );
				*pInitSpeed = ( *pInitSpeed + AddUnitVec ) * SpeedRatio;

		}

		pArmor_Index.at( i )->Break( *pInitSpeed, DelayFrame );
	}
	this->pArmor_Index.clear();
}