//
//	DebuCircle.cpp
//		Author:YU NISHIMAKI		DATE:2018/10/18
//===============================================
#include<d3dx9.h>
#include"System.h"
#include"Debug_Sphere.h"


//===============================================
//	マクロ定義
//===============================================
// Sphere
#define CIRCLE_VERTEX_COUNT		(16)
#define CIRCLE_DRAW_MAX			(2048)

// Cuboid
#define CUBOID_VERTEX_COUNT     ( 8 )
#define CUBOID_EDGE_COUNT       ( 12 )
#define CUBOID_POINT_COUNT_PER_EDGE    ( 2 )
#define CUBOID_DRAW_MAX			( 2048 )
//===============================================
//	構造体
//===============================================
#define FVF_DEBUG_VERTEX	(D3DFVF_XYZ | D3DFVF_DIFFUSE)



//===============================================
//	グローバル変数
//===============================================

DebugCollisionModule* DebugCollisionModule::pInstance = NULL;

// Sphere用バッファ
int DebugCollisionModule::SphereCount = 0;
 LPDIRECT3DVERTEXBUFFER9 DebugCollisionModule::pSphereVertexBuffer;		// 頂点バッファ
 LPDIRECT3DINDEXBUFFER9 DebugCollisionModule::pSphereIndexBuffer;		// インデックスバッファ
// Cuboid用バッファ 
 int DebugCollisionModule::CuboidCount = 0;
 LPDIRECT3DVERTEXBUFFER9 DebugCollisionModule::pCuboidVertexBuffer;
 LPDIRECT3DINDEXBUFFER9 DebugCollisionModule::pCuboidIndexBuffer;
/* 
 * デストラクタ
 */
DebugCollisionModule::~DebugCollisionModule()
{
#if defined(_DEBUG) || defined(DEBUG)
	
	Finalize();
	delete pInstance;

#endif // _DEBUG || DEBUG
}

/*
 * 関数
 */
void DebugCollisionModule::Init( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	pInstance = new DebugCollisionModule;
	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	// 球用のバッファ確保
	// 円を3軸分書くので用意するバッファ領域は3倍
	pDevice->CreateVertexBuffer( sizeof( DebugVertex ) * CIRCLE_VERTEX_COUNT * CIRCLE_DRAW_MAX * 3, D3DUSAGE_WRITEONLY, FVF_DEBUG_VERTEX, D3DPOOL_MANAGED, &pSphereVertexBuffer, NULL );
	pDevice->CreateIndexBuffer( sizeof( WORD ) * ( CIRCLE_VERTEX_COUNT * 2 ) *  CIRCLE_DRAW_MAX * 3, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pSphereIndexBuffer, NULL );
	SphereCount = 0;

	// Cuboid用のバッファ確保
	pDevice->CreateVertexBuffer( sizeof( DebugVertex ) * CUBOID_VERTEX_COUNT * CUBOID_DRAW_MAX, D3DUSAGE_WRITEONLY, FVF_DEBUG_VERTEX, D3DPOOL_MANAGED, &pCuboidVertexBuffer, NULL );
	pDevice->CreateIndexBuffer( sizeof( WORD ) * CUBOID_EDGE_COUNT * 2 * CUBOID_POINT_COUNT_PER_EDGE, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pCuboidIndexBuffer, NULL );

#endif // _DEBUG || DEBUG
}
void DebugCollisionModule::Finalize( void )
{
	if( pSphereIndexBuffer )
	{
		pSphereIndexBuffer->Release();
		pSphereIndexBuffer = NULL;
	}


	if( pSphereVertexBuffer )
	{
		pSphereVertexBuffer->Release();
		pSphereVertexBuffer = NULL;
	}
	if( pCuboidVertexBuffer )
	{
		pCuboidVertexBuffer->Release();
		pCuboidVertexBuffer = NULL;
	}
	if( pCuboidIndexBuffer )
	{
		pCuboidIndexBuffer->Release();
		pCuboidIndexBuffer = NULL;
	}
	MessageBox( NULL, "DELETE", "ok ", MB_OK );
}

