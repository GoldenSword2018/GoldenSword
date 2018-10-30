//
//	Lighting.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/04
//===============================================
#include"Lighting.h"
#include"System.h"

//===============================================
//	グローバル変数
//===============================================
#define COLORVALUE_RGBA(r,g,b,a) D3DCOLORVALUE{r/255,g/255,b/255,a/255}

static D3DLIGHT9 g_DirectLight;
static D3DXVECTOR3 g_DirectLight_Direction;

//===============================================
//	初期化
//===============================================
void Lighting_Initialize()
{
	//------------------------------------
	//	ライティング
	//------------------------------------
	System_GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);	//ライティングをON

	ZeroMemory(&g_DirectLight, sizeof(g_DirectLight));
	g_DirectLight.Type = D3DLIGHT_DIRECTIONAL;

	g_DirectLight_Direction = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&g_DirectLight_Direction, &g_DirectLight_Direction);

	g_DirectLight.Diffuse = COLORVALUE_RGBA(255,255,255,255);
	g_DirectLight.Direction = g_DirectLight_Direction;

	System_GetDevice()->SetLight(0, &g_DirectLight);
	System_GetDevice()->LightEnable(0, TRUE);
	System_GetDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);	//法線ベクトルを単位ベクトル化：拡大・縮小の変化
	System_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);

	//アンビエント
	System_GetDevice()->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(64, 64, 64, 255));
	System_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	/*
		D3DMCS_COLOR1 頂点カラーをマテリアルの色にします。
		D3DMCS_MATERIAL マテリアルをマテリアルの色にします。

		提案1
		 ライトらかSetRenderStateの設定を消す。
		 キューブなどの描画にD3DMCS_COLOR1
		 モデルの描画にD3DMCS_MATERIAL

		提案2
		 どちらかをデフォルトを設定して
		 違うやつをやった後に、デフォルトに戻す
	
		提案3
		　全てをマテリアルにする
	*/
}

//===============================================
//	ライト設定
//===============================================
void Lighting_SetLight()
{
	System_GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);	//ライティングをON
}

