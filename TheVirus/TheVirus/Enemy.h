#pragma once
#include"Main.h"
#include"GameObject.h"
class CEnemy : public CGameObject
{
public:
	float speed;
	CEnemy();
	~CEnemy();

	void Draw();
	void Move();
	void Func();
	void IsAttack(CGameObject* obj);
};

