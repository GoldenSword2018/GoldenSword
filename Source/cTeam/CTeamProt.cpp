//
//	CTeamProt.cpp
//		Author:HIROMASA IEKDA	DATE:2018/10/15
//===============================================

#include<d3dx9.h>
#include"common.h"
#include"CTeamProt.h"
#include"input.h"

//Gometry
#include"Cube.h"
#include"Grid.h"

//Class
#include"CArmorObject.h"
#include"CCoreObject.h"
#include"CBodyObject.h"
#include"CCamera.h"
#include "CCollisionChecker.h" // �����蔻��
#include "Debug_Collision.h" // �����蔻��f�o�b�O�`��

//===============================================
//	�O���[�o���ϐ�
//===============================================
static float movez = -5.0f;

//===============================================
//	�֐�
//===============================================

//-------------------------------------
//	������
//-------------------------------------
void CTeamProt_Initialize()
{
}

//-------------------------------------
//	�X�V
//-------------------------------------
void CTeamProt_Update()
{
	GameObject::g_Update();		//�Q�[���I�u�W�F�N�g�̍X�V

	TmpCollisionChecker::GetInstance()->CheckCollision();
}

//-------------------------------------
//	�`��
//-------------------------------------
void CTeamProt_Render()
{
	DebugCollisionModule::GetInstance()->BatchBegin();
	GameObject::g_Render();
	DebugCollisionModule::GetInstance()->BatchRun();

}

//-------------------------------------
//	�I��
//-------------------------------------
void CTeamProt_Finalize()
{

}

