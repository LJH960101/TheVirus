// 주인공의 정보를 담는 클래스 입니다.

#pragma once
#include"GameObject.h"
class CMainChar : public CGameObject
{
	int speed;
	int moveTimer;
	
	CMainChar();
	~CMainChar();
public:
	//소멸탄을 담는 변수
	int ammo;

	static CMainChar* GetInstance()
	{
		static CMainChar singleTone;
		return &singleTone;
	}
	void Draw();
	void Move();
	void Func();
	void IsAttack(CGameObject* obj);
	// 좌클릭 이벤트입니다.
	void Shoot_L();
	// 우클릭 이벤트입니다.
	void Shoot_R();
	void Reset();
};

