//
//	GameObject.h
//		Author:HIROMASA IKEDA	DATE:2018/09/30
//===============================================
#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<d3dx9.h>
#include<vector>

//Class
#include"CTransform.h"
#include"CTexture.h"
#include"CRender.h"
#include"Component.h"

//===============================================
//	GameObject　クラス
//===============================================
class GameObject
{
private:
	static std::vector<GameObject*> pIndex;
	GameObject* pParent;	//親

public:
	static void g_Update();	//全体更新
	static void g_Render();	//全体描画

	Transform transform;	//位置
	Texture texture;		//テクスチャ
	Render3D render;		//描画

	GameObject():GameObject(&Transform(), &Texture()) {};
	GameObject(Transform* pTransform):GameObject(pTransform, &Texture()) {};
	GameObject(Transform* pTransform,Texture* pTexture);

	void Set_Parent(GameObject* pParent);	//親を設定
	virtual void Update();
	virtual void Render();
};

#endif // !GAMEOBJECT_H


