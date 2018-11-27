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
//	GameObject�@�N���X
//===============================================
class GameObject
{
private:
	static std::vector<GameObject*> pIndex;
public:
	static void g_Update();	//�S�̍X�V
	static void g_Render();	//�S�̕`��

public: 
	GameObject* pParent;	//�e

public:
	Transform transform;	//�ʒu
	Texture texture;		//�e�N�X�`��
	Render3D render;		//�`��

public:
	GameObject():GameObject(&Transform(), &Texture()) {};
	GameObject(Transform* pTransform):GameObject(pTransform, &Texture()) {};
	GameObject(Transform* pTransform,Texture* pTexture);

public:
	void Set_Parent(GameObject* pParent);	//�e��ݒ�

public:
	virtual void Update();
	virtual void Render();
};

#endif // !GAMEOBJECT_H


