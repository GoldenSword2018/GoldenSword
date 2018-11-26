//
//	Bullet.cpp
//		Author:ハン	DATE:
//===============================================
//	変更者 Change by
//		Author:MinodaTakamasa DATE:2018/10/23
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
#define BULLET_NORMAL_SPEED (0.05f)
#define BULLET_NORMAL_RADIUS (1)		//弾の半径
#define BULLET_COUNT (256)
#define BULLET_MAX (256)
#define CORRECT_WAIT(a) (a/100.f)		//補正の強さ

//===============================================
//	構造体
//===============================================

//===============================================
//	グローバル変数
//===============================================

Bullet g_Bullet[BULLET_MAX];
float fRoll = 0;

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
		memcpy(&g_Bullet[i].BulletMesh, GetMeshData(BulletIndex), sizeof(MeshData));
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
			XModel_Render(&g_Bullet[i].BulletMesh);
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
	ColSphape(&this->transform,0.5f)
{
	IsEnable = false;
}

Bullet::Bullet(Transform* pTransform, Texture* pTexture):GameObject(pTransform,pTexture),ColSphape(&transform,0.5f)
{
	type = NORMAL;
	Bullet();
}

//-------------------------------------
//	弾のタイプ設定
//-------------------------------------
void Bullet::TypeSet(TYPE tyep)
{
	this->type = type;
}

static float value = 0;

//-------------------------------------
//	更新処理
//-------------------------------------
void Bullet::Update()
{
	// ColSphape.Pos = this->BulletMesh.vecPosition;

	switch (this->type)
	{
	case NORMAL:
		//スプライトの中心座標を更新する
		this->BulletMesh.vecPosition += this->face * BULLET_NORMAL_SPEED;
		break;

	//回転させる弾
	case TORNADO:
		this->BulletMesh.vecPosition += this->face * BULLET_NORMAL_SPEED;
		//this->transform.Position = MainPosition;

		this->BulletMesh.vecPosition.x += 0.01f * sinf(D3DXToRadian(value));
		this->BulletMesh.vecPosition.y +=0.01f * cosf(D3DXToRadian(value));

		break;
	default:
		break;
	}

	D3DXMATRIXA16 matPosition;
	//D3DXMatrixIdentity(&this->BulletMesh.matWorld);
	D3DXMatrixTranslation(&matPosition, this->BulletMesh.vecPosition.x, this->BulletMesh.vecPosition.y, this->BulletMesh.vecPosition.z);

	D3DXMATRIX matRotationZ;
	D3DXMatrixRotationZ(&matRotationZ, fRoll);

	D3DXMATRIX matRotationFace;
	D3DXVECTOR3 face = this->face;
	D3DXVECTOR3 X, Y, Z; //X:右 Z:前 Y:上
	D3DXVECTOR3 Faceup = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Z = -face;
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, &Faceup), &Z);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Y, D3DXVec3Cross(&Y, &Z, &X));

	//回転行列を作る
	matRotationFace._11 = X.x; matRotationFace._12 = X.y; matRotationFace._13 = X.z; matRotationFace._14 = 0;
	matRotationFace._21 = Y.x; matRotationFace._22 = Y.y; matRotationFace._23 = Y.z; matRotationFace._24 = 0;
	matRotationFace._31 = Z.x; matRotationFace._32 = Z.y; matRotationFace._33 = Z.z; matRotationFace._34 = 0;
	matRotationFace._41 = 0.0f; matRotationFace._42 = 0.0f; matRotationFace._43 = 0.0f; matRotationFace._44 = 1.0f;

	D3DXMATRIX matSize;
	D3DXMatrixScaling(&matSize, 0.2f, 0.2f, 0.2f);

	this->BulletMesh.matWorld =  matSize * matRotationZ * matRotationFace * matPosition;

	fRoll += 0.001f;
	value += 0.01f;
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
	memcpy(&this->BulletMesh.vecPosition, position, sizeof(D3DXVECTOR3));
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
	this->BulletMesh.vecPosition = Pos;
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