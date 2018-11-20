//
//	CCoreObject.cpp	
//		Author:HIROMASA IKEDA	DATE:2018/10/13
//===============================================
#include<d3dx9.h>
#include<vector>

//Class
#include"Cube.h"
#include"CCoreObject.h"
#include"CCollisionShape.h"
#include"Bullet.h"
#include"Screwdrop.h"
#include"XModel.h"

#include "Debug_Collision.h"

// �b�蓖���蔻��@�\ ------------------------------------------------------------------------------------------------------------------- TMP!>
#include "CCollisionChecker.h"
//===============================================
//	CoreObject	�N���X
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
// �R���X�g���N�^�ł�Shape�n�N���X�̏�������CoreObject���g��transform�̃A�h���X��^���邱��. ������pTransform�̓R���X�g���N�^�I����,�j�������.
CoreObject::CoreObject(Transform* pTransform, Texture* pTexture, CORE_DISCHARGE_JUDGE_TYPE Type, D3DXVECTOR3 face) 
: 
	GameObject(pTransform, pTexture),
	ColShape(&transform.Position, 0.5f),
	CorrectSphere(&transform.Position, 1.0f)
{
	this->face = face;
	TmpCollisionChecker::GetInstance()->RegisterCollision_CoreObject( this );
	this->Type = Type;
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
CoreObject::~CoreObject()
{
	TmpCollisionChecker::GetInstance()->DeregisterCollision_CoreObject( this );
}

//-------------------------------------
//	���̃I�u�W�F�N�g�o�^
//-------------------------------------
void CoreObject::SetBody(BodyObject* pBodyObject)
{
	this->pBodyObject = pBodyObject;
}

//-------------------------------------
//	�A�[�}�[�I�u�W�F�N�g��o�^
//-------------------------------------
void CoreObject::Set(ArmorObject* pArmorObject)
{
	this->pArmor_Index.push_back(pArmorObject);
}

//--------------------------------------
//	�A�[�}�[�I�u�W�F�N�g�Ɠ��̂𓯎��ɓo�^
//--------------------------------------
void CoreObject::Set(ArmorObject* pArmorObject,BodyObject* pBodyObject)
{
	this->pArmor_Index.push_back(pArmorObject);
	this->pBodyObject = pBodyObject;
	this->Set_Parent(this->pBodyObject);
}

//-------------------------------------
//	�e�ɓ�������
//-------------------------------------
void CoreObject::Hit()
{
	this->bHit = true;

	if(this->pArmor_Index.size() > 0)
	{
		DischargeArmor( 120.0f, 1.0f, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) ); // ������������o�ɂ��Ď��Ȃ肷��I -------------------------------------------------------------------------- CAUTION!>
	}
}

//-------------------------------------
//	�X�V����
//-------------------------------------
void CoreObject::Update()
{
	//�e�Ƃ̓����蔻��
	for (int i = 0; i<BULLET_MAX; i++)
	{
		//�e���L��
		if (Bullet_IsEnable(i))
		{
			//�����񂹂�	
			if ( CollisionCheck::SphereVsSphere(CorrectSphere, Bullet_ColShape(i))&& this->pArmor_Index.size() > 0)
			{
				const D3DXVECTOR3* bullet_face = Bullet_GetBullet(i)->GetFace();
				D3DXVECTOR3 vec = *(CorrectSphere.pParentPos) - *(Bullet_ColShape(i).pParentPos);		// �l�W�ƒe�̒��S�ԃx�N�g��
				float Angle = acosf(D3DXVec3Dot(bullet_face, &vec));				// �e�̐i�s������vec�̐����p

				if (Angle <= D3DX_PI / 4 && Angle > 0.0f)
				{
					Bullet_GetBullet(i)->CorrectFace(vec);
				}
			}
			/*
			//�l�W�{�̂̓����蔻��
			if ( CollisionCheck::SphereVsSphere(ColShape, Bullet_ColShape(i)) && this->pArmor_Index.size() > 0)
			{
				Hit();
				Bullet_GetBullet(i)->SetFace(face);
				Bullet_GetBullet(i)->SetPos(this->transform.Position - ColShape.Radius * face * 1.0f);
				Screwdrop_Create(*(Bullet_GetBullet(i)->ColSphape.pParentPos),*( CorrectSphere.pParentPos ), Bullet::NORMAL, *Bullet_GetBullet(i)->GetFace());
				Bullet_GetBullet(i)->DisEnable();
			}
			*/
		}
	}


}

