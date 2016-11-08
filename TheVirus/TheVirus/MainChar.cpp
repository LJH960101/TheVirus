#include "externValue.h"
#include "Bullet.h"
#include "MainChar.h"
#include "Main.h"

CMainChar::CMainChar() : CGameObject(10, 10, 3, 3, "■")
{
	m_color = EColor::CC_GREEN;
	speed = 3;
	moveTimer = 0;
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
	cout << "?" ;
}
void CMainChar::Shoot_L()
{
	CBullet* tmp = new CBullet(0);
	Gameobjects.push_back(tmp);
}

void CMainChar::Shoot_R() {
	CBullet* tmp = new CBullet(1);
	Gameobjects.push_back(tmp);
}