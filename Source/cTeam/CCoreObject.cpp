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
	ColShape(&transform.WorldPosition, 0.5f),
	CorrectSphere(&transform.WorldPosition, 1.0f)
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
		DischargeArmor( 120.0f, 1.0f, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) ); // ���������������o�ɂ��Ď��Ȃ肷��I -------------------------------------------------------------------------- CAUTION!>
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
	//�A�[�}�[�I�u�W�F�N�g�������Ă���B
	if (this->pArmor_Index.size() > 0)
	{

		//X���f���̍s��ϊ�
		D3DXMATRIXA16 mtxBaseTransform;		// ��ϊ��s��
		D3DXMATRIXA16 mtxBaseTranslation;
		D3DXMATRIXA16 mtxBaseRotation;	
		D3DXMATRIXA16 mtxBaseScaling;	

		D3DXMATRIXA16 mtxWorld;
		D3DXMATRIXA16 mtxTranslation;
		D3DXMATRIXA16 mtxRotation;
		/*
		D3DXMATRIXA16 mtxRotation2;
		D3DXMATRIXA16 mtxScaling;

		this->transform.Set_WorldTransform();
		D3DXMatrixTranslation(&mtxTranslation, this->transform.WorldPosition.x, this->transform.WorldPosition.y, this->transform.WorldPosition.z);
		D3DXMatrixTranslation(&mtxTranslation2, 0.0f, -0.5f, 0.0f);
		//D3DXMatrixRotationY(&mtxRotation, D3DX_PI);
		D3DXMatrixRotationYawPitchRoll(&mtxRotation2,this->transform.WorldRotation.y,this->transform.WorldRotation.x,this->transform.WorldRotation.z);
		D3DXMatrixScaling(&mtxScaling, 0.4f, 0.4f, 0.4f);
		

		//����
		mtxWorld = (mtxTranslation2*mtxScaling)*mtxTranslation;
		*/


		D3DXMATRIXA16 mtxRotationY;
		D3DXMATRIXA16 mtxRotationAxis;
		D3DXVECTOR3 vecFaceGroud;
		D3DXVECTOR3 vecRight;

		D3DXMatrixTranslation(&mtxBaseTranslation, 0.0f, -0.5f, 0.0f);	// ���_�ɕ��s�ړ�
		D3DXMatrixRotationY(&mtxBaseRotation, D3DX_PI);					// Y������ɔ���]���Đ��ʂɌ�����
		D3DXMatrixScaling(&mtxBaseScaling, 0.4f, 0.4f, 0.4f);			// �T�C�Y����

		mtxBaseTransform = mtxBaseTranslation * mtxBaseRotation * mtxBaseScaling;	// ��ϊ��s��̐ݒ�

		if (this->face == D3DXVECTOR3(0.0f, 1.0f, 0.0f))
		{
			D3DXMatrixRotationX(&mtxRotation, -D3DX_PI / 2);
		}
		else if (this->face == D3DXVECTOR3(0.0f, -1.0f, 0.0f))
		{
			D3DXMatrixRotationX(&mtxRotation, D3DX_PI / 2);
		}
		else
		{
			vecFaceGroud = this->face;
			vecFaceGroud.y = 0.0f;
			D3DXVec3Normalize(&vecFaceGroud, &vecFaceGroud);
			vecRight.x = vecFaceGroud.z;
			vecRight.y = 0.0f;
			vecRight.z = -vecFaceGroud.x;
			D3DXMatrixRotationY(&mtxRotationY, atan2f(vecFaceGroud.x, vecFaceGroud.z));
			D3DXMatrixRotationAxis(&mtxRotationAxis, &vecRight, acosf(D3DXVec3Dot(&this->face, &vecFaceGroud)));
			mtxRotation = mtxRotationY * mtxRotationAxis;
		}


		this->transform.Set_WorldTransform();
		D3DXMATRIX MtxRotation;
		D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->transform.WorldRotation.y, this->transform.WorldRotation.x, this->transform.WorldRotation.z);
		D3DXVec3TransformNormal(&this->transform.WorldPosition, &this->transform.WorldPosition,&MtxRotation);

		D3DXMatrixTranslation(&mtxTranslation, this->transform.WorldPosition.x, this->transform.WorldPosition.y, this->transform.WorldPosition.z);		// ���s�ړ�

		//����
		mtxWorld = mtxBaseTransform * mtxRotation * mtxTranslation;

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
		// �A�[�}�[�j���C�x���g�܂ł̒x���t���[�����Z�o
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
				pInitSpeed = new D3DXVECTOR3( pArmor_Index.at( i )->transform.Position - transform.Position );
				D3DXVec3Normalize( pInitSpeed, pInitSpeed );
				*pInitSpeed = ( *pInitSpeed + AddUnitVec ) * SpeedRatio;

		}

		pArmor_Index.at( i )->Break( *pInitSpeed, DelayFrame );
	}
	this->pArmor_Index.clear();
}