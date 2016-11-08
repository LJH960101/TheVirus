// 화면의 출력을 담당하는 헤더입니다.
// 싱글톤으로, CScreen->GetInstance()로 객체를 받아와서,
// Print를 이용하여 출력하시면 됩니다.

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
	//텍스트, 배경색 모두 변경 함수
	void setColor(int color, int bgcolor);
	//텍스트 색상 변경 함수
	void setFontColor(int color);
	//배경 색상 변경 함수
	void setBgColor(int bgcolor);
public:
	static CScreen* CScreen::GetInstance() {
		static CScreen instance;
		return &instance;
	}

	// 글꼴색과 배경색을 바꾸어 줍니다.
	void SetColor(EColor color, EColor bkColor);
	// 글꼴색을 바꾸어 줍니다.
	void SetColor(EColor color);
	// 배경색을 바꾸어 줍니다.
	void SetBKColor(EColor bkColor);
	// 글꼴색을 리턴합니다.
	EColor GetColor();
	// 배경색을 리턴합니다.
	EColor GetBkColor();
	// 커서를 움직여 줍니다.
	void gotoxy(int x, int y);
	// 화면에 출력할 정보를 모두 지워줍니다. 
	void Clear();
	// 화면에 출력할 정보를 저장합니다. 
	void Print(int x, int y, char* str, int len = 0);
	// 화면을 다시 그려줍니다. 
	void Draw();
};