// 총알을 담는 클래스 입니다.

#pragma once
#include "externValue.h"
#include "GameObject.h"
#include "Tool.h"
class CBullet :
	public CGameObject
{
public:
	// 0은 주인공일반 1은 주인공폭탄
	bool m_bIsBomb;
	// 매 프레임마다 움직일 벡터입니다.
	float vecX, vecY;
	// 움직이는 시간을 관장하는 변수입니다.
	int moveTimer, speed;

	CBullet(bool bIsBomb);
	~CBullet();

	void Draw();
	void Move();
	void Func();
	void IsAttack(CGameObject* obj);
};