//-------------------------------------
//	Sphere
//-------------------------------------

DebugVertex* DebugCollisionModule::pSphereVertex;
WORD* DebugCollisionModule::pSphereVertexIndex;

/*
 * 描画開始 : 終了
 */
void DebugCollisionModule::Sphere_BatchBegin( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	SphereCount = 0;

	pSphereVertexBuffer->Lock( 0, 0, (void**) &pSphereVertex, 0 );
	pSphereIndexBuffer->Lock( 0, 0, (void**) &pSphereVertexIndex, 0 );

#endif // _DEBUG || DEBUG
}

void DebugCollisionModule::Sphere_BatchRun( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	D3DXMATRIX mtxTransform;
	D3DXMatrixIdentity( &mtxTransform );
	pDevice->SetTransform( D3DTS_WORLD, &mtxTransform );

	pSphereVertexBuffer->Unlock();
	pSphereIndexBuffer->Unlock();

	pDevice->SetTexture( 0, NULL );
	pDevice->SetFVF( FVF_DEBUG_VERTEX );
	pDevice->SetStreamSource( 0, pSphereVertexBuffer, 0, sizeof( DebugVertex ) );
	pDevice->SetIndices( pSphereIndexBuffer );
	pDevice->DrawIndexedPrimitive( D3DPT_LINELIST, 0, 0, CIRCLE_VERTEX_COUNT * CIRCLE_DRAW_MAX, 0, SphereCount * CIRCLE_VERTEX_COUNT * 3 );
#endif // _DEBUG || DEBUG
}


/*
 * Bufferへの座標登録関数
 */
void DebugCollisionModule::BatchDrawSphere( const ShapeSphere *Sphere )
{
#if defined(_DEBUG) || defined(DEBUG)

	int n = SphereCount * CIRCLE_VERTEX_COUNT;

	const float s = D3DX_PI * 2 / CIRCLE_VERTEX_COUNT;

	for( int i = 0; i < CIRCLE_VERTEX_COUNT; i++ )
	{
		pSphereVertex[ n + i ].position.x = (float) cos( i * s ) * Sphere->Radius + Sphere->pParentPos->x;
		pSphereVertex[ n + i ].position.y = (float) sin( i * s ) * Sphere->Radius + Sphere->pParentPos->y;
		pSphereVertex[ n + i ].position.z = Sphere->pParentPos->z;
		pSphereVertex[ n + i ].color = D3DCOLOR_RGBA( 0, 255, 0, 255 );

		pSphereVertexIndex[ n * 2 + i * 2 ] = (WORD) ( n + i );
		pSphereVertexIndex[ n * 2 + i * 2 + 1 ] = (WORD) ( n + ( i + 1 ) % CIRCLE_VERTEX_COUNT );
	}

	SphereCount++;
	n += CIRCLE_VERTEX_COUNT;
	for( int i = 0; i < CIRCLE_VERTEX_COUNT; i++ )
	{
		pSphereVertex[ n + i ].position.x = Sphere->pParentPos->x;
		pSphereVertex[ n + i ].position.y = (float) cos( i * s ) * Sphere->Radius + Sphere->pParentPos->y;
		pSphereVertex[ n + i ].position.z = (float) sin( i * s ) * Sphere->Radius + Sphere->pParentPos->z;
		pSphereVertex[ n + i ].color = D3DCOLOR_RGBA( 0, 255, 0, 255 );

		pSphereVertexIndex[ n * 2 + i * 2 ] = (WORD) ( n + i );
		pSphereVertexIndex[ n * 2 + i * 2 + 1 ] = (WORD) ( n + ( i + 1 ) % CIRCLE_VERTEX_COUNT );
	}
	SphereCount++;
	n += CIRCLE_VERTEX_COUNT;
	for( int i = 0; i < CIRCLE_VERTEX_COUNT; i++ )
	{
		pSphereVertex[ n + i ].position.x = (float) sin( i * s ) * Sphere->Radius + Sphere->pParentPos->x;
		pSphereVertex[ n + i ].position.y = Sphere->pParentPos->y;
		pSphereVertex[ n + i ].position.z = (float) cos( i * s ) * Sphere->Radius + Sphere->pParentPos->z;
		pSphereVertex[ n + i ].color = D3DCOLOR_RGBA( 0, 255, 0, 255 );

		pSphereVertexIndex[ n * 2 + i * 2 ] = (WORD) ( n + i );
		pSphereVertexIndex[ n * 2 + i * 2 + 1 ] = (WORD) ( n + ( i + 1 ) % CIRCLE_VERTEX_COUNT );
	}

	SphereCount++;

#endif // _DEBUG || DEBUG
}

