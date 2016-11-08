#define _CRT_SECURE_NO_WARNINGS
#include "Bullet.h"
#include "externValue.h"

// 거리를 구하는 함수
float Distance(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}
CBullet::CBullet(bool bIsBomb)
{
	moveTimer = 0;
	m_bIsBomb = bIsBomb;

	if (bIsBomb) {
		var["destroy"] = WORLD_SPEED;
		strcpy(m_img, "★");
		SetW(7);
		SetH(7);
		speed = 7;
	}
	else {
		strcpy(m_img, "●");
		SetW(1);
		SetH(1);
		speed = 8;
	}

	SetX(MainChar->GetX() + MainChar->GetW() / 2 - GetW()/2);
	SetY(MainChar->GetY() + MainChar->GetH() / 2 - GetH()/2);
	float dist = Distance(mouse_x, mouse_y, GetX() + GetW() / 2, GetY() + GetH() / 2);
	vecX = (mouse_x - GetX() - GetW()/2)/ dist;
	vecY = (mouse_y - GetY() - GetH()/2)/ dist;
	m_color = EColor::CC_RED;
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
			// 폭탄 타입인가?
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
	if (m_bIsBomb) {
		if (var["destroy"]<=0) {
			SetW(GetW() - 2);
			SetH(GetH() - 2);
			PlusPosition(1, 1);
			var["destroy"] = WORLD_SPEED;
		}
		else var["destroy"] --;
	}
}

void CBullet::IsAttack(CGameObject * obj)
{
}
