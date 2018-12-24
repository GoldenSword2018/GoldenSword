//
//	Animetion.h
//		USER:HIROMASA IKEDA		DATE:2018/09/28
//===============================================
#pragma once
#ifndef ANIMETION_H
#define ANIMETION_H

#include<d3dx9.h>

#include"common.h"
#include"CTransform.h"
#include"Texture.h"

//===============================================
//	関数宣言	
//===============================================
void Animation_Initialize();	
void Animation_Update();
int Animation_GetFrame();

bool Animation_NoLoop(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);		//ループしない
void Animation_Loop(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);			//ループする
void Animation_Loop_Rotate(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);	//ループ回転する

void Animation_Score(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation, int Score, bool bLeft, bool bZero, int digitNum);	//スコア

#endif