//-------------------------------------
//	Cuboid
//-------------------------------------

// 頂点 インデックス
DebugVertex* DebugCollisionModule::pCuboidVertex;
WORD* DebugCollisionModule::pCuboidVertexIndex;

void DebugCollisionModule::Cuboid_BatchBegin( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	CuboidCount = 0;

	pCuboidVertexBuffer->Lock( 0, 0, (void**) &pCuboidVertex, 0 );
	pCuboidIndexBuffer->Lock( 0, 0, (void**) &pCuboidVertexIndex, 0 );

#endif // _DEBUG || DEBUG
}
void DebugCollisionModule::Cuboid_BatchRun( void )

{
#if defined(_DEBUG) || defined(DEBUG)

	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	D3DXMATRIX mtxTransform;
	D3DXMatrixIdentity( &mtxTransform );
	pDevice->SetTransform( D3DTS_WORLD, &mtxTransform );

	pCuboidVertexBuffer->Unlock();
	pCuboidIndexBuffer->Unlock();

	pDevice->SetTexture( 0, NULL );
	pDevice->SetFVF( FVF_DEBUG_VERTEX );
	pDevice->SetStreamSource( 0, pCuboidVertexBuffer, 0, sizeof( DebugVertex ) );
	pDevice->SetIndices( pCuboidIndexBuffer );
	pDevice->DrawIndexedPrimitive( D3DPT_LINELIST, 0, 0, CUBOID_VERTEX_COUNT * CUBOID_DRAW_MAX, 0, CuboidCount * CUBOID_EDGE_COUNT * 2 );


#endif // _DEBUG || DEBUG
}
/*
 * Bufferへの座標登録関数
 */
