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
//	MatrixTransform : �s�� �N���X
//===============================================
class MatrixTransform
{
private:
	D3DXMATRIX MtxWorld;					//���[���h�ϊ��s��
	D3DXMATRIX MtxTransform;				//�ʒu
	D3DXMATRIX MtxRotation;					//��]
	D3DXMATRIX MtxScale;					//�g��E�k��
public:
	MatrixTransform();
};

//===============================================
//	Transform : 3D��p�@�N���X
//===============================================
class Transform
{
private:
	
	static std::vector<Transform*> pIndex;
public :
	bool bConverted;			//�ϊ�������
	Transform* pParent;		//�e
	std::vector<Transform*> pChild;	//�q
	D3DXMATRIX MtxWorld;		//�ϊ������s��

	//��{���
	D3DXVECTOR3 Position;	//�ʒu
	D3DXVECTOR3 Scale;		//�T�C�Y
	D3DXVECTOR3 Rotation;	//��]

	//���[���h��Ԃ̏��	
	//	pParent->transform.position + this->transform.position;
	D3DXVECTOR3 WorldPosition;
	D3DXVECTOR3 WorldRotation;

	D3DCOLOR	Color;		//�F
	
	//������
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

	D3DXMATRIX Convert();					//�ϊ��J�n
	void Set_Parent(Transform* pParent);		//�e��ݒ�
	void Release_Parent();					//�e�Ɨ����
	void Set_WorldTransform();
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
