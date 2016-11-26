#define _CRT_SECURE_NO_WARNINGS
#include "Bullet.h"

float Distance(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}
CBullet::CBullet(bool bIsBomb)
{
	var["isBullet"] = 1;
	moveTimer = 0;
	m_bIsBomb = bIsBomb;

	float dist = Distance(mouse_x, mouse_y, GetX() + GetW() / 2, GetY() + GetH() / 2);
	if (bIsBomb) {
		var["smallCnt"] = 0;
		var["isBomb"] = 1;
		var["destroy"] = WORLD_SPEED;
		strcpy(m_img, "¡Ú");
		SetW(10);
		SetH(10);
		speed = 7;
	}
	else {
		var["isBomb"] = 0;
		strcpy(m_img, "¡Ü");
		SetW(1);
		SetH(1);
		speed = 8;
		dist = Distance(mouse_x, mouse_y, GetX() + GetW() / 2, GetY() + GetH() / 2) / 5;
	}

	SetX(MainChar->GetX() + MainChar->GetW() / 2 - GetW() / 2);
	SetY(MainChar->GetY() + MainChar->GetH() / 2 - GetH() / 2);

	vecX = (mouse_x - GetX() - GetW()/2)/ dist;
	vecY = (mouse_y - GetY() - GetH()/2)/ dist;

	if (vecX == 0.0f && vecY == 0.0f) {
		vecX = rand() % 2 ? 1 : -1;
		vecY = rand() % 2 ? 1 : -1;
	}

	m_color = EColor::CC_MAGENTA;
}


CBullet::~CBullet()
{
}

void CBullet::Draw()
{
	EColor oldColor = Screen->GetColor();
	EColor oldBkColor = Screen->GetBkColor();

	Screen->SetColor(m_color, m_bkColor);
	for (int i = 0; i < GetW(); i++) {
		for (int j = 0; j < GetH(); j++) {
			// ÆøÅº Å¸ÀÔÀÎ°¡?
			if (m_bIsBomb == true) {
				Screen->SetColor((EColor)(rand() % 16));
				if(rand()%3==1) Screen->SetBKColor((EColor)(rand() % 16));
				if(rand()%5==1) Screen->Print(GetX() + i, GetY() + j, m_img, 2);
				Screen->SetColor(m_color, m_bkColor);
			}
			else Screen->Print(GetX() + i, GetY() + j, m_img, 2);
		}
	}
	Screen->SetColor(oldColor, oldBkColor);
}

void CBullet::Move()
{
	--moveTimer;
	if (moveTimer <= 0) {
		PlusX(vecX);
		PlusY(vecY);
		moveTimer = WORLD_SPEED / speed;
	}

	if (GetX() <= -100 || GetY() <= -100 || GetX() >= SCREEN_WIDTH + 100 || GetY() >= SCREEN_HEIGHT + 100) this->Destory();
}

void CBullet::Func()
{
	++var["smallCnt"];
	if (var["smallCnt"] >= 5) {
		var["smallCnt"] = 0;
		if (m_bIsBomb) {
			if (var["destroy"] <= 0) {
				SetW(GetW() - 2);
				SetH(GetH() - 2);
				PlusPosition(1, 1);
				var["destroy"] = WORLD_SPEED;
			}
			else var["destroy"] --;
		}
	}
	if (Distance(GetX() + GetW() / 2, GetY() + GetH() / 2, MainChar->GetX() + MainChar->GetW() / 2, MainChar->GetY() + MainChar->GetH() / 2) >= 80) {
		this->Destory();
	}
}

void CBullet::IsAttack(CGameObject * obj)
{
}
