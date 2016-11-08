#include "Main.h"
#include<stdio.h>


// ������ ���� �������� �ʱ�ȭ ��Ŵ.
void Init();
// ���� �Է��� ó���ϴ� ������ �Լ�.
void Thread_input();
// �浹 ó���� �ϴ� �˰��� �Լ�.
bool CollisionChker(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

int main(VOID)
{
	// ������ �⺻ ������ �ʱ�ȭ �մϴ�.
	Init();

	// ������ �ð��� ��� �����Դϴ�.
	clock_t timer = clock();
	// �Է��� �޴� �����带 ������ŵ�ϴ�.
	std::thread input_thread(Thread_input);
	
	while (bOnGame) {
		// �ൿ
		{
			// ����Ʈ�� ����ִ� ��� Gameobjects���� Func�Լ��� �����ŵ�ϴ�.
			for (std::list<CGameObject*>::iterator i = Gameobjects.begin(); i != Gameobjects.end();) {
				(*i)->Func();
				if ((*i)->bDieFlag) {// ������ ������Ʈ�� ó���Ѵ�.
					delete (*i);
					i = Gameobjects.erase(i);
				}
				else ++i;
			}
		}
		// ������
		{
			for (std::list<CGameObject*>::iterator i = Gameobjects.begin(); i != Gameobjects.end();) {
				(*i)->Move();
				if ((*i)->bDieFlag) {// ������ ������Ʈ�� ó���Ѵ�.
					delete (*i);
					i = Gameobjects.erase(i);
				}
				else ++i;
			}
		}
		// �浹
		{
			// ������Ʈ���� �浹 ó��
			{
				bool i_has_coll = false;
				for (std::list<CGameObject*>::iterator i = Gameobjects.begin(); i != Gameobjects.end();) {
					i_has_coll = false;
					for (std::list<CGameObject*>::iterator j = i; j != Gameobjects.end();) {
						if (i == j) { // i�� j�� ���ٸ� continue;
							++j;
							continue;
						}

						// �浹 �ߴ°�?
						if (CollisionChker((*i)->GetX(), (*i)->GetY(), (*i)->GetW(), (*i)->GetH(), (*j)->GetX(), (*j)->GetY(), (*j)->GetW(), (*j)->GetH())) {
							// �浹 �ߴٸ�, ������ isAttack�� ���.
							(*i)->IsAttack(*j);
							(*j)->IsAttack(*i);
						}

						if ((*j)->bDieFlag) {// ������ ������Ʈ�� ó���Ѵ�.
							delete (*j);
							j = Gameobjects.erase(j);
						}
						else ++j;

						if ((*i)->bDieFlag) {// ������ ������Ʈ�� ó���ϰ�, i���� �ٲ�Ƿ� �극��ũ��.
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
		// �׸���
		{
			Screen->Clear();
			for (auto i : Gameobjects) i->Draw();
			// ũ�ν���� �׸���
			{
				Screen->SetColor(EColor::CC_CYAN, EColor::CC_BLACK);
				Screen->Print(mouse_x, mouse_y - 1, "��", 2);
				Screen->Print(mouse_x - 1, mouse_y, "��", 2);
				Screen->Print(mouse_x, mouse_y, "��", 2);
				Screen->Print(mouse_x + 1, mouse_y, "��", 2);
				Screen->Print(mouse_x, mouse_y + 1, "��", 2);
			}
			Screen->Draw();
		}

		// ��� �������� �ð����� ����ȭ �����ֱ� ���� �۾�.
		{
			// ���� �ð��� ���� �������� �ð��� ���̸� ���մϴ�.
			deltaTime = ((float)(clock() - timer) / CLOCKS_PER_SEC);
			// �����Ӹ��� �׻� ���� �ð��� �� �� �ְ� Sleep�� �̴ϴ�.
			if (deltaTime * 1000 < 20) Sleep(20.0f-deltaTime*1000);
			timer = clock();
		}
	}
	return 0;
}

void Init() {
	// â ������ ����
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	system("MODE CON COLS=160 LINES=51");

	// OnKey �ʱ�ȭ
	for (int i = 0; i < 200; i++) onKey[i] = false;

	// ���� ĳ���͸� GameObjects���ٰ� �ֽ��ϴ�.
	Gameobjects.push_front(MainChar);

	// ���� ĳ������ ��ġ�� ���� �մϴ�.
	MainChar->SetPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	//
	CGameObject* obj = new CGameObject(MainChar->GetX()-6, MainChar->GetY()-6, "��");
	Gameobjects.push_back(obj);

	// Ŀ���� ����ϴ�.
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = true; // true ����, false �Ⱥ���
	ConsoleCursor.dwSize = 1; // Ŀ��������
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor); // ����
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ ������ �������� �ʾƵ� �������ϴ�.
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
	// Ű�� �ԷµǸ� onKey[�ش��ϴ� Ű��]�� True�� �־��ݴϴ�.
	if (ker.bKeyDown) onKey[ker.wVirtualKeyCode] = true;
	// Ű�� �ԷµǸ� onKey[�ش��ϴ� Ű��]�� False�� �־��ݴϴ�.
	else onKey[ker.wVirtualKeyCode] = false;
}

// ���콺�� �̺�Ʈ �Դϴ�.
VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	switch (mer.dwEventFlags)
	{
	case 0:
		// ��Ŭ���� �Է��� ��,
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			// ����ĳ������ Shoot_L�Լ��� �����ŵ�ϴ�.
			MainChar->Shoot_L();
		}
		// ��Ŭ���� �Է��� ��,
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			// ����ĳ������ Shoot_R�Լ��� �����ŵ�ϴ�.
			MainChar->Shoot_R();
		}
		break;
	case MOUSE_MOVED:
		// ���콺�� �����̸� ���콺�� ��ǥ���� �˾ƿɴϴ�.
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

// �浹 ó���� �ϴ� �˰��� �Լ� �Դϴ�.
bool CollisionChker(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	if (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2)
	{
		return true;
	}

	return false;
}