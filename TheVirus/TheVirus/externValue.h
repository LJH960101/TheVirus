// 여러 전역(extern) 변수들을 선언하는 파일 입니다.

#pragma once
#include"MainChar.h"
#include"Screen.h"
#include"Bullet.h"

#include<list>

class CBullet;

// 여러 오브젝트들의 타이머 초기값입니다.
extern const int WORLD_SPEED;
// 키가 입력되었는지 저장하는 함수입니다. onKey[65] -> 'A'키가 입력되었는가?
extern bool onKey[200];
// 마우스의 좌표값을 저장하는 함수입니다.
extern int mouse_x, mouse_y;
// 메인캐릭터의 변수입니다.
extern CMainChar* MainChar;
// 스크린의 변수입니다.
extern CScreen* Screen;
// 여러 총알을 담는 리스트입니다.
extern std::list<CGameObject*> Gameobjects;
// 프레임별 시간차를 담는 변수입니다.
extern float deltaTime;
// 게임 중임을 나타내는 변수입니다.
extern bool bOnGame;