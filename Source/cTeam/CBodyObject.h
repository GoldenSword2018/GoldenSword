//
//	CBodyObject.h
//		Author:HIROMASA IKEDA	DATE:2018/10/13
//===============================================
#pragma once
#ifndef CBODYOBJECT_H
#define CBODYOBJECT_H

#include"CGameObject.h"

//===============================================
//	BodyObject	ƒNƒ‰ƒX
//===============================================
class BodyObject:public GameObject
{
private:

public:
	BodyObject() :BodyObject(&Transform(), &Texture()) {};
	BodyObject(Transform* pTransform) :BodyObject(pTransform, &Texture()) {};
	BodyObject(Transform* pTransform, Texture* pTexture);

};

#endif // !CBODYOBJECT_H

