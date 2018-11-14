//
//	DebuCircle.cpp
//		Author:YU NISHIMAKI		DATE:2018/10/18
//===============================================
//	�ύX�� Changed By
//		Name: Yuto Hashimoto	DATE:2018/11/13
//  �p�ӂ���o�b�t�@�̈�̐������.
//  Cuboid��Color�����o��p���ĐF�t������悤�ɕύX.
//
//-----------------------------------------------
#include<d3dx9.h>
#include"System.h"
#include"Debug_Collision.h"


//===============================================
//	�}�N����`
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
//	�\����
//===============================================
#define FVF_DEBUG_VERTEX	(D3DFVF_XYZ | D3DFVF_DIFFUSE)



//===============================================
//	�O���[�o���ϐ�
//===============================================

DebugCollisionModule* DebugCollisionModule::pInstance = NULL;


/* 
 * �f�X�g���N�^
 */
DebugCollisionModule::~DebugCollisionModule()
{
#if defined(_DEBUG) || defined(DEBUG)
	
	Finalize();
	delete pInstance;

#endif // _DEBUG || DEBUG
}

/*
 * �֐�
 */
void DebugCollisionModule::Init( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	pInstance = new DebugCollisionModule;
	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	// ���p�̃o�b�t�@�m��
	// �~��3���������̂ŗp�ӂ���o�b�t�@�̈��3�{
	pDevice->CreateVertexBuffer( sizeof( DebugVertex ) * CIRCLE_VERTEX_COUNT * CIRCLE_DRAW_MAX * 3, D3DUSAGE_WRITEONLY, FVF_DEBUG_VERTEX, D3DPOOL_MANAGED, &pInstance->pSphereVertexBuffer, NULL );
	pDevice->CreateIndexBuffer( sizeof( WORD ) * ( CIRCLE_VERTEX_COUNT * 2 ) *  CIRCLE_DRAW_MAX * 3, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pInstance->pSphereIndexBuffer, NULL );
	pInstance->SphereCount = 0;

	// Cuboid�p�̃o�b�t�@�m��
	pDevice->CreateVertexBuffer( sizeof( DebugVertex ) * CUBOID_VERTEX_COUNT * CUBOID_DRAW_MAX, D3DUSAGE_WRITEONLY, FVF_DEBUG_VERTEX, D3DPOOL_MANAGED, &pInstance->pCuboidVertexBuffer, NULL );
	pDevice->CreateIndexBuffer( sizeof( WORD ) * CUBOID_EDGE_COUNT * CUBOID_POINT_COUNT_PER_EDGE * CUBOID_DRAW_MAX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pInstance->pCuboidIndexBuffer, NULL );
	pInstance->CuboidCount = 0;

#endif // _DEBUG || DEBUG
}

DebugCollisionModule* DebugCollisionModule::GetInstance( void )
{
#if defined(_DEBUG) || defined(DEBUG)
	if( DebugCollisionModule::pInstance )
	{
		DebugCollisionModule::Init();
	}

	return pInstance;
#endif // _DEBUG || DEBUG
}
void DebugCollisionModule::Finalize( void )
{
#if defined(_DEBUG) || defined(DEBUG)
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
#endif // _DEBUG || DEBUG
}

//-------------------------------------
//	Sphere
//-------------------------------------


/*
 * �`��J�n : �I��
 */
void DebugCollisionModule::Sphere_BatchBegin( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	pInstance->SphereCount = 0;

	pInstance->pSphereVertexBuffer->Lock( 0, 0, (void**) &pInstance->pSphereVertex, 0 );
	pInstance->pSphereIndexBuffer->Lock( 0, 0, (void**) &pInstance->pSphereVertexIndex, 0 );

#endif // _DEBUG || DEBUG
}

void DebugCollisionModule::Sphere_BatchRun( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	D3DXMATRIX mtxTransform;
	D3DXMatrixIdentity( &mtxTransform );
	pDevice->SetTransform( D3DTS_WORLD, &mtxTransform );

	pInstance->pSphereVertexBuffer->Unlock();
	pInstance->pSphereIndexBuffer->Unlock();

	pDevice->SetTexture( 0, NULL );
	pDevice->SetFVF( FVF_DEBUG_VERTEX );
	pDevice->SetStreamSource( 0, pInstance->pSphereVertexBuffer, 0, sizeof( DebugVertex ) );
	pDevice->SetIndices( pInstance->pSphereIndexBuffer );
	pDevice->DrawIndexedPrimitive( D3DPT_LINELIST, 0, 0, CIRCLE_VERTEX_COUNT * pInstance->SphereCount, 0, pInstance->SphereCount * CIRCLE_VERTEX_COUNT * 3 );
#endif // _DEBUG || DEBUG
}


/*
 * Buffer�ւ̍��W�o�^�֐�
 */
