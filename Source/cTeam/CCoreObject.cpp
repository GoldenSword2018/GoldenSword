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

// �����蔻��o�^ ------------------------------------------------------------------------------------------------------------------- TMP!>
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
	ColShape(&transform, 0.5f),
	CorrectSphere(&transform, 1.0f)
{
	this->LocalFace = face;

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
	this->Set_Parent(this->pBodyObject);
}

//-------------------------------------
//	�A�[�}�[�I�u�W�F�N�g��o�^
//-------------------------------------
void CoreObject::SetArmor(ArmorObject* pArmorObject)
{
	this->pArmor_Index.push_back(pArmorObject);
	pArmorObject->transform.Set_Parent(&this->transform);
}

//--------------------------------------
//	�A�[�}�[�I�u�W�F�N�g�Ɠ��̂𓯎��ɓo�^
//--------------------------------------
void CoreObject::Set(ArmorObject* pArmorObject,BodyObject* pBodyObject)
{
	this->SetBody(pBodyObject);
	this->SetArmor(pArmorObject);
}

//-------------------------------------
//	�e�ɓ�������
//-------------------------------------
void CoreObject::Hit()
{
	this->bHit = true;

	if(this->pArmor_Index.size() > 0)
	{
		DischargeArmor( 30, 0.5f, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) ); // ���������������o�ɂ��Ď��Ȃ肷��I -------------------------------------------------------------------------- CAUTION!>
	}
}

//-------------------------------------
//	�X�V����
//-------------------------------------
void CoreObject::Update()
{
	if( pArmor_Index.size() <= 0 )
	{
		int a = 0;
	}
	//�e�Ƃ̓����蔻��ths
	for (int i = 0; i<BULLET_MAX; i++)
	{
		//�e���L��
		if (Bullet_IsEnable(i))
		{
			//�����񂹂�	
			if ( CollisionCheck::SphereVsSphere(CorrectSphere, Bullet_ColShape(i))&& this->pArmor_Index.size() > 0)
			{
				const D3DXVECTOR3* bullet_face = Bullet_GetBullet(i)->GetFace();
				D3DXVECTOR3 vec = (CorrectSphere.pParentTransform->Position) - (Bullet_ColShape(i).pParentTransform->Position);		// �l�W�ƒe�̒��S�ԃx�N�g��
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
	//�A�[�}�[�I�u�W�F�N�g�������Ă���B
	if (this->pArmor_Index.size() > 0)
	{
		D3DXMATRIXA16 mtxBaseTransform;    
		D3DXMATRIXA16 mtxBaseTranslation;
		D3DXMATRIXA16 mtxBaseRotation;    
		D3DXMATRIXA16 mtxBaseScaling;    

		D3DXMATRIXA16 mtxWorld;
		D3DXMATRIXA16 mtxTranslation;
		D3DXMATRIXA16 mtxRotation;

		D3DXMATRIXA16 mtxRotationY;
		D3DXMATRIXA16 mtxRotationAxis;
		D3DXVECTOR3 vecFaceGroud;
		D3DXVECTOR3 vecRight;

		D3DXMatrixIdentity( &mtxBaseTransform );

		if (this->LocalFace == D3DXVECTOR3(0.0f, 1.0f, 0.0f))
		{
		    D3DXMatrixRotationX(&mtxRotation, -D3DX_PI / 2);
		}
		else if (this->LocalFace == D3DXVECTOR3(0.0f, -1.0f, 0.0f))
		{
		    D3DXMatrixRotationX(&mtxRotation, D3DX_PI / 2);
		}
		else
		{
		    vecFaceGroud = this->LocalFace;
		    vecFaceGroud.y = 0.0f;
		    D3DXVec3Normalize(&vecFaceGroud, &vecFaceGroud);
		    vecRight.x = vecFaceGroud.z;
		    vecRight.y = 0.0f;
		    vecRight.z = -vecFaceGroud.x;
		    D3DXMatrixRotationY(&mtxRotationY, atan2f(vecFaceGroud.x, vecFaceGroud.z));
		    D3DXMatrixRotationAxis(&mtxRotationAxis, &vecRight, acosf(D3DXVec3Dot(&this->LocalFace, &vecFaceGroud)));
		    mtxRotation = mtxRotationY * mtxRotationAxis;
		 }
		this->transform.Set_WorldTransform();

		//����
		this->transform.MtxWorld = mtxBaseTransform * this->transform.GetWorldMatrix();

		////�l�W�̕`��
		XModel_Render(GetMeshData(ScrewIndex), this->transform.MtxWorld );

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
	return this->LocalFace;
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
// para0 ������int�^�ɂ��Ă܂��B
void CoreObject::DischargeArmor( int Margin, float Weight, D3DXVECTOR3 AddUnitVec, float SpeedRatio )
{
	for( int i = 0; i < pArmor_Index.size(); i++ )
	{
		// �A�[�}�[�j���C�x���g�܂ł̒x���t���[�����Z�o
		float DelayFrame;

		float SquaredDist = D3DXVec3LengthSq( &( pArmor_Index.at( i )->transform.GetWorldPosision() - transform.GetWorldPosision() ) );

		switch( this->Type )
		{
			case CORE_JUDGE_TYPE_0:	//����
				DelayFrame = SquaredDist * Weight + Margin;
				break;
			case CORE_JUDGE_TYPE_1:	// �qArmor�S�Ĉ�x��
				DelayFrame = Weight + Margin;
				break;
			default:
				DelayFrame = Weight + Margin; // ���u����Type1���f�t�H���g��
				break;
		}

		// ���x���w��
		D3DXVECTOR3* pInitSpeed;
		const ARMOR_DISCHARGING_TYPE Type = pArmor_Index.at( i )->Discharging_Type;

		switch( Type )
		{

			case FALL:	//����ė�����
				pInitSpeed = new D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
				*pInitSpeed += AddUnitVec;
				break;
			case RADIALLY: //���ˏ�ɍL����
				pInitSpeed = new D3DXVECTOR3( pArmor_Index.at( i )->transform.GetWorldPosision() - transform.GetWorldPosision() );
				D3DXVec3Normalize( pInitSpeed, pInitSpeed );
				*pInitSpeed = ( *pInitSpeed + AddUnitVec ) * SpeedRatio;

		}
		this;
		pArmor_Index.at( i )->Break( *pInitSpeed, DelayFrame );
		// ���[���h���W���ꎞ�I�ɕێ��B
		D3DXVECTOR3 tmp = pArmor_Index.at( i )->transform.GetWorldPosision();
		// �A�[�}�[�Ƃ̐e�q�֌W������
		pArmor_Index.at( i )->transform.pParent = NULL;
		// ���߂ă��[���h�|�W�V������ݒ�
		pArmor_Index.at( i )->transform.Position = tmp;
		D3DXVECTOR3 tmppos = pArmor_Index.at( i )->transform.Position;
		tmppos = tmppos;
	}
	this->pArmor_Index.clear();
}