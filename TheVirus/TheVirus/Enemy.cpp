#include "Enemy.h"



CEnemy::CEnemy()
{
	var["isMonster"] = 1;
	var["moveCounter"] = 0;
	speed = (float)(rand()%40)/20;
	SetWH(rand() % 5 + 1, rand() % 5 + 1);
	SetImg("■");
	m_color = EColor::CC_RED;

	// Enemy 위치 고르기
	if (rand() % 4 == 1) { // 상
		SetX((rand() % SCREEN_WIDTH + 2) - 1);
		SetY(-10);
	}
	else if (rand() % 3 == 1) { // 하
		SetX((rand() % SCREEN_WIDTH + 2) - 1);
		SetY(SCREEN_HEIGHT+10);
	}
	else if (rand() % 2 == 1) { // 좌
		SetX(-10);
		SetY((rand() % SCREEN_HEIGHT + 2) - 1);
	}
	else { // 우
		SetX(SCREEN_WIDTH + 10);
		SetY((rand() % SCREEN_HEIGHT + 2) - 1);
	}
}


CEnemy::~CEnemy()
{
}

void CEnemy::Draw()
{
	EColor oldColor = Screen->GetColor();
	EColor oldBkColor = Screen->GetBkColor();

	Screen->SetColor(m_color, m_bkColor);
	for (int i = 0; i < GetW(); i++) {
		for (int j = 0; j < GetH(); j++) {
			Screen->Print(GetX() + i, GetY() + j, m_img, 2);
		}
	}
	Screen->SetColor(oldColor, oldBkColor);
}

void CEnemy::Move()
{
	if (++var["moveCounter"] >= 10) {
		var["moveCounter"] = 0;

		if (GetX()+GetW()/2 > MainChar->GetX() + MainChar->GetW()/2) PlusX(-speed);
		else if (GetX() + GetW() / 2 < MainChar->GetX() + MainChar->GetW() / 2) PlusX(speed);
		if (GetY() + GetH() / 2 > MainChar->GetY() + MainChar->GetH() / 2) PlusY(-speed);
		else if (GetY() + GetH() / 2 < MainChar->GetY() + MainChar->GetH() / 2) PlusY(speed);
	}
}

void CEnemy::Func()
{
}

void CEnemy::IsAttack(CGameObject * obj)
{
	if (obj->var["isBullet"] == 1) {
		int nowW = GetW();
		int nowH = GetH();

		if (rand() % 2 == 1) nowW -= rand()%2+1;
		else nowH -= rand()%2+1;

		if (nowW == 0 || nowH == 0) {
			Destory();
			if (obj->var["isBomb"] == 0) obj->Destory();
		}
		else {
			SetWH(nowW, nowH);
			if (obj->var["isBomb"] == 0) obj->Destory();
		}
	}
}
