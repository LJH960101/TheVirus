// ȭ���� ����� ����ϴ� ����Դϴ�.
// �̱�������, CScreen->GetInstance()�� ��ü�� �޾ƿͼ�,
// Print�� �̿��Ͽ� ����Ͻø� �˴ϴ�.

#pragma once
#include <windows.h>
#include <stdio.h>

#define SCREEN_WIDTH 80 
#define SCREEN_HEIGHT 50

enum EColor {
	CC_BLACK,
	CC_DARKBLUE,
	CC_DARKGREEN,
	CC_DARKCYAN,
	CC_DARKRED,
	CC_DARKMAGENTA,
	CC_DARKYELLOW,
	CC_GRAY,
	CC_DARKGRAY,
	CC_BLUE,
	CC_GREEN,
	CC_CYAN,
	CC_RED,
	CC_MAGENTA,
	CC_YELLOW,
	CC_WHITE,
	CC_LIGHTGRAY = 7,
	CC_ORIGINAL = 7,
	CC_ORIGINALFONT = 7,
	CC_ORIGINALBG = 0
};

class CScreen {
private:
	char m_map[SCREEN_WIDTH][SCREEN_HEIGHT][3];
	char m_before_map[SCREEN_WIDTH][SCREEN_HEIGHT][3];
	EColor m_map_color[SCREEN_WIDTH][SCREEN_HEIGHT][2];
	EColor m_before_map_color[SCREEN_WIDTH][SCREEN_HEIGHT][2];
	EColor m_bkcolor;
	EColor m_color;

	CScreen();
	//�ؽ�Ʈ, ���� ��� ���� �Լ�
	void setColor(int color, int bgcolor);
	//�ؽ�Ʈ ���� ���� �Լ�
	void setFontColor(int color);
	//��� ���� ���� �Լ�
	void setBgColor(int bgcolor);
public:
	static CScreen* CScreen::GetInstance() {
		static CScreen instance;
		return &instance;
	}

	// �۲û��� ������ �ٲپ� �ݴϴ�.
	void SetColor(EColor color, EColor bkColor);
	// �۲û��� �ٲپ� �ݴϴ�.
	void SetColor(EColor color);
	// ������ �ٲپ� �ݴϴ�.
	void SetBKColor(EColor bkColor);
	// �۲û��� �����մϴ�.
	EColor GetColor();
	// ������ �����մϴ�.
	EColor GetBkColor();
	// Ŀ���� ������ �ݴϴ�.
	void gotoxy(int x, int y);
	// ȭ�鿡 ����� ������ ��� �����ݴϴ�. 
	void Clear();
	// ȭ�鿡 ����� ������ �����մϴ�. 
	void Print(int x, int y, char* str, int len = 0);
	// ȭ���� �ٽ� �׷��ݴϴ�. 
	void Draw();
};