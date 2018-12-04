//
//	Transform.h
//		Author:HIROMASA IKEDA	DATE:2018/09/28
//===============================================
#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<d3dx9.h>
#include<vector>

//===============================================
//	Transform : 3D��p�@�N���X
//===============================================
class Transform
{
private:
	//�STransform���i�[
	static std::vector<Transform*> pIndex;

private:
	bool bConverted;				//�ϊ�������

public :
	Transform* pParent;				//�e
	std::vector<Transform*> pChild;	//�q

	D3DXMATRIX MtxWorld;		//�ϊ������s��


	//��Ԉʒu(���[���h��ԏ�ł̈ʒu�Ȃǂ�ێ����܂�)
	//�e�̈ʒu�Ȃǂ����Z��������
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;		//Radian
	D3DXVECTOR3 Scale;

	//��{�ʒu(���g�̈ʒu�Ȃǂ�ێ����܂�)
	D3DXVECTOR3 localPosition;
	D3DXVECTOR3 localRotation;
	D3DXVECTOR3 localScale;

	D3DCOLOR	Color;		//�F
	
	//����
	D3DXVECTOR3 up;			//��
	D3DXVECTOR3 forward;	//�O
	D3DXVECTOR3 right;		//�E

public:
	static void ResetConvert();

public:
	
	//�R���X�g���N�^
	Transform() :Transform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, D3DCOLOR_RGBA(255, 255, 255, 255)){};
	Transform(D3DCOLOR Color) :Transform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, Color) {};
	Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation) :Transform(Position, Scale, Rotation, D3DCOLOR_RGBA(255, 255, 255, 255)) {};
	Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation, D3DCOLOR Color);

	//�f�X�g���N�^
	~Transform();

public:
	//Get

	//Set

//	��]�֐�
//	forward�Ȃǂ̕����̒l�������̂Ŋ�{�͂��̊֐��Q���g��
public:
	void Rotation(const D3DXVECTOR3 value);
	void RotationAxis(const D3DXVECTOR3 Axis, const float value);

public:

	D3DXMATRIX Convert();					//�ϊ��J�n
	void Adjustment_Rotation();
	void Set_Parent(Transform* pParent);	//�e��ݒ�
	void Release_Parent();					//�e�Ɨ����
	void Set_WorldTransform();

	// ���[���h���W�ւ̃A�N�Z�T
	D3DXVECTOR3 GetWorldPosision( void );
	D3DXMATRIX GetWorldMatrix( void );
	void SetWorldPosition( D3DXVECTOR3 Position );
	void SetLocalPosition( D3DXVECTOR3 Position );

};

//===============================================
//	Transform2 : 2D��p�@�N���X
//===============================================
class Transform2
{
private:

public:
	D3DXVECTOR2 Position;	//�ʒu
	D3DXVECTOR2 Scale;		//�T�C�Y
	float Rotation;			//��]
	D3DCOLOR Color;			//�F

	//�R���X�g���N�^
	Transform2();
	Transform2(D3DXVECTOR2 Position,D3DXVECTOR2 Scale,float Rotation);
	Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation,D3DCOLOR Color);
	
};

#endif