//-------------------------------------
//	�`��
//-------------------------------------
void CoreObject::Render()
{
	//�A�[�}�[�I�u�W�F�N�g����Ă���B
	if (this->pArmor_Index.size() > 0)
	{

		//X���f���̍s��ϊ�
		D3DXMATRIXA16 mtxWorld;
		D3DXMATRIXA16 mtxTranslation;
		D3DXMATRIXA16 mtxTranslation2;
		D3DXMATRIXA16 mtxRotation;
		D3DXMATRIXA16 mtxScaling;

		D3DXMatrixTranslation(&mtxTranslation, this->transform.Position.x, this->transform.Position.y, this->transform.Position.z);
		D3DXMatrixTranslation(&mtxTranslation2, 0.0f, -0.5f, 0.0f);
		D3DXMatrixRotationY(&mtxRotation, D3DX_PI);
		D3DXMatrixScaling(&mtxScaling, 0.4f, 0.4f, 0.4f);

		//����
		mtxWorld = mtxTranslation2*mtxRotation*mtxScaling*mtxTranslation;
		
		//�l�W�̕`��
		XModel_Render(GetMeshData(ScrewIndex), mtxWorld);

		//�����蔻��̕`��
		ColShape.DebugDraw();
		CorrectSphere.DebugDraw();
	}
}

//-------------------------------------
//	�l�W�̌����̎擾
//-------------------------------------
D3DXVECTOR3 CoreObject::GetFace()
{
	return this->face;
}

//-------------------------------------
//	����ݒ�
//-------------------------------------
void CoreObject::Set_JudgeType(CORE_DISCHARGE_JUDGE_TYPE Type)
{
	this->Type = Type;
}

//-------------------------------------
//	�A�[�}�[��΂�
//-------------------------------------
void CoreObject::DischargeArmor( float Margin, float Weight, D3DXVECTOR3 AddUnitVec, float SpeedRatio )
{
	for( int i = 0; i < pArmor_Index.size(); i++ )
	{
		// �A�[�}�[�j���C�x���g�܂ł̒x���t���[����Z�o
		float DelayFrame;

		float SquaredDist = D3DXVec3LengthSq( &( pArmor_Index.at( i )->transform.Position - transform.Position ) );

		switch( this->Type )
		{
			case CORE_JUDGE_TYPE_0:	//����
				DelayFrame = SquaredDist * Weight + Margin;
				break;
			case CORE_JUDGE_TYPE_1:	// �qArmor�S�Ĉ�x��
				DelayFrame = Weight + Margin;
				break;
			default:
				DelayFrame = Weight + Margin; // ���u����Type1��f�t�H���g��
				break;
		}

		// ���x��w��
		D3DXVECTOR3* pInitSpeed;
		const ARMOR_DISCHARGING_TYPE Type = pArmor_Index.at( i )->Discharging_Type;

		switch( Type )
		{

			case FALL:	//����ė�����
				pInitSpeed = new D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
				*pInitSpeed += AddUnitVec;
				break;
			case RADIALLY: //���ˏ�ɍL����
				pInitSpeed = new D3DXVECTOR3( pArmor_Index.at( i )->transform.Position - transform.Position );
				D3DXVec3Normalize( pInitSpeed, pInitSpeed );
				*pInitSpeed = ( *pInitSpeed + AddUnitVec ) * SpeedRatio;

		}

		pArmor_Index.at( i )->Break( *pInitSpeed, DelayFrame );
	}
	this->pArmor_Index.clear();
}