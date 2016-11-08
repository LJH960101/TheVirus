// ���� ����(extern) �������� �����ϴ� ���� �Դϴ�.

#pragma once
#include"MainChar.h"
#include"Screen.h"
#include"Bullet.h"

#include<list>

class CBullet;

// ���� ������Ʈ���� Ÿ�̸� �ʱⰪ�Դϴ�.
extern const int WORLD_SPEED;
// Ű�� �ԷµǾ����� �����ϴ� �Լ��Դϴ�. onKey[65] -> 'A'Ű�� �ԷµǾ��°�?
extern bool onKey[200];
// ���콺�� ��ǥ���� �����ϴ� �Լ��Դϴ�.
extern int mouse_x, mouse_y;
// ����ĳ������ �����Դϴ�.
extern CMainChar* MainChar;
// ��ũ���� �����Դϴ�.
extern CScreen* Screen;
// ���� �Ѿ��� ��� ����Ʈ�Դϴ�.
extern std::list<CGameObject*> Gameobjects;
// �����Ӻ� �ð����� ��� �����Դϴ�.
extern float deltaTime;
// ���� ������ ��Ÿ���� �����Դϴ�.
extern bool bOnGame;