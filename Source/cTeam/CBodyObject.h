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
	BodyObject();
	BodyObject(Transform* pTransform);
	BodyObject(Transform* pTransform, NMesh::AMesh* pModel);
};

#endif // !CBODYOBJECT_H

