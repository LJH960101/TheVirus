// ���ΰ��� ������ ��� Ŭ���� �Դϴ�.

#pragma once
#include"GameObject.h"
class CMainChar :
	public CGameObject
{
	int speed;
	int moveTimer;

	CMainChar();
	~CMainChar();
public:
	static CMainChar* GetInstance()
	{
		static CMainChar singleTone;
		return &singleTone;
	}
	void Draw();
	void Move();
	void Func();
	void IsAttack(CGameObject* obj);
	// ��Ŭ�� �̺�Ʈ�Դϴ�.
	void Shoot_L();
	// ��Ŭ�� �̺�Ʈ�Դϴ�.
	void Shoot_R();
};

