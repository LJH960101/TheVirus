#include"externValue.h"
bool onKey[200];
int mouse_x, mouse_y;
CMainChar* MainChar = CMainChar::GetInstance();
CScreen* Screen = CScreen::GetInstance();
const int WORLD_SPEED = 10;
std::list<CGameObject*> Gameobjects;
float deltaTime = 0;
bool bOnGame = true;
int score = 0;