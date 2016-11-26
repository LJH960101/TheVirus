#pragma once
#include"Main.h"
#include "GameObject.h"
#include "Tool.h"

class CEffect :
	public CGameObject
{
public:
	CEffect() : CGameObject(0, 0, "0") {
		SetX((rand() % SCREEN_WIDTH + 2) - 1);
		SetY(- 8);
		SetH(rand() % 3 + 5);
		m_color = EColor::CC_DARKGREEN;
		var["isEffect"] = 1;
		var["moveCnt"] = 0;
		var["moveSpeed"] = 1+rand()%4;
	}
	~CEffect() {}
	void Move() {};
	void Func(); 
	void Draw()
	{
		EColor oldColor = Screen->GetColor();
		EColor oldBkColor = Screen->GetBkColor();

		Screen->SetColor(m_color, m_bkColor);
		for (int i = 0; i < GetW(); i++) {
			for (int j = 0; j < GetH(); j++) {
				if(rand()%2) Screen->Print(GetX() + i, GetY() + j, "1", 2);
				else Screen->Print(GetX() + i, GetY() + j, "0", 2);
			}
		}
		Screen->SetColor(oldColor, oldBkColor);
	}
	void IsAttack(CGameObject* obj) {};
};

