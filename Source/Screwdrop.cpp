//
//	Screwdrop.cpp
//		Author:ハン	DATE:2018/10/23
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------
#include "Screwdrop.h"

//===============================================
//	マクロ定義
//===============================================
#define BULLET_MAX (256)				//被ってるだろが！！
#define SCREW_DROP_SPEED (0.03f)		//落下速度
#define SCREW_ROTATION_SPEED (0.01f)	//回転時の移動速度
#define ROTATION_FRAME_MAX (1000)		//回転フレーム数

//===============================================
//	構造体
//===============================================

//===============================================
//	グローバル変数
//===============================================
Screwdrop g_Screwdrop[BULLET_MAX];		//大丈夫かこの配列！

//================================================
//	関数		
//================================================
//-------------------------------------
//	初期化
//-------------------------------------
void Screwdrop_Init()
{
	for (int i = 0; i<BULLET_MAX; i++)
	{
		g_Screwdrop[i].IsEnable = false;
		g_Screwdrop[i].BulletPosition = D3DXVECTOR3(0.5f, 0.5f,0.5f);
		g_Screwdrop[i].ScrewPosition = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		g_Screwdrop[i].bullet_type = Bullet::NORMAL;
		g_Screwdrop[i].face = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		g_Screwdrop[i].rotation_count = 0;
		memcpy(&g_Screwdrop[i].BulletMesh, GetMeshData(BulletIndex), sizeof(MeshData));
		memcpy(&g_Screwdrop[i].ScrewMesh, GetMeshData(ScrewIndex), sizeof(MeshData));
	}
}

//-------------------------------------
//	更新
//-------------------------------------
void Screwdrop_Update()
{
	for (int i = 0; i< BULLET_MAX; i++)
	{
		//有効ならば
		if (g_Screwdrop[i].IsEnable)
		{
			//ROTATION_FRAME_MAX以下ならば
			if (g_Screwdrop[i].rotation_count <= ROTATION_FRAME_MAX)
			{
				//回転しながら外す
				g_Screwdrop[i].BulletPosition -= g_Screwdrop[i].face * SCREW_ROTATION_SPEED;
				g_Screwdrop[i].ScrewPosition -= g_Screwdrop[i].face * SCREW_ROTATION_SPEED;
				g_Screwdrop[i].rotation_count+=10;
			}
			else
			{
				//地面に接地するまで落ちる
				if (g_Screwdrop[i].BulletPosition.y >= 0.0f/*地面*/)
				{
					g_Screwdrop[i].BulletPosition.y -= SCREW_DROP_SPEED;
					g_Screwdrop[i].ScrewPosition.y -= SCREW_DROP_SPEED;
				}
				else
				{
					//無効化
					Screwdrop_DisEnable(i);
				}
			}
		}
	}
}

//-------------------------------------
//	描画
//-------------------------------------
void Screwdrop_Render()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//有効なら
		if (g_Screwdrop[i].IsEnable)
		{
			D3DXMATRIX mtxWorld;
			D3DXMATRIX mtxRotation;
			D3DXMATRIX mtxTranslation;
			D3DXMATRIX mtxScaling;

			//平行移動
			D3DXMatrixTranslation(&mtxTranslation, g_Screwdrop[i].BulletPosition.x, g_Screwdrop[i].BulletPosition.y, g_Screwdrop[i].BulletPosition.z);

			//Faceを軸に回転
			D3DXMatrixRotationAxis(&mtxRotation, &g_Screwdrop[i].face,D3DXToRadian(3*g_Screwdrop[i].rotation_count));
			//D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(g_Screwdrop[i].rotation_count));
			
			//スケールを変更
			D3DXMatrixScaling(&mtxScaling, 0.3f, 0.3f, 0.3f);	//マジックナンバ

			//ワールド行列
			mtxWorld = mtxRotation * mtxScaling * mtxTranslation;
			System_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);	//この登録意味ある？

			//バレットの描画関数
			XModel_Render(&g_Screwdrop[i].BulletMesh, mtxWorld);


			D3DXMATRIX mtxTranlationScrew;		// ネジを原点に移動するための平行移動行列
			D3DXMATRIX mtxRotationScrew;		// ネジを正対させるための回転行列
			
			//平行移動
			D3DXMatrixTranslation(&mtxTranlationScrew, 0.0f, -0.5f, 0.0f);	//マジックナンバ

			//スケールを変更
			D3DXMatrixScaling(&mtxScaling, 0.5f, 0.5f, 0.5f);

			//Y軸を中心に半周
			D3DXMatrixRotationY(&mtxRotationScrew, D3DX_PI);
			
			//スクリューの位置に移行
			D3DXMatrixTranslation(&mtxTranslation, g_Screwdrop[i].ScrewPosition.x, g_Screwdrop[i].ScrewPosition.y, g_Screwdrop[i].ScrewPosition.z);
		
			//ワールド行列変換
			mtxWorld = mtxTranlationScrew * mtxRotationScrew * mtxScaling * mtxRotation * mtxTranslation;
			
			System_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);	//この登録意味ある？

			//ネジの描画関数
			XModel_Render(&g_Screwdrop[i].ScrewMesh, mtxWorld);

		}
	}
}

//-------------------------------------
//	生成
//-------------------------------------
void  Screwdrop_Create(D3DXVECTOR3 pos_bullet, D3DXVECTOR3 pos_screw, Bullet::TYPE type, D3DXVECTOR3 face)
{
	for (int i = 0; i< BULLET_MAX; i++)
	{
		if (!g_Screwdrop[i].IsEnable)
		{
			g_Screwdrop[i].ScrewPosition = pos_screw;
			g_Screwdrop[i].BulletPosition = pos_bullet;
			g_Screwdrop[i].bullet_type = type;
			g_Screwdrop[i].face = face;
			g_Screwdrop[i].rotation_count = 0;
			g_Screwdrop[i].IsEnable = true;
			return;
		}
	}
}

//-------------------------------------
//	削除
//-------------------------------------
void Screwdrop_DisEnable(int index)
{
	g_Screwdrop[index].IsEnable = false;
}
