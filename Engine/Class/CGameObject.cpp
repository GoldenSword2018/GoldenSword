//
//	CGameObject.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/29
//===============================================
#include<d3dx9.h>
#include<vector>
#include"Cube.h"

//Class
#include"CGameObject.h"

//===============================================
//	グローバル変数
//===============================================
std::vector<GameObject*> GameObject::pIndex;

//===============================================
//	GameObject クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
GameObject::GameObject(Transform* pTransform)
{
	this->transform		= *pTransform;
	this->pIndex.push_back(this);
	this->pParent = NULL;
}

//モデル形式のコンストラクタ
GameObject::GameObject(Transform* pTransform,NMesh::AMesh* pModel):GameObject(pTransform)
{
	this->render.Set_Mesh(pModel);
}

//-------------------------------------
//	親を設定
//-------------------------------------
void GameObject::Set_Parent(GameObject* pParent)
{
	this->pParent = pParent;
	this->transform.Set_Parent(&this->pParent->transform);
}

//------------------------------------
//	親を放す
//------------------------------------
void GameObject::Relesase_Parent()
{
	this->pParent = NULL;
	return;
}

//------------------------------------
//	更新処理
//------------------------------------
void GameObject::Update()
{

}

//------------------------------------
//	描画処理
//------------------------------------
void GameObject::Render()
{
	this->render.Begin(&this->transform.Get_MtxWorld());
}

//===============================================
//	グローバル
//===============================================

//-----------------------------------
//	全体更新
//-----------------------------------
void GameObject::g_Update()
{
	for(int i = 0; i < pIndex.size(); i++)
	{
		pIndex.at(i)->Update();
	}

}

//----------------------------------
//	全体描画
//----------------------------------
void GameObject::g_Render()
{
	for(int i = 0; i< pIndex.size(); i++)
	{
		pIndex.at(i)->Render();
	}
}
