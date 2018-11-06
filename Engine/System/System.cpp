//
//	System.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/13
//===============================================
//
//	マクロ条件で設定してあるもの
//
//	・入力関係			input.h
//	・テクスチャ関係	Texture.h
//	・描画関係			Sprite.h
//	・タイマー			system_time.h
//	・サウンド			sound.h
//
//	デバッグ
//	・デバッグCircle	Debug_Circle.h
//	・デバッグfont		debug_font.h
//
//-----------------------------------------------
//
//	left Shift + Dキーでデバッグ表示を有効にする場合
//	#define	DEBUG_KEY_ENABLE 
//	を定義
//
//-----------------------------------------------
#include<Windows.h>
#include<d3dx9.h>

#include"System.h"
#include"input.h"
#include"Sprite.h"
#include"Texture.h"
#include"system_timer.h"
#include"sound.h"

#ifdef _DEBUG
//#include"Debug_Circle.h"
#include"Debug_font.h"
#endif // !DEBUG

//===============================================
//	関数
//===============================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void System_Initialize();
void System_Finalize();
void Device_Update();
void Debug_Render();

//===============================================
//	グローバル変数
//===============================================
static HWND					g_hWnd = {};						//ハンドルの設定
static HINSTANCE			g_hInstance = {};
static LPDIRECT3D9			g_pd3d9 = NULL;					//ポインタ
static LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;					//デバイス
static MSG					g_Msg = {};						//メッセージ

#ifdef DEBUG_KEY_ENABLE
static bool					g_bDebug_Render = false;			//デバッグ表示している
#endif // DEBUG_KEY_ENABLE

D3DVIEWPORT9 g_port[] = { { 0, 0, WINDOWSCREEN_WIDTH / 2,WINDOWSCREEN_HEIGHT / 2,0.0f,1.0f },
{ WINDOWSCREEN_WIDTH / 2, 0, WINDOWSCREEN_WIDTH / 2,WINDOWSCREEN_HEIGHT / 2,0.0f,1.0f },
{ 0,WINDOWSCREEN_HEIGHT / 2, WINDOWSCREEN_WIDTH / 2,WINDOWSCREEN_HEIGHT / 2,0.0f,1.0f },
{ WINDOWSCREEN_WIDTH / 2,WINDOWSCREEN_HEIGHT / 2, WINDOWSCREEN_WIDTH / 2,WINDOWSCREEN_HEIGHT / 2,0.0f,1.0f } };

//===============================================
//	ウィンドウ処理
//===============================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASS	MyWindow_01 = {};
	MyWindow_01.lpfnWndProc = WndProc;
	MyWindow_01.lpszClassName = CLASS_NAME;
	MyWindow_01.hInstance = hInstance;
	MyWindow_01.hCursor = LoadCursor(NULL, IDC_ARROW);
	MyWindow_01.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	//システムへの登録
	RegisterClass(&MyWindow_01);

	//ウィンドウサイズ
	RECT Window_Rect = { 0,0,WINDOWSCREEN_WIDTH,WINDOWSCREEN_HEIGHT };

	AdjustWindowRect(&Window_Rect, WINDOW_STYLE, FALSE);

	int WinWidth = Window_Rect.right - Window_Rect.left;
	int WinHeight = Window_Rect.bottom - Window_Rect.top;

	//max(a,b);	a,bを比較して、大きい方を返す。
	int WinPosX = max((GetSystemMetrics(SM_CXSCREEN) - WinWidth) / 2, 0);
	int WinPosY = max((GetSystemMetrics(SM_CYSCREEN) - WinHeight) / 2, 0);

	g_hWnd = CreateWindow(CLASS_NAME, WINDOW_CAPTION, WINDOW_STYLE, WinPosX, WinPosY, WinWidth, WinHeight, NULL, NULL, hInstance, NULL);

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	g_hInstance = hInstance;

	g_Msg = {};				//Message

	System_Initialize();	//初期化

	//------------------------------------
	//	メインループ
	//------------------------------------
	Main_Initialize();

	do
	{
		//メッセージが届いた処理
		if (PeekMessage(&g_Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&g_Msg);
			DispatchMessage(&g_Msg);
		}
		else
		{
	//--------------------------
	//	前更新
	//--------------------------
			Device_Update();
			Main_UpdateBegin();

	//--------------------------
	//	描画
	//--------------------------
			g_pD3DDevice->BeginScene();

			for (int i = 0, count = sizeof(g_port) / sizeof(g_port[0]); i < count; i++)
			{
				//描画領域を変更（ビューポート行列）
				System_GetDevice()->SetViewport(&g_port[i]);
				g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BG_COLOR, 1.0f, 0);
				Main_Render();
			}

	//--------------------------
	//	デバッグ　描画
	//--------------------------
#if defined(INPUT_H) && defined(DEBUG_KEY_ENABLE)

			//デバッグキー
			if (Keyboard_IsTrigger(DIK_D) && Keyboard_IsTrigger(DIK_LSHIFT))
			{
				g_bDebug_Render = !g_bDebug_Render;
				if (g_bDebug_Render)
				{

#endif // INPUT_H && INPUTTING_DEBUG

					Debug_Render();	//デバッグ描画

#if defined(INPUT_H) && defined(DEBUG_KEY_ENABLE)

				}
			}
#endif // INPUT_H && INPUTTING_DEBUG


			g_pD3DDevice->EndScene();
			g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	//--------------------------
	//	後更新
	//--------------------------

			Main_UpdateEnd();

		}
	} while (g_Msg.message != WM_QUIT);

	Main_Finalize();		//ゲームの終了処理

	System_Finalize();		//終了処理

	return (int)g_Msg.wParam;
}

