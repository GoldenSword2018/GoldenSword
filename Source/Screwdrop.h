//
//	Screwdrop.h
//		Author:ハン	DATE:2018/10/23
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef SCREW_DROP_H
#define SCREW_DROP_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include"XModel.h"
#include"Bullet.h"
#include <d3dx9.h>
#include<math.h>
#include "common.h"
#include "System.h"
#include "XModel.h"

#include"Cube.h"

//================================================
//	マクロ定義	define
//================================================


//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================

//-------------------------------------
//	Screwdrop
//-------------------------------------
typedef struct
{
	bool IsEnable;							//有効・無効
	D3DXVECTOR3 BulletPosition;				//弾のポジション
	D3DXVECTOR3 ScrewPosition;				//ネジのポジション
	Bullet::TYPE bullet_type;				//弾のタイプ
//	SCREW_TYPE	screw_type;					//ネジのタイプ
	MeshData BulletMesh;					//弾のメッシュデータ
	MeshData ScrewMesh;						//ネジのメッシュデータ
	D3DXVECTOR3 face;						//向き
	int rotation_count;						//回転のフレーム数と角度
}Screwdrop;
//================================================
//	グローバル変数　global
//================================================


//================================================
//	関数		function
//================================================
void Screwdrop_Render(void);
void Screwdrop_Update(void);
void Screwdrop_Init(void);
void Screwdrop_Create(D3DXVECTOR3 pos_bullet, D3DXVECTOR3 pos_screw, Bullet::TYPE type, D3DXVECTOR3 face);
void Screwdrop_DisEnable(int index);

#endif