void DebugCollisionModule::BatchDrawSphere( const ShapeSphere *Sphere )
{
#if defined(_DEBUG) || defined(DEBUG)

	int n = pInstance->SphereCount * CIRCLE_VERTEX_COUNT;

	const float s = D3DX_PI * 2 / CIRCLE_VERTEX_COUNT;

	for( int i = 0; i < CIRCLE_VERTEX_COUNT; i++ )
	{
		pInstance->pSphereVertex[ n + i ].position.x = (float) cos( i * s ) * Sphere->Radius + Sphere->pParentPos->x;
		pInstance->pSphereVertex[ n + i ].position.y = (float) sin( i * s ) * Sphere->Radius + Sphere->pParentPos->y;
		pInstance->pSphereVertex[ n + i ].position.z = Sphere->pParentPos->z;
		pInstance->pSphereVertex[ n + i ].color = D3DCOLOR_RGBA( 0, 255, 0, 255 );

		pInstance->pSphereVertexIndex[ n * 2 + i * 2 ] = (WORD) ( n + i );
		pInstance->pSphereVertexIndex[ n * 2 + i * 2 + 1 ] = (WORD) ( n + ( i + 1 ) % CIRCLE_VERTEX_COUNT );
	}

	n += CIRCLE_VERTEX_COUNT;
	for( int i = 0; i < CIRCLE_VERTEX_COUNT; i++ )
	{
		pInstance->pSphereVertex[ n + i ].position.x = Sphere->pParentPos->x;
		pInstance->pSphereVertex[ n + i ].position.y = (float) cos( i * s ) * Sphere->Radius + Sphere->pParentPos->y;
		pInstance->pSphereVertex[ n + i ].position.z = (float) sin( i * s ) * Sphere->Radius + Sphere->pParentPos->z;
		pInstance->pSphereVertex[ n + i ].color = D3DCOLOR_RGBA( 0, 255, 0, 255 );

		pInstance->pSphereVertexIndex[ n * 2 + i * 2 ] = (WORD) ( n + i );
		pInstance->pSphereVertexIndex[ n * 2 + i * 2 + 1 ] = (WORD) ( n + ( i + 1 ) % CIRCLE_VERTEX_COUNT );
	}
	n += CIRCLE_VERTEX_COUNT;
	for( int i = 0; i < CIRCLE_VERTEX_COUNT; i++ )
	{
		pInstance->pSphereVertex[ n + i ].position.x = (float) sin( i * s ) * Sphere->Radius + Sphere->pParentPos->x;
		pInstance->pSphereVertex[ n + i ].position.y = Sphere->pParentPos->y;
		pInstance->pSphereVertex[ n + i ].position.z = (float) cos( i * s ) * Sphere->Radius + Sphere->pParentPos->z;
		pInstance->pSphereVertex[ n + i ].color = D3DCOLOR_RGBA( 0, 255, 0, 255 );

		pInstance->pSphereVertexIndex[ n * 2 + i * 2 ] = (WORD) ( n + i );
		pInstance->pSphereVertexIndex[ n * 2 + i * 2 + 1 ] = (WORD) ( n + ( i + 1 ) % CIRCLE_VERTEX_COUNT );
	}

	pInstance->SphereCount++;

#endif // _DEBUG || DEBUG
}

//-------------------------------------
//	Cuboid
//-------------------------------------

void DebugCollisionModule::Cuboid_BatchBegin( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	pInstance->CuboidCount = 0;

	pInstance->pCuboidVertexBuffer->Lock( 0, 0, (void**) &pInstance->pCuboidVertex, 0 );
	pInstance->pCuboidIndexBuffer->Lock( 0, 0, (void**) &pInstance->pCuboidVertexIndex, 0 );

#endif // _DEBUG || DEBUG
}
void DebugCollisionModule::Cuboid_BatchRun( void )

{
#if defined(_DEBUG) || defined(DEBUG)

	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	D3DXMATRIX mtxTransform;
	D3DXMatrixIdentity( &mtxTransform );
	pDevice->SetTransform( D3DTS_WORLD, &mtxTransform );

	pInstance->pCuboidVertexBuffer->Unlock();
	pInstance->pCuboidIndexBuffer->Unlock();

	pDevice->SetTexture( 0, NULL );
	pDevice->SetFVF( FVF_DEBUG_VERTEX );
	pDevice->SetStreamSource( 0, pInstance->pCuboidVertexBuffer, 0, sizeof( DebugVertex ) );
	pDevice->SetIndices( pInstance->pCuboidIndexBuffer );
	pDevice->DrawIndexedPrimitive( D3DPT_LINELIST, 0, 0, CUBOID_VERTEX_COUNT * pInstance->CuboidCount, 0, pInstance->CuboidCount * CUBOID_EDGE_COUNT );


#endif // _DEBUG || DEBUG
}
/*
 * Buffer�ւ̍��W�o�^�֐�
 */
