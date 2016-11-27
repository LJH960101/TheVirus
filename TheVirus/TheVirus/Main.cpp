#include "Main.h"
#include "RankClass.h"

// ������ ���� �������� �ʱ�ȭ ��Ŵ.
void Init();
// ���� �Է��� ó���ϴ� ������ �Լ�.
void Thread_input();
// �浹 ó���� �ϴ� �˰��� �Լ�.
bool CollisionChker(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
void InitGame();

#define MAIN_SPEED1 10
#define MAIN_SPEED2 30

RankClass myRank;

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void RankingScreen() {
	int i;

	for (i = 54; i < 108; i += 2)
	{
		gotoxy(i, 4);
		printf("��");
		Sleep(MAIN_SPEED1);
	}

	gotoxy(108, 4);
	printf("��");
	for (i = 5; i < 25; i++)
	{
		gotoxy(108, i);
		printf("��");
		Sleep(MAIN_SPEED2);
	}

	gotoxy(108, 24);
	printf("��");
	for (i = 106; i > 52; i -= 2)
	{
		gotoxy(i, 24);
		printf("��");
		Sleep(MAIN_SPEED1);
	}

	gotoxy(52, 24);
	printf("��");
	for (i = 23; i > 4; i--)
	{
		gotoxy(52, i);
		printf("��");
		Sleep(MAIN_SPEED2);
	}

	gotoxy(52, 4);
	printf("��");
	Sleep(600);

	for (int i = 0; i < 10; i++) {
		if(i>=5) gotoxy(52 + 38 , 6 + (i-5)*3+2);
		else gotoxy(52 + 8, 6 + i*3+2);
		std::cout << i + 1 << ". " << myRank.GetRank(i) << "��";
	}
	gotoxy(65, 28);
	std::cout << "Press Enter to back main-menu.";;
	while (1) {
		if (onKey[13]) break;
	}
	Screen->Draw_Clear();
}
void LoadingScreen() {

	int i;

	for (i = 54; i < 108; i += 2)
	{
		gotoxy(i, 4);
		printf("��");
		Sleep(MAIN_SPEED1);
	}

	gotoxy(108, 4);
	printf("��");
	for (i = 5; i < 25; i++)
	{
		gotoxy(108, i);
		printf("��");
		Sleep(MAIN_SPEED2);
	}

	gotoxy(108, 24);
	printf("��");
	for (i = 106; i > 52; i -= 2)
	{
		gotoxy(i, 24);
		printf("��");
		Sleep(MAIN_SPEED1);
	}

	gotoxy(52, 24);
	printf("��");
	for (i = 23; i > 4; i--)
	{
		gotoxy(52, i);
		printf("��");
		Sleep(MAIN_SPEED2);
	}

	gotoxy(52, 4);
	printf("��");
	Sleep(600);

	gotoxy(70, 10);
	std::cout << "���ᡡ�ᡡ�ᡡ����" << std::endl;
	gotoxy(70, 11);
	std::cout << "���ᡡ���ᡡ�ᡡ�ᡡ��" << std::endl;
	gotoxy(70, 12);
	std::cout << "���ᡡ�����ᡡ����" << std::endl;
	gotoxy(70, 13);
	std::cout << "���ᡡ���ᡡ�ᡡ�ᡡ��" << std::endl;
	gotoxy(70, 14);
	std::cout << "���ᡡ���ᡡ�ᡡ����" << std::endl;
	gotoxy(62, 16);
	std::cout << "�ᡡ�ᡡ���ᡡ��ᡡ���ᡡ�ᡡ����" << std::endl;
	gotoxy(62, 17);
	std::cout << "�ᡡ�ᡡ���ᡡ���ᡡ�ᡡ�ᡡ�ᡡ�ᡡ��" << std::endl;
	gotoxy(62, 18);
	std::cout << "�ᡡ�ᡡ���ᡡ����ᡡ���ᡡ�ᡡ����" << std::endl;
	gotoxy(62, 19);
	std::cout << "�ᡡ�ᡡ���ᡡ���ᡡ�ᡡ�ᡡ�ᡡ������" << std::endl;
	gotoxy(62, 20);
	std::cout << "���ᡡ�����ᡡ�ᡡ�ᡡ���ᡡ����" << std::endl;
	Sleep(500);


	gotoxy(40, 26);
	std::cout << "����������������������������������������������������������������������������������" << std::endl;
	gotoxy(40, 27);
	std::cout << "��Move : WSAD ��  Basic Attack : Left click ��  Extinction cannon : Right click ��" << std::endl;
	gotoxy(40, 28);
	std::cout << "����������������������������������������������������������������������������������" << std::endl;
	gotoxy(72, 35);
	std::cout << "   Click to start";
	gotoxy(72, 37);
	std::cout << "   Rank";
	gotoxy(72, 39);
	std::cout << "   Exit";

	int current_cursor = 1, before_cursor = 1;
	gotoxy(72, 35 + current_cursor * 2 - 2);
	std::cout << "��" << endl;
	while (1) {
		while (1) {
			if (onKey[KEY_UP] == true || onKey[KEY_DOWN] == true || onKey[13] == true) break;
		}
		if (onKey[KEY_UP]) {
			--current_cursor;
			if (current_cursor < 1) current_cursor = 1;
		}
		if (onKey[KEY_DOWN]) {
			++current_cursor;
			if (current_cursor > 3) current_cursor = 3;
		}
		if (onKey[13]) {
			if (current_cursor == 1) break;
			if (current_cursor == 2) {
				Screen->Draw_Clear();
				RankingScreen();
				LoadingScreen();
				break;
			}
			if (current_cursor == 3) exit(1);
		}
		if (before_cursor != current_cursor) {
			gotoxy(72, 35 + before_cursor * 2 - 2);
			std::cout << " " << endl;
			gotoxy(72, 35 + current_cursor * 2 - 2);
			std::cout << "��" << endl;
			before_cursor = current_cursor;
		}
		while (1) {
			if (onKey[KEY_UP] == false && onKey[KEY_DOWN] == false) break;
		}
	}	
}
void GameOverScreen() {



	int i;

	for (i = 54; i < 108; i += 2)
	{
		gotoxy(i, 10);
		printf("��");
		Sleep(30);
	}

	for (i = 106; i > 52; i -= 2)
	{
		gotoxy(i, 30);
		printf("��");
		Sleep(30);
	}

	Sleep(500);

	gotoxy(58, 15);
	std::cout << "������ᡡ�����ᡡ���ᡡ�����ᡡ������" << std::endl;
	gotoxy(58, 16);
	std::cout << "�ᡡ���������ᡡ�����ᡡ��ᡡ��ᡡ�ᡡ������" << std::endl;
	gotoxy(58, 17);
	std::cout << "�ᡡ����ᡡ�����ᡡ�ᡡ�ᡡ�ᡡ������" << std::endl;
	gotoxy(58, 18);
	std::cout << "�ᡡ�����ᡡ�ᡡ�����ᡡ�ᡡ�����ᡡ�ᡡ������" << std::endl;
	gotoxy(58, 19);
	std::cout << "������ᡡ�ᡡ�����ᡡ�ᡡ�����ᡡ������" << std::endl;
	gotoxy(58, 22);
	std::cout << "�����ᡡ���ᡡ�����ᡡ�����ᡡ����ᡡ" << std::endl;
	gotoxy(58, 23);
	std::cout << "�ᡡ�����ᡡ�ᡡ�����ᡡ�ᡡ���������ᡡ������" << std::endl;
	gotoxy(58, 24);
	std::cout << "�ᡡ�����ᡡ���ᡡ�ᡡ�������ᡡ����ᡡ" << std::endl;
	gotoxy(58, 25);
	std::cout << "�ᡡ�����ᡡ���ᡡ�ᡡ���ᡡ���������ᡡ������" << std::endl;
	gotoxy(58, 26);
	std::cout << "�����ᡡ�������ᡡ���������ᡡ�ᡡ������" << std::endl;
	gotoxy(58, 35);
	printf("                 %7d", score);
	gotoxy(58, 37);
	for (int i = 0; i < 10; i++) {
		if (myRank.GetRank(i) == score) {
			printf("                �� %d�� �޼� ��", i+1);
			break;
		}
	}
	Sleep(2000);
}
int main()
{
	// ������ �⺻ ������ �ʱ�ȭ �մϴ�.
	Init();

	// �Է��� �޴� �����带 ������ŵ�ϴ�.
	std::thread input_thread(Thread_input);

	// �ε� ��ũ�� ����!!
	LoadingScreen();
	Screen->Draw_Clear();

	// ������ �ð��� ��� �����Դϴ�.
	clock_t timer = clock();
	clock_t start, end;
	clock_t startTime = clock();	

	while (1) {
		while (bOnGame) {
			// ���͸� ����
			{
				const int regenTime = 20;
				static int regenCounter = 0;
				if (++regenCounter >= max(regenTime - score/200, 10)) {
					CEnemy* tmp = new CEnemy();
					Gameobjects.push_back(tmp);
					regenCounter = 0;
				}
				const int effectTime = 40;
				static int effectCounter = 0;
				if (++effectCounter >= effectTime) {
					score += 5;
					CEffect* tmp = new CEffect();
					Gameobjects.push_back(tmp);
					effectCounter = 0;
				}
			}

			// �ൿ
			{
				// ����Ʈ�� ����ִ� ��� Gameobjects���� Func�Լ��� �����ŵ�ϴ�.
				for (std::list<CGameObject*>::iterator i = Gameobjects.begin(); i != Gameobjects.end();) {
					(*i)->Func();
					if ((*i)->bDieFlag) {// ������ ������Ʈ�� ó���Ѵ�.
						try {
							delete (*i);
							i = Gameobjects.erase(i);
						}
						catch (int) {
							MessageBox(HWND_DESKTOP, TEXT("Func Error!!"), TEXT("Func���� ��ü�� �����ϴ� ����, ������ �߻��Ͽ����ϴ�."), MB_OK);
						}
					}
					else ++i;
				}
			}
			// ������
			{
				for (std::list<CGameObject*>::iterator i = Gameobjects.begin(); i != Gameobjects.end();) {
					(*i)->Move();
					if ((*i)->bDieFlag) {// ������ ������Ʈ�� ó���Ѵ�.
						try{
							delete (*i);
							i = Gameobjects.erase(i);
						}
						catch (int) {
							MessageBox(HWND_DESKTOP, TEXT("Move Error!!"), TEXT("Move���� ��ü�� �����ϴ� ����, ������ �߻��Ͽ����ϴ�."), MB_OK);
						}
					}
					else ++i;
				}
			}
			//�Ҹ�ź ����
			if (MainChar->ammo < 5) {
				static int deltaTime = 0;
				deltaTime++;
				if (deltaTime == 400) {
					MainChar->ammo++;
					deltaTime = 0;
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
								try{
									delete (*j);
									j = Gameobjects.erase(j);
								}
								catch (int) {
									MessageBox(HWND_DESKTOP, TEXT("Attack Error!!"), TEXT("Attck���� ��ü�� �����ϴ� ����, ������ �߻��Ͽ����ϴ�."), MB_OK);
								}
							}
							else ++j;

							if ((*i)->bDieFlag) {// ������ ������Ʈ�� ó���ϰ�, i���� �ٲ�Ƿ� �극��ũ��.
								try {
									delete (*i);
									i = Gameobjects.erase(i);
								}
								catch (int) {
									MessageBox(HWND_DESKTOP, TEXT("Func Error!!"), TEXT("Func���� ��ü�� �����ϴ� ����, ������ �߻��Ͽ����ϴ�."), MB_OK);
								}
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
				for (auto i : Gameobjects) if (i->var["isEffect"]) i->Draw();
				for (auto i : Gameobjects) if (!(i->var["isEffect"])) i->Draw();
				// ũ�ν���� �׸���
				{
					Screen->SetColor(EColor::CC_CYAN, EColor::CC_BLACK);
					Screen->Print(mouse_x, mouse_y - 1, "��", 2);
					Screen->Print(mouse_x - 1, mouse_y, "��", 2);
					Screen->Print(mouse_x + 1, mouse_y, "��", 2);
					Screen->Print(mouse_x, mouse_y + 1, "��", 2);
				}
				// �����ð� ǥ��
				Screen->SetColor(EColor::CC_WHITE);
				float delay = (clock() - startTime) / 1000;
				char str[256];
				sprintf(str, "����ð�:%2g ��", delay);
				Screen->Print(SCREEN_WIDTH - 13, 2, str);
				// ���ھ� ǥ��
				sprintf(str, "%d", score);
				Screen->Print(2, 2, str);
				//�Ҹ�ź ���� ǥ��
				Screen->SetColor(EColor::CC_YELLOW);
				Screen->Print(SCREEN_WIDTH - 13, 3, "�Ҹ�ź:");
				for (int i = 0; i < 5; i++)
				{
					if (i < MainChar->ammo)
						Screen->Print(SCREEN_WIDTH - 9 + i, 3, "��");
					else
						Screen->Print(SCREEN_WIDTH - 9 + i, 3, "  ");
				}
				Screen->Draw();
			}

			// ��� �������� �ð����� ����ȭ �����ֱ� ���� �۾�.
			{
				// ���� �ð��� ���� �������� �ð��� ���̸� ���մϴ�.
				deltaTime = ((float)(clock() - timer) / CLOCKS_PER_SEC);
				// �����Ӹ��� �׻� ���� �ð��� �� �� �ְ� Sleep�� �̴ϴ�.
				if (deltaTime * 1000 < 20) Sleep(20.0f - deltaTime * 1000);
				timer = clock();
			}
		}
		Screen->Draw_Clear();

		myRank.AddRank(score);
		GameOverScreen();
		Screen->Draw_Clear();
		LoadingScreen();
		InitGame();
		startTime = clock();
		Screen->Draw_Clear_Rect();
	}
	input_thread.detach();
	return 0;
}
void InitGame() {
	score = 0;
	for (auto i : Gameobjects) {
		if(i!=MainChar) delete i;
	}
	bOnGame = true;
	Gameobjects.clear();
	Screen->Clear();
	Gameobjects.push_front(MainChar);
	MainChar->Reset();
	MainChar->SetPosition(SCREEN_WIDTH / 2 - MainChar->GetW() / 2, SCREEN_HEIGHT / 2 - MainChar->GetH() / 2);
	for (int i = 0; i < 200; i++) onKey[i] = false;
}
void Init() {
	// â ������ ����
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	// �����츦 �������� ���ϵ���.
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE)&~WS_SIZEBOX);

	// ������ ��ġ �ʱ�ȭ
	SetWindowPos(console, 0, 100, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	
	// ������ ũ�� ����
	system("MODE CON COLS=160 LINES=51");

	// OnKey �ʱ�ȭ
	for (int i = 0; i < 200; i++) onKey[i] = false;

	// ���� ĳ���͸� GameObjects���ٰ� �ֽ��ϴ�.
	Gameobjects.push_front(MainChar);

	// ���� ĳ������ ��ġ�� ���� �մϴ�.
	MainChar->SetPosition(SCREEN_WIDTH/2 - MainChar->GetW()/2, SCREEN_HEIGHT/2 - MainChar->GetH()/2);

	// Ŀ���� ����ϴ�.
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = false;
	ConsoleCursor.dwSize = 1; // Ŀ��������
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor); // ����

	Screen->Draw_Clear();
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
		try {
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
		catch (char) {
			MessageBox(HWND_DESKTOP, TEXT("Thread Error!!"), TEXT("�����忡�� ������ �߻��߽��ϴ�."), MB_OK);
		};
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