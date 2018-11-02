//
//	Bullet.h
//		Author:ハン DATE:
//===============================================
//	変更者 Changed by
//		Author:HIROMASA IKEDA	DATE:2018/10/17
//
//-----------------------------------------------
#ifndef BULLET_H
#define BULLET_H

#include"common.h"
#include <d3dx9.h>
#include "XModel.h"

//Class
#include"CGameObject.h"
#include"CCollisionableObject.h"

#define BULLET_MAX (256)

//===============================================
//	構造体
//===============================================

//===============================================
//	クラス
//===============================================

//-------------------------------------
//	Bullet
//-------------------------------------
class Bullet:public GameObject
{
public:
	enum TYPE
	{
		NORMAL,
		TORNADO
	};

private:
	bool IsEnable;							//有効・無効
	//D3DXVECTOR3 MainPosition;				//
	TYPE type;						//タイプ
	D3DXVECTOR3 face;						//弾の向き
public:
	MeshData BulletMesh;
	ShapeSphere ColSphape;

	Bullet();
	Bullet(Transform* pTransform, Texture* pTexture);

	virtual void Update();					//更新
	bool GetEnable();						//有効・無効の取得
	void TypeSet(TYPE type);			//タイプの設定
	void SetBullet(D3DXVECTOR3 position, D3DXVECTOR3 face, TYPE type);	//弾をセットする
	void DisEnable();						//無効化
	const D3DXVECTOR3* GetFace();
	void SetPos(D3DXVECTOR3 Pos);
	void SetFace(D3DXVECTOR3 face);
	void CorrectFace(D3DXVECTOR3 face);
};


//===============================================
//	関数
//===============================================
void Bullet_Initialize();
void Bullet_Render();
void Bullet_Update();
void Bullet_Create(D3DXVECTOR3 pos,D3DXVECTOR3 face, Bullet::TYPE type);
void Bullet_Destroy(int index);
bool Bullet_IsEnable(int index);
ShapeSphere Bullet_ColShape(int index);
Bullet* Bullet_GetBullet(int index);

#endif // !BULLET_H