void DebugCollisionModule::BatchDrawCuboid( const ShapeOBB* pCuboid )
{
#if defined(_DEBUG) || defined(DEBUG)
	D3DXVECTOR3 AbsLocalX = pCuboid->NormalDirect[ 1 ] * pCuboid->Length[ 1 ];
	D3DXVECTOR3 AbsLocalY = pCuboid->NormalDirect[ 2 ] * pCuboid->Length[ 2 ];
	D3DXVECTOR3 AbsLocalZ = pCuboid->NormalDirect[ 0 ] * pCuboid->Length[ 0 ];

	DebugVertex CuboidVertex[] =
	{
		{ -AbsLocalX + AbsLocalY - AbsLocalZ + pCuboid->GetEffectivePos(), D3DCOLOR_RGBA( 255, 255, 255, 255 ) },
		{  AbsLocalX + AbsLocalY - AbsLocalZ + pCuboid->GetEffectivePos(), D3DCOLOR_RGBA( 255, 255, 255, 255 ) },
		{ -AbsLocalX - AbsLocalY - AbsLocalZ + pCuboid->GetEffectivePos(), D3DCOLOR_RGBA( 255, 255, 255, 255 ) },
		{  AbsLocalX - AbsLocalY - AbsLocalZ + pCuboid->GetEffectivePos(), D3DCOLOR_RGBA( 255, 255, 255, 255 ) },

		{  AbsLocalX + AbsLocalY + AbsLocalZ + pCuboid->GetEffectivePos(), D3DCOLOR_RGBA( 255, 255, 255, 255 ) },
		{ -AbsLocalX + AbsLocalY + AbsLocalZ + pCuboid->GetEffectivePos(), D3DCOLOR_RGBA( 255, 255, 255, 255 ) },
		{  AbsLocalX - AbsLocalY + AbsLocalZ + pCuboid->GetEffectivePos(), D3DCOLOR_RGBA( 255, 255, 255, 255 ) },
		{ -AbsLocalX - AbsLocalY + AbsLocalZ + pCuboid->GetEffectivePos(), D3DCOLOR_RGBA( 255, 255, 255, 255 ) },
	};

	int Margin = CUBOID_VERTEX_COUNT * CuboidCount;

	pCuboidVertex[ Margin + 0 ] = CuboidVertex[ 0 ];
	pCuboidVertex[ Margin + 1 ] = CuboidVertex[ 1 ];
	pCuboidVertex[ Margin + 2 ] = CuboidVertex[ 2 ];
	pCuboidVertex[ Margin + 3 ] = CuboidVertex[ 3 ];
	pCuboidVertex[ Margin + 4 ] = CuboidVertex[ 4 ];
	pCuboidVertex[ Margin + 5 ] = CuboidVertex[ 5 ];
	pCuboidVertex[ Margin + 6 ] = CuboidVertex[ 6 ];
	pCuboidVertex[ Margin + 7 ] = CuboidVertex[ 7 ];

	int IndexMargin = CUBOID_EDGE_COUNT * 2 * CuboidCount;
	// x軸 平行の辺
	pCuboidVertexIndex[ IndexMargin +  0 ] = (WORD) ( Margin + 1 );
	pCuboidVertexIndex[ IndexMargin +  1 ] = (WORD) ( Margin + 0 );

	pCuboidVertexIndex[ IndexMargin +  2 ] = (WORD) ( Margin + 4 );
	pCuboidVertexIndex[ IndexMargin +  3 ] = (WORD) ( Margin + 5 );

	pCuboidVertexIndex[ IndexMargin +  4 ] = (WORD) ( Margin + 6 );
	pCuboidVertexIndex[ IndexMargin +  5 ] = (WORD) ( Margin + 7 );

	pCuboidVertexIndex[ IndexMargin +  6 ] = (WORD) ( Margin + 3 );
	pCuboidVertexIndex[ IndexMargin +  7 ] = (WORD) ( Margin + 2 );

	// y軸 平行
	pCuboidVertexIndex[ IndexMargin +  8 ] = (WORD) ( Margin + 0 );
	pCuboidVertexIndex[ IndexMargin +  9 ] = (WORD) ( Margin + 2 );

	pCuboidVertexIndex[ IndexMargin + 10 ] = (WORD) ( Margin + 1 );
	pCuboidVertexIndex[ IndexMargin + 11 ] = (WORD) ( Margin + 3 );
	
	pCuboidVertexIndex[ IndexMargin + 12 ] = (WORD) ( Margin + 4 );
	pCuboidVertexIndex[ IndexMargin + 13 ] = (WORD) ( Margin + 6 );
	
	pCuboidVertexIndex[ IndexMargin + 14 ] = (WORD) ( Margin + 5 );
	pCuboidVertexIndex[ IndexMargin + 15 ] = (WORD) ( Margin + 7 );
	
	// z軸平行
	pCuboidVertexIndex[ IndexMargin + 16 ] = (WORD) ( Margin + 5 );
	pCuboidVertexIndex[ IndexMargin + 17 ] = (WORD) ( Margin + 0 );
	
	pCuboidVertexIndex[ IndexMargin + 18 ] = (WORD) ( Margin + 4 );
	pCuboidVertexIndex[ IndexMargin + 19 ] = (WORD) ( Margin + 1 );
	
	pCuboidVertexIndex[ IndexMargin + 20 ] = (WORD) ( Margin + 6 );
	pCuboidVertexIndex[ IndexMargin + 21 ] = (WORD) ( Margin + 3 );
	
	pCuboidVertexIndex[ IndexMargin + 22 ] = (WORD) ( Margin + 7 );
	pCuboidVertexIndex[ IndexMargin + 23 ] = (WORD) ( Margin + 2 );
	CuboidCount++;

#endif // _DEBUG || DEBUG 
}