void DebugCollisionModule::BatchDrawCuboid( const ShapeOBB* pCuboid )
{
#if defined(_DEBUG) || defined(DEBUG)
	D3DXVECTOR3 AbsLocalX = pCuboid->NormalDirect[ 1 ] * pCuboid->Length[ 1 ];
	D3DXVECTOR3 AbsLocalY = pCuboid->NormalDirect[ 2 ] * pCuboid->Length[ 2 ];
	D3DXVECTOR3 AbsLocalZ = pCuboid->NormalDirect[ 0 ] * pCuboid->Length[ 0 ];

	DebugVertex CuboidVertex[] =
	{
		{ -AbsLocalX + AbsLocalY - AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },
		{  AbsLocalX + AbsLocalY - AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },
		{ -AbsLocalX - AbsLocalY - AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },
		{  AbsLocalX - AbsLocalY - AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },

		{  AbsLocalX + AbsLocalY + AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },
		{ -AbsLocalX + AbsLocalY + AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },
		{  AbsLocalX - AbsLocalY + AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },
		{ -AbsLocalX - AbsLocalY + AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color }
	};

	int Margin = CUBOID_VERTEX_COUNT * pInstance->CuboidCount;

	pInstance->pCuboidVertex[ Margin + 0 ] = CuboidVertex[ 0 ];
	pInstance->pCuboidVertex[ Margin + 1 ] = CuboidVertex[ 1 ];
	pInstance->pCuboidVertex[ Margin + 2 ] = CuboidVertex[ 2 ];
	pInstance->pCuboidVertex[ Margin + 3 ] = CuboidVertex[ 3 ];
	pInstance->pCuboidVertex[ Margin + 4 ] = CuboidVertex[ 4 ];
	pInstance->pCuboidVertex[ Margin + 5 ] = CuboidVertex[ 5 ];
	pInstance->pCuboidVertex[ Margin + 6 ] = CuboidVertex[ 6 ];
	pInstance->pCuboidVertex[ Margin + 7 ] = CuboidVertex[ 7 ];

	int IndexMargin = CUBOID_EDGE_COUNT * 2 * pInstance->CuboidCount;
	// x�� ���s�̕�
	pInstance->pCuboidVertexIndex[ IndexMargin +  0 ] = (WORD) ( Margin + 1 );
	pInstance->pCuboidVertexIndex[ IndexMargin +  1 ] = (WORD) ( Margin + 0 );

	pInstance->pCuboidVertexIndex[ IndexMargin +  2 ] = (WORD) ( Margin + 4 );
	pInstance->pCuboidVertexIndex[ IndexMargin +  3 ] = (WORD) ( Margin + 5 );

	pInstance->pCuboidVertexIndex[ IndexMargin +  4 ] = (WORD) ( Margin + 6 );
	pInstance->pCuboidVertexIndex[ IndexMargin +  5 ] = (WORD) ( Margin + 7 );

	pInstance->pCuboidVertexIndex[ IndexMargin +  6 ] = (WORD) ( Margin + 3 );
	pInstance->pCuboidVertexIndex[ IndexMargin +  7 ] = (WORD) ( Margin + 2 );

	// y�� ���s
	pInstance->pCuboidVertexIndex[ IndexMargin +  8 ] = (WORD) ( Margin + 0 );
	pInstance->pCuboidVertexIndex[ IndexMargin +  9 ] = (WORD) ( Margin + 2 );

	pInstance->pCuboidVertexIndex[ IndexMargin + 10 ] = (WORD) ( Margin + 1 );
	pInstance->pCuboidVertexIndex[ IndexMargin + 11 ] = (WORD) ( Margin + 3 );
	
	pInstance->pInstance->pCuboidVertexIndex[ IndexMargin + 12 ] = (WORD) ( Margin + 4 );
	pInstance->pInstance->pCuboidVertexIndex[ IndexMargin + 13 ] = (WORD) ( Margin + 6 );
	
	pInstance->pCuboidVertexIndex[ IndexMargin + 14 ] = (WORD) ( Margin + 5 );
	pInstance->pCuboidVertexIndex[ IndexMargin + 15 ] = (WORD) ( Margin + 7 );
	
	// z�����s
	pInstance->pCuboidVertexIndex[ IndexMargin + 16 ] = (WORD) ( Margin + 5 );
	pInstance->pCuboidVertexIndex[ IndexMargin + 17 ] = (WORD) ( Margin + 0 );
	
	pInstance->pCuboidVertexIndex[ IndexMargin + 18 ] = (WORD) ( Margin + 4 );
	pInstance->pCuboidVertexIndex[ IndexMargin + 19 ] = (WORD) ( Margin + 1 );
	
	pInstance->pCuboidVertexIndex[ IndexMargin + 20 ] = (WORD) ( Margin + 6 );
	pInstance->pCuboidVertexIndex[ IndexMargin + 21 ] = (WORD) ( Margin + 3 );
	
	pInstance->pCuboidVertexIndex[ IndexMargin + 22 ] = (WORD) ( Margin + 7 );
	pInstance->pCuboidVertexIndex[ IndexMargin + 23 ] = (WORD) ( Margin + 2 );
	pInstance->CuboidCount++;

#endif // _DEBUG || DEBUG 
}

