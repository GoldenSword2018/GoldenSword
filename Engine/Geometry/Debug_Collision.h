﻿//
//	Debug_Circle.h
//		USER:YU NISHIMAKI		DATE:2018/10/18
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//		Name: Yuto Hashimoto	DATE:2018/10/18
// シングルトンっぽい感じに記述を変更.　直方体に関しては未実装.
//
//-----------------------------------------------
#pragma once
#ifndef DEBUG_PRIMITIVE_H
#define DEBUG_PRIMITIVE_H

#include<d3dx9.h>
#include"CCollisionShape.h"

typedef struct DebugVertex_tag
{
	D3DXVECTOR3 position;
	D3DCOLOR color;
}DebugVertex;

class DebugCollisionModule
{

private:
	DebugCollisionModule() {}
	~DebugCollisionModule();
public: // instance 
	static DebugCollisionModule* pInstance;
public: // 関数
	static void Init( void );
	static void Finalize( void );
	/*
	static void BatchRun( void ); // ここの実装わかりません
	*/
/*
 * スフィア用
 */

private:
	static LPDIRECT3DVERTEXBUFFER9 pSphereVertexBuffer;		// 頂点バッファ
	static LPDIRECT3DINDEXBUFFER9 pSphereIndexBuffer;		// インデックスバッファ
public: // バッチ処理 将来的にprivateメンバにする
	static void Sphere_BatchBegin( void );
	static void Sphere_BatchRun( void );
private:
	static int SphereCount;
	static DebugVertex* pSphereVertex;
	static WORD* pSphereVertexIndex;
public: // 座標登録
	static void BatchDrawSphere( const ShapeSphere* Sphere );

// キューブ用 _-----------------------------------------------------------------------------------------------NOT YET!>
private:
	static LPDIRECT3DVERTEXBUFFER9 pCuboidVertexBuffer;		// 頂点バッファ
	static LPDIRECT3DINDEXBUFFER9 pCuboidIndexBuffer;		// インデックスバッファ
public: // バッチ処理
	static void Cuboid_BatchBegin( void );
	static void Cuboid_BatchRun( void );
private:
	static int CuboidCount;
	static DebugVertex* pCuboidVertex;
	static WORD*  pCuboidVertexIndex;
public: // 座標登録
	static void BatchDrawCuboid( const ShapeOBB* pCuboid );

};

#endif // !DEBUG_PRIMITIVE_H