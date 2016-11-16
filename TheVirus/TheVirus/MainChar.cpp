#include "externValue.h"
#include "Bullet.h"
#include "MainChar.h"
#include "Main.h"

CMainChar::CMainChar() : CGameObject(10, 10, 5, 5, "■")
{
	m_color = EColor::CC_GREEN;
	speed = 3;
	moveTimer = 0;
	ammo = 5;
}
CMainChar::~CMainChar()
{
}
void CMainChar::Draw()
{
	EColor oldColor = Screen->GetColor();
	EColor oldBkColor = Screen->GetBkColor();
	
	Screen->SetColor(m_color, m_bkColor);
	for (int i = 0; i < GetW(); i++) {
		for (int j=0; j < GetH(); j++){
			Screen->Print(GetX()+i, GetY()+j, m_img, 2);
		}
	}
	Screen->SetColor(oldColor, oldBkColor);
}
void CMainChar::Move()
{
	// 키가 입력되었다면
	--moveTimer;
	if (onKey[KEY_LEFT] || onKey[KEY_UP] || onKey[KEY_RIGHT] || onKey[KEY_DOWN]) {

		// 메인 캐릭터를 제외하고 모두 움직여줍니다.
		if (moveTimer <= 0) {
			if (onKey[KEY_LEFT]) {
				for (auto i : Gameobjects) {
					if (i == MainChar) continue;
					i->PlusX(1);
				}
			}
			if (onKey[KEY_UP]) {
				for (auto i : Gameobjects) {
					if (i == MainChar) continue;
					i->PlusY(1);
				}
			}
			if (onKey[KEY_RIGHT]) {
				for (auto i : Gameobjects) {
					if (i == MainChar) continue;
					i->PlusX(-1);
				}
			}
			if (onKey[KEY_DOWN]) {
				for (auto i : Gameobjects) {
					if (i == MainChar) continue;
					i->PlusY(-1);
				}
			}
			moveTimer = WORLD_SPEED / speed;
		}
	}
}
void CMainChar::Func()
{
}

void CMainChar::IsAttack(CGameObject * obj)
{
	if (obj->var["isMonster"] == 1) {
		int nowW = GetW();
		int nowH = GetH();

		if (rand() % 2 == 1 && nowW!=1) {
			--nowW;
		}
		else if(nowH!=1) --nowH;
		else {
			--nowW;
		}
		if (nowW == 0) {
			system("cls");
			cout << "게임오버";
			exit(1);
		}

		SetWH(nowW, nowH);
		SetPosition(SCREEN_WIDTH / 2 - MainChar->GetW() / 2, SCREEN_HEIGHT / 2 - MainChar->GetH() / 2);

		obj->Destory();
	}
}
void CMainChar::Shoot_L()
{
	CBullet* tmp = new CBullet(0);
	Gameobjects.push_back(tmp);
}

void CMainChar::Shoot_R() {
	if (ammo > 0) {
		CBullet* tmp = new CBullet(1);
		Gameobjects.push_back(tmp);
		ammo--;
	}
}