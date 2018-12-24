//
//	Bullet.cpp
//		Author:ハン	DATE:
//===============================================
//	変更者 Change by
//		Author:MinodaTakamasa DATE:2018/10/23
//
//-----------------------------------------------
//
//	設計思想と噛み合って無いので、改造するべき事項。
//
//-----------------------------------------------

#include <d3dx9.h>
#include<math.h>
#include "Bullet.h"
#include "common.h"
#include "System.h"

// 暫定当たり判定機能 ------------------------------------------------------------------------------------------------------------------- TMP!>
#include "CCollisionChecker.h"

//===============================================
//	マクロ定義
//===============================================
#define BULLET_NORMAL_SPEED (0.1f)
#define BULLET_NORMAL_RADIUS ( 1 )		//弾の半径
#define BULLET_COUNT (256)
#define BULLET_MAX (256)
#define CORRECT_WAIT(a) (a/100.f)		//補正の強さ

//===============================================
//	構造体
//===============================================

//===============================================
//	グローバル変数
//===============================================

Bullet g_Bullet[BULLET_MAX];	//弾配列
float fRoll = 0;				//弾の回転
static float value = 0;			//誰？

//===============================================
//	関数
//===============================================

//-------------------------------------
//	初期化
//-------------------------------------
void Bullet_Initialize()
{
	for(int i = 0; i<BULLET_MAX; i++)
	{
		memcpy(&g_Bullet[i].BulletMesh, NModel::Get_Data(NModel::BulletIndex), sizeof(NModel::Data));
	}
}

//-------------------------------------
//	更新
//-------------------------------------
void Bullet_Update()
{
	for(int i = 0; i< BULLET_MAX; i++)
	{
		if(g_Bullet[i].GetEnable())
		{
			g_Bullet[i].Update();
		}
	}
}

/*
	////弾の無効(画面外の場合
	//for (int i = 0; i < BULLET_COUNT; i++)
	//{
	//	if (Bullet[i].pos.x >= SCREEN_WIDTH || Bullet[i].pos.x <= -SCREEN_WIDTH || 
	//		Bullet[i].pos.y <= -SCREEN_HEIGHT || Bullet[i].pos.y >= SCREEN_HEIGHT ||
	//		Bullet[i].pos.z >=||Bullet[i].pos.z <=)				//判定条件がわからない
	//	{
	//		Bullet_Destroy(i);
	//	}
	//}
*/

//-------------------------------------
//	描画
//-------------------------------------
void Bullet_Render()
{
	for(int i = 0; i < BULLET_MAX; i++)
	{
		if(g_Bullet[i].GetEnable())
		{
			NModel::Render(&g_Bullet[i].BulletMesh);
		}
	}
	
}

//-------------------------------------
//	生成
//-------------------------------------
void Bullet_Create(D3DXVECTOR3 position, D3DXVECTOR3 face, Bullet::TYPE type)
{
	for(int i= 0; i< BULLET_MAX; i++)
	{
		if(!g_Bullet[i].GetEnable())
		{
			g_Bullet[i].SetBullet(position,face,type);
			return;
		}
	}
}

//-------------------------------------
//	削除
//-------------------------------------
void Bullet_Destroy(int index)
{
	g_Bullet[index].DisEnable();
}

//-------------------------------------
//	有効か
//-------------------------------------
bool Bullet_IsEnable(int index)
{
	return g_Bullet[index].GetEnable();
}

ShapeSphere Bullet_ColShape(int index)
{
	return g_Bullet[index].ColSphape;
}

//-------------------------------------
//	Bulletクラス取得
//-------------------------------------
Bullet* Bullet_GetBullet(int index)
{
	return &g_Bullet[index];
}


//===============================================
//	Bullet クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Bullet::Bullet()
	:
	ColSphape(&this->transform,1.0f)
{
	IsEnable = false;
}

Bullet::Bullet(Transform* pTransform):GameObject(pTransform),ColSphape(&this->transform,0.5f)
{
	type = NORMAL;
	Bullet();
}

Bullet::Bullet(Transform* pTransform,NMesh::AMesh* pModel)
:
	GameObject(pTransform,pModel),ColSphape(&this->transform,0.5f)
{
	
}

//-------------------------------------
//	弾のタイプ設定
//-------------------------------------
void Bullet::TypeSet(TYPE tyep)
{
	this->type = type;
}



