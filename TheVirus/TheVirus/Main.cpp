#include "Main.h"
#include<stdio.h>


// 게임의 전역 변수들을 초기화 시킴.
void Init();
// 여러 입력을 처리하는 쓰레드 함수.
void Thread_input();
// 충돌 처리를 하는 알고리즘 함수.
bool CollisionChker(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

int main(VOID)
{
	// 게임의 기본 변수를 초기화 합니다.
	Init();

	// 게임의 시간을 담는 변수입니다.
	clock_t timer = clock();
	// 입력을 받는 쓰레드를 가동시킵니다.
	std::thread input_thread(Thread_input);
	
	while (bOnGame) {
		// 행동
		{
			// 리스트에 들어있는 모든 Gameobjects들의 Func함수를 실행시킵니다.
			for (std::list<CGameObject*>::iterator i = Gameobjects.begin(); i != Gameobjects.end();) {
				(*i)->Func();
				if ((*i)->bDieFlag) {// 삭제된 오브젝트는 처리한다.
					delete (*i);
					i = Gameobjects.erase(i);
				}
				else ++i;
			}
		}
		// 움직임
		{
			for (std::list<CGameObject*>::iterator i = Gameobjects.begin(); i != Gameobjects.end();) {
				(*i)->Move();
				if ((*i)->bDieFlag) {// 삭제된 오브젝트는 처리한다.
					delete (*i);
					i = Gameobjects.erase(i);
				}
				else ++i;
			}
		}
		// 충돌
		{
			// 오브젝트간의 충돌 처리
			{
				bool i_has_coll = false;
				for (std::list<CGameObject*>::iterator i = Gameobjects.begin(); i != Gameobjects.end();) {
					i_has_coll = false;
					for (std::list<CGameObject*>::iterator j = i; j != Gameobjects.end();) {
						if (i == j) { // i와 j가 같다면 continue;
							++j;
							continue;
						}

						// 충돌 했는가?
						if (CollisionChker((*i)->GetX(), (*i)->GetY(), (*i)->GetW(), (*i)->GetH(), (*j)->GetX(), (*j)->GetY(), (*j)->GetW(), (*j)->GetH())) {
							// 충돌 했다면, 서로의 isAttack을 출력.
							(*i)->IsAttack(*j);
							(*j)->IsAttack(*i);
						}

						if ((*j)->bDieFlag) {// 삭제된 오브젝트는 처리한다.
							delete (*j);
							j = Gameobjects.erase(j);
						}
						else ++j;

						if ((*i)->bDieFlag) {// 삭제된 오브젝트를 처리하고, i값이 바뀌므로 브레이크함.
							delete (*i);
							i = Gameobjects.erase(i);
							i_has_coll = true;
							break;
						}
					}
					if (!i_has_coll) ++i;
				}
			}
		}
		// 그리기
		{
			Screen->Clear();
			for (auto i : Gameobjects) i->Draw();
			// 크로스헤어 그리기
			{
				Screen->SetColor(EColor::CC_CYAN, EColor::CC_BLACK);
				Screen->Print(mouse_x, mouse_y - 1, "▲", 2);
				Screen->Print(mouse_x - 1, mouse_y, "◀", 2);
				Screen->Print(mouse_x, mouse_y, "■", 2);
				Screen->Print(mouse_x + 1, mouse_y, "▶", 2);
				Screen->Print(mouse_x, mouse_y + 1, "▼", 2);
			}
			Screen->Draw();
		}

		// 모든 프레임의 시간차를 동기화 시켜주기 위한 작업.
		{
			// 현재 시간과 이전 프레임의 시간의 차이를 구합니다.
			deltaTime = ((float)(clock() - timer) / CLOCKS_PER_SEC);
			// 프레임마다 항상 같은 시간이 될 수 있게 Sleep을 겁니다.
			if (deltaTime * 1000 < 20) Sleep(20.0f-deltaTime*1000);
			timer = clock();
		}
	}
	return 0;
}

void Init() {
	// 창 사이즈 조정
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	system("MODE CON COLS=160 LINES=51");

	// OnKey 초기화
	for (int i = 0; i < 200; i++) onKey[i] = false;

	// 메인 캐릭터를 GameObjects에다가 넣습니다.
	Gameobjects.push_front(MainChar);

	// 메인 캐릭터의 위치를 리셋 합니다.
	MainChar->SetPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	//
	CGameObject* obj = new CGameObject(MainChar->GetX()-6, MainChar->GetY()-6, "★");
	Gameobjects.push_back(obj);

	// 커서를 지웁니다.
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = true; // true 보임, false 안보임
	ConsoleCursor.dwSize = 1; // 커서사이즈
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor); // 설정
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 이하의 내용은 이해하지 않아도 괜찮습니다.
HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

void Thread_input() {
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");
	while (1)
	{
		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit("ReadConsoleInput");
		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				break;
			}
		}
	}

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);
}
VOID ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
	// 키가 입력되면 onKey[해당하는 키값]에 True를 넣어줍니다.
	if (ker.bKeyDown) onKey[ker.wVirtualKeyCode] = true;
	// 키가 입력되면 onKey[해당하는 키값]에 False를 넣어줍니다.
	else onKey[ker.wVirtualKeyCode] = false;
}

// 마우스의 이벤트 입니다.
VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	switch (mer.dwEventFlags)
	{
	case 0:
		// 좌클릭이 입력됬을 때,
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			// 메인캐릭터의 Shoot_L함수를 실행시킵니다.
			MainChar->Shoot_L();
		}
		// 우클릭이 입력됬을 때,
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			// 메인캐릭터의 Shoot_R함수를 실행시킵니다.
			MainChar->Shoot_R();
		}
		break;
	case MOUSE_MOVED:
		// 마우스가 움직이면 마우스의 좌표값을 알아옵니다.
		mouse_x = mer.dwMousePosition.X / 2;
		mouse_y = mer.dwMousePosition.Y;
		break;
	}
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}

// 충돌 처리를 하는 알고리즘 함수 입니다.
bool CollisionChker(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	if (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2)
	{
		return true;
	}

	return false;
}