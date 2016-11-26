// �Ѿ��� ��� Ŭ���� �Դϴ�.

#pragma once
#include "externValue.h"
#include "GameObject.h"
#include "Tool.h"
class CBullet :
	public CGameObject
{
public:
	// 0�� ���ΰ��Ϲ� 1�� ���ΰ���ź
	bool m_bIsBomb;
	// �� �����Ӹ��� ������ �����Դϴ�.
	float vecX, vecY;
	// �����̴� �ð��� �����ϴ� �����Դϴ�.
	int moveTimer, speed;

	CBullet(bool bIsBomb);
	~CBullet();

	void Draw();
	void Move();
	void Func();
	void IsAttack(CGameObject* obj);
};

