#include "Enemy.h"



float Distance3(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}
CEnemy::CEnemy()
{
	var["isMonster"] = 1;
	var["moveCounter"] = 0;
	speed = rand()%4+1;
	SetWH(rand() % 5 + 2, rand() % 5 + 2);
	SetImg("■");
	m_color = EColor::CC_RED;

	var["attackTimer"] = 0;

	// Enemy 위치 고르기
	if (rand() % 4 == 1) { // 상
		SetX((rand() % SCREEN_WIDTH + 2) - 1);
		SetY(-15);
	}
	else if (rand() % 3 == 1) { // 하
		SetX((rand() % SCREEN_WIDTH + 2) - 1);
		SetY(SCREEN_HEIGHT+15);
	}
	else if (rand() % 2 == 1) { // 좌
		SetX(-15);
		SetY((rand() % SCREEN_HEIGHT + 2) - 1);
	}
	else { // 우
		SetX(SCREEN_WIDTH + 15);
		SetY((rand() % SCREEN_HEIGHT + 2) - 1);
	}

	var["isNontarget"] = rand() % 6;
	if (var["isNontarget"] != 1) {
		SetWH(1, 1);
		var["isNontarget"] = 1;
		var["vecX"] = (MainChar->GetX() - GetX()) / 10;
		var["vecY"] = (MainChar->GetY() - GetY()) / 10;
		if (var["vecX"] == 0 || var["vecY"] == 0) {
			var["vecX"] = rand() % 2 ? 4 : -4;
			var["vecY"] = rand() % 2 ? 4 : -4;
		}
	}
	else var["isNontarget"] = 0;

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

		if (var["isNontarget"] == 1) {
			PlusX(var["vecX"]);
			PlusY(var["vecY"]);
		}
		else {
			if (GetX() + GetW() / 2 > MainChar->GetX() + MainChar->GetW() / 2 &&  abs(MainChar->GetX() + MainChar->GetW() / 2 - GetX() + GetW() / 2)>=GetW()/2 ) PlusX(-speed);
			else if (GetX() + GetW() / 2 < MainChar->GetX() + MainChar->GetW() / 2 && abs(MainChar->GetX() + MainChar->GetW() / 2 - GetX() + GetW() / 2)>=GetW() / 2) PlusX(speed);
			if (GetY() + GetH() / 2 > MainChar->GetY() + MainChar->GetH() / 2 && abs(MainChar->GetY() + MainChar->GetH() / 2 - GetY() + GetH() / 2)>=GetH() / 2) PlusY(-speed);
			else if (GetY() + GetH() / 2 < MainChar->GetY() + MainChar->GetH() / 2 && abs(MainChar->GetY() + MainChar->GetH() / 2 - GetY() + GetH() / 2)>=GetH() / 2) PlusY(speed);
		}
	}
}

void CEnemy::Func()
{
	if (var["isNontarget"] == 1 && Distance3(GetX() + GetW() / 2, GetY() + GetH() / 2, MainChar->GetX() + MainChar->GetW() / 2, MainChar->GetY() + MainChar->GetH() / 2) >= 100) {
		this->Destory();
	}
	else if (Distance3(GetX() + GetW() / 2, GetY() + GetH() / 2, MainChar->GetX() + MainChar->GetW() / 2, MainChar->GetY() + MainChar->GetH() / 2) >= 300) {
		this->Destory();
	}
}

void CEnemy::IsAttack(CGameObject * obj)
{
	if (obj->var["isBullet"] == 1) {
		score += 10;

		int nowW = GetW();
		int nowH = GetH();

		if (rand() % 2 == 1) nowW -= rand()%2+1;
		else nowH -= rand()%2+1;

		// 너비와 높이가 더이상 줄어들지 않는다면 삭제한다.
		// 오브젝트가 폭탄이 아닌 불렛이라도 바로 삭제한다.
		if (nowW <= 1 || nowH <= 1) {
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