//===============================================
//	プロシージャー処理
//===============================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i = 0;
	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してもよろしいですか？", "確認", MB_OKCANCEL || MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}

		return 0;

	case WM_DESTROY:
		//WM_QUIT　というメッセージを送る
		PostQuitMessage(0);
		return 0;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//===============================================
//	初期化
//===============================================
void System_Initialize()
{
	//--------------------------------------------------------
	//	デバイスの設定
	//--------------------------------------------------------
	g_pd3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pd3d9 == NULL) 
	{
		return;
	}

	D3DPRESENT_PARAMETERS	d3dpp = {};							//デバイスの動作を設定する構造体
	d3dpp.BackBufferWidth = WINDOWSCREEN_WIDTH;
	d3dpp.BackBufferHeight = WINDOWSCREEN_HEIGHT;
	d3dpp.BackBufferCount = 1;									//バックバッファーの枚数
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					//使えるカラーの設定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//表と裏の画面切り替えを行う処理の仕方設定
	d3dpp.Windowed = TRUE;										//ウィンドウ:TRUE	フルスクリーン:FALSE 
	d3dpp.EnableAutoDepthStencil = TRUE;						//ステンシルバッファの有無	FALSEにすると表画面と裏画面が混合する
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//ステンシルバッファのデータ量
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//垂直同期を待つタイミング

	HRESULT hr = g_pd3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice);

	if (FAILED(hr)) {
		MessageBox(g_hWnd, "デバイスの取得に失敗しました。", "エラー", MB_OK);
		DestroyWindow(g_hWnd);
		return;
	}

	//------------------------------------
	//	描画設定
	//------------------------------------
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//半透明処理をON
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//背景DSETのブレンド設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						//深度を適用

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//テクスチャポリゴン透過処理

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);


	//------------------------------------
	//	入力処理　	初期化
	//------------------------------------
#if defined INPUT_H
	Input_Initalize(g_hWnd,g_hInstance);
#endif // INPUT_H

	//------------------------------------
	//	タイマー	初期化
	//------------------------------------
#if defined SYSTEM_TIMER_H_
	SystemTimer_Initialize();
#endif // SYSTEM_TIMER_H_

	//------------------------------------
	//	サウンド　	初期化
	//------------------------------------
#if defined _SOUND_H_
	InitSound(g_hWnd);
#endif // _SOUND_H_

	//------------------------------------
	//	テクスチャ　初期化
	//------------------------------------
#if defined(TEXTURE_H)
	Texture_Initialize();
#endif // TEXTURE_H

	//------------------------------------
	//	スプライト　初期化
	//------------------------------------
#if defined(SPRITE_H)
	Sprite_SetDevice(g_pD3DDevice);		//デバイスを渡す
#endif // SPRITE_H
	
#if defined(DEBUG_CIRCLE_H)
	//------------------------------------
	//	デバッグCircle	初期化
	//------------------------------------
	DebugPrimitive_Initialize(g_pD3DDevice);
#endif // DEBUG_CIRCLE_H

	//------------------------------------
	//	デバッグFont	初期化
	//------------------------------------
#if defined(DEBUG_FONT_H)
	DebugFont_Initialize();
#endif
}

//===============================================
//	デバイス　更新処理
//===============================================
void Device_Update()
{
#if defined INPUT_H
	Input_Update(g_hWnd);
#endif // INPUT_H

}

//===============================================
//	デバッグ描画
//===============================================
void Debug_Render()
{
#if defined(DEBUG_CIRCLE_H)
	DebugPrimitive_BatchRun(g_pD3DDevice);
#endif // DEBUG_CIRCLE_H
}

//===============================================
//	終了処理
//===============================================
void System_Finalize()
{
#if defined(DEBUG_FONT_H)
	//------------------------------------
	//	デバッグFont	終了処理
	//------------------------------------
	DebugFont_Finalize();
#endif

#if defined(DEBUG_CIRCLE_H)
	//------------------------------------
	//	デバッグCircle	終了処理
	//------------------------------------
	DebugPrimitive_Finalize();
#endif // _DEBUG

#if defined(TEXTURE_H)
	//------------------------------------
	//	テクスチャ		終了処理
	//------------------------------------
	Texture_Finalize();
#endif // TEXTURE_H
	
#if defined(_SOUND_H_)
	//------------------------------------
	//	サウンド	　	終了処理
	//------------------------------------
	UninitSound();
#endif // SOUND_H

#if defined(INPUT_H)
	//------------------------------------
	//	入力　			終了処理
	//------------------------------------
	Input_Finalize();
#endif // INPUT_H

	//------------------------------------
	//	デバイスの破棄
	//------------------------------------
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pd3d9 != NULL)
	{
		g_pd3d9->Release();
		g_pd3d9 = NULL;
	}
}

//===============================================
//	HWNDの取得
//===============================================
HWND *System_GethWnd()
{
	return &g_hWnd;
}

//===============================================
//	インスタンスの取得
//===============================================
HINSTANCE *System_GethInstance() 
{
	return &g_hInstance;
}

//===============================================
//	デバイスの取得
//===============================================
LPDIRECT3DDEVICE9 System_GetDevice(void)
{
	return g_pD3DDevice;
}
