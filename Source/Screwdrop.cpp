//
//	Screwdrop.cpp
//		Author:�n��	DATE:2018/10/23
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------
#include "Screwdrop.h"

//===============================================
//	�}�N����`
//===============================================
#define BULLET_MAX (256)				//����Ă邾�낪�I�I
#define SCREW_DROP_SPEED (0.03f)		//�������x
#define SCREW_ROTATION_SPEED (0.01f)	//��]���̈ړ����x
#define ROTATION_FRAME_MAX (1000)		//��]�t���[����

//===============================================
//	�\����
//===============================================

//===============================================
//	�O���[�o���ϐ�
//===============================================
Screwdrop g_Screwdrop[BULLET_MAX];		//���v�����̔z��I

//================================================
//	�֐�		
//================================================
//-------------------------------------
//	������
//-------------------------------------
void Screwdrop_Init()
{
	for (int i = 0; i<BULLET_MAX; i++)
	{
		g_Screwdrop[i].IsEnable = false;
		g_Screwdrop[i].BulletPosition = D3DXVECTOR3(0.5f, 0.5f,0.5f);
		g_Screwdrop[i].ScrewPosition = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		g_Screwdrop[i].bullet_type = Bullet::NORMAL;
		g_Screwdrop[i].face = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		g_Screwdrop[i].rotation_count = 0;
		memcpy(&g_Screwdrop[i].BulletMesh, GetMeshData(BulletIndex), sizeof(MeshData));
		memcpy(&g_Screwdrop[i].ScrewMesh, GetMeshData(ScrewIndex), sizeof(MeshData));
	}
}

//-------------------------------------
//	�X�V
//-------------------------------------
void Screwdrop_Update()
{
	for (int i = 0; i< BULLET_MAX; i++)
	{
		//�L���Ȃ��
		if (g_Screwdrop[i].IsEnable)
		{
			//ROTATION_FRAME_MAX�ȉ��Ȃ��
			if (g_Screwdrop[i].rotation_count <= ROTATION_FRAME_MAX)
			{
				//��]���Ȃ���O��
				g_Screwdrop[i].BulletPosition -= g_Screwdrop[i].face * SCREW_ROTATION_SPEED;
				g_Screwdrop[i].ScrewPosition -= g_Screwdrop[i].face * SCREW_ROTATION_SPEED;
				g_Screwdrop[i].rotation_count+=10;
			}
			else
			{
				//�n�ʂɐڒn����܂ŗ�����
				if (g_Screwdrop[i].BulletPosition.y >= 0.0f/*�n��*/)
				{
					g_Screwdrop[i].BulletPosition.y -= SCREW_DROP_SPEED;
					g_Screwdrop[i].ScrewPosition.y -= SCREW_DROP_SPEED;
				}
				else
				{
					//������
					Screwdrop_DisEnable(i);
				}
			}
		}
	}
}

//-------------------------------------
//	�`��
//-------------------------------------
void Screwdrop_Render()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//�L���Ȃ�
		if (g_Screwdrop[i].IsEnable)
		{
			D3DXMATRIX mtxWorld;
			D3DXMATRIX mtxRotation;
			D3DXMATRIX mtxTranslation;
			D3DXMATRIX mtxScaling;

			//���s�ړ�
			D3DXMatrixTranslation(&mtxTranslation, g_Screwdrop[i].BulletPosition.x, g_Screwdrop[i].BulletPosition.y, g_Screwdrop[i].BulletPosition.z);

			//Face�����ɉ�]
			D3DXMatrixRotationAxis(&mtxRotation, &g_Screwdrop[i].face,D3DXToRadian(3*g_Screwdrop[i].rotation_count));
			//D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(g_Screwdrop[i].rotation_count));
			
			//�X�P�[����ύX
			D3DXMatrixScaling(&mtxScaling, 0.3f, 0.3f, 0.3f);	//�}�W�b�N�i���o

			//���[���h�s��
			mtxWorld = mtxRotation * mtxScaling * mtxTranslation;
			System_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);	//���̓o�^�Ӗ�����H

			//�o���b�g�̕`��֐�
			XModel_Render(&g_Screwdrop[i].BulletMesh, mtxWorld);


			D3DXMATRIX mtxTranlationScrew;		// �l�W�����_�Ɉړ����邽�߂̕��s�ړ��s��
			D3DXMATRIX mtxRotationScrew;		// �l�W�𐳑΂����邽�߂̉�]�s��
			
			//���s�ړ�
			D3DXMatrixTranslation(&mtxTranlationScrew, 0.0f, -0.5f, 0.0f);	//�}�W�b�N�i���o

			//�X�P�[����ύX
			D3DXMatrixScaling(&mtxScaling, 0.5f, 0.5f, 0.5f);

			//Y���𒆐S�ɔ���
			D3DXMatrixRotationY(&mtxRotationScrew, D3DX_PI);
			
			//�X�N�����[�̈ʒu�Ɉڍs
			D3DXMatrixTranslation(&mtxTranslation, g_Screwdrop[i].ScrewPosition.x, g_Screwdrop[i].ScrewPosition.y, g_Screwdrop[i].ScrewPosition.z);
		
			//���[���h�s��ϊ�
			mtxWorld = mtxTranlationScrew * mtxRotationScrew * mtxScaling * mtxRotation * mtxTranslation;
			
			System_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);	//���̓o�^�Ӗ�����H

			//�l�W�̕`��֐�
			XModel_Render(&g_Screwdrop[i].ScrewMesh, mtxWorld);

		}
	}
}

//-------------------------------------
//	����
//-------------------------------------
void  Screwdrop_Create(D3DXVECTOR3 pos_bullet, D3DXVECTOR3 pos_screw, Bullet::TYPE type, D3DXVECTOR3 face)
{
	for (int i = 0; i< BULLET_MAX; i++)
	{
		if (!g_Screwdrop[i].IsEnable)
		{
			g_Screwdrop[i].ScrewPosition = pos_screw;
			g_Screwdrop[i].BulletPosition = pos_bullet;
			g_Screwdrop[i].bullet_type = type;
			g_Screwdrop[i].face = face;
			g_Screwdrop[i].rotation_count = 0;
			g_Screwdrop[i].IsEnable = true;
			return;
		}
	}
}

//-------------------------------------
//	�폜
//-------------------------------------
void Screwdrop_DisEnable(int index)
{
	g_Screwdrop[index].IsEnable = false;
}
