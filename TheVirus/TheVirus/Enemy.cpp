#include "Enemy.h"



CEnemy::CEnemy()
{
	var["isMonster"] = 1;
	var["moveCounter"] = 0;
	speed = (float)(rand()%40)/20;
	SetWH(rand() % 5 + 1, rand() % 5 + 1);
	SetImg("■");
	m_color = EColor::CC_RED;

	var["attackTimer"] = 0;

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
	if (var["attackTimer"] > 0) {
		--var["attackTimer"];
		Screen->SetColor(EColor::CC_DARKRED, EColor::CC_WHITE);
	}
	else {
		Screen->SetColor(EColor::CC_RED);
	}
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

		// 너비와 높이가 더이상 줄어들지 않는다면 삭제한다.
		// 오브젝트가 폭탄이 아닌 불렛이라도 바로 삭제한다.
		if (nowW <= 0 || nowH <= 0) {
			Destory();
			if (obj->var["isBomb"] == 0) obj->Destory();
		}
		else {
			SetWH(nowW, nowH);
			if (obj->var["isBomb"] == 0) obj->Destory();
		}

		// 피격시 뒤로 밀어주기
		if (GetX() + GetW() / 2 > MainChar->GetX() + MainChar->GetW() / 2) PlusX(rand()%3);
		if (GetX() + GetW() / 2 < MainChar->GetX() + MainChar->GetW() / 2) PlusX(-rand() % 3);
		if (GetY() + GetH() / 2 > MainChar->GetY() + MainChar->GetH() / 2) PlusY(rand() % 3);
		if (GetY() + GetH() / 2 < MainChar->GetY() + MainChar->GetH() / 2) PlusY(-rand() % 3);

		var["attackTimer"] = 5;
	}
}
