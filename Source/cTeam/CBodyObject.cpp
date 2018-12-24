//
//	CBodyObject.cpp
//
//===============================================
#include<d3dx9.h>
#include"CBodyObject.h"

//===============================================
//	BodyObject	
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
BodyObject::BodyObject():GameObject()
{

}

BodyObject::BodyObject(Transform* pTransform):GameObject(pTransform)
{

}

BodyObject::BodyObject(Transform* pTransform, NMesh::AMesh* pModel) : GameObject(pTransform,pModel)
{

}