//-------------------------------------
//	更新処理
//-------------------------------------
void Bullet::Update()
{
	switch (this->type)
	{
	case NORMAL:
		//スプライトの中心座標を更新する
		*this->transform.Position() += this->face * BULLET_NORMAL_SPEED;
		break;
	}

	//===========================================
	//	弾の向きを変更する行列変換
	//===========================================

	D3DXMATRIXA16 matPosition;

	//平行移動
	//D3DXMatrixIdentity(&this->BulletMesh.matWorld);
	D3DXMatrixTranslation(&matPosition, this->vecPosition.x, this->vecPosition.y, this->vecPosition.z);

	//Z軸回転
	D3DXMATRIX matRotationZ;
	D3DXMatrixRotationZ(&matRotationZ, fRoll);

	//回転
	D3DXMATRIX matRotationFace;
	D3DXVECTOR3 face = this->face;
	D3DXVECTOR3 X, Y, Z;				//X:右 Z:前 Y:上
	D3DXVECTOR3 Faceup = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	Z = -face;							//逆転？
	//FaceUpを正規化したYベクトル と face向きを逆転させたZ との外積
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, &Faceup), &Z);

	//Xベクトル？を正規化
	D3DXVec3Normalize(&X, &X);

	//ZベクトルとXベクトルの外積Yベクトルを正規化
	D3DXVec3Normalize(&Y, D3DXVec3Cross(&Y, &Z, &X));

	//回転行列を作る
	matRotationFace._11 = X.x; matRotationFace._12 = X.y; matRotationFace._13 = X.z; matRotationFace._14 = 0;
	matRotationFace._21 = Y.x; matRotationFace._22 = Y.y; matRotationFace._23 = Y.z; matRotationFace._24 = 0;
	matRotationFace._31 = Z.x; matRotationFace._32 = Z.y; matRotationFace._33 = Z.z; matRotationFace._34 = 0;
	matRotationFace._41 = 0.0f; matRotationFace._42 = 0.0f; matRotationFace._43 = 0.0f; matRotationFace._44 = 1.0f;

	//スケール行列
	D3DXMATRIX matSize;
	D3DXMatrixScaling(&matSize, 0.2f, 0.2f, 0.2f);	//マジックナンバーだ！！

	//ワールド行列
	this->transform.Set_MtxWorld(matSize * matRotationZ * matRotationFace * matPosition);

	fRoll += 0.001f;
	value += 0.01f;

	*this->transform.Position() = this->vecPosition;
}

//-------------------------------------
//	Enable取得
//-------------------------------------
bool Bullet::GetEnable()
{
	return this->IsEnable;
}

//--------------------------------------
//	弾を設定
//--------------------------------------
void Bullet::SetBullet(D3DXVECTOR3 position, D3DXVECTOR3 face, TYPE type)
{
	D3DXVec3Normalize(&face,&face);		//単位化
	//this->MainPosition = position;
	memcpy(&this->vecPosition, position, sizeof(D3DXVECTOR3));
	this->face = face;
	this->type = type;
	this->IsEnable = true;
	TmpCollisionChecker::GetInstance()->RegisterCollision_Bullet( this );
}

//-------------------------------------
//	弾を無効化
//-------------------------------------
void Bullet::DisEnable()
{
	this->IsEnable = false;
	TmpCollisionChecker::GetInstance()->DeregisterCollision_Bullet( this );
}

//-------------------------------------
//	弾の進行方向を取得
//-------------------------------------
const D3DXVECTOR3* Bullet::GetFace()
{
	return &face;
}

//-------------------------------------
//	弾のポジションをセット
//-------------------------------------
void Bullet::SetPos(D3DXVECTOR3 Pos)
{
	this->vecPosition = Pos;
	// this->ColSphape.Pos = Pos;
}

//-------------------------------------
//	弾の進行方向をセット
//-------------------------------------
void Bullet::SetFace(D3DXVECTOR3 face)
{
	this->face = face;
}

//-------------------------------------
//	弾の進行方向に補正をかける
//-------------------------------------
void Bullet::CorrectFace(D3DXVECTOR3 vec)
{
	D3DXVECTOR3 newFace = face + vec * CORRECT_WAIT(30);
	D3DXVec3Normalize(&newFace, &newFace);
	SetFace(newFace);

}

void Bullet::Render()
{
	return;
}