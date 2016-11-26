#define _CRT_SECURE_NO_WARNINGS
#include"Screen.h"
#include<time.h>

CScreen::CScreen() {
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			m_map[i][j][0] = ' ';
			m_map[i][j][1] = ' ';
			m_map[i][j][2] = NULL;
			m_before_map[i][j][0] = ' ';
			m_before_map[i][j][1] = ' ';
			m_before_map[i][j][2] = NULL;
			m_map_color[i][j][0] = EColor::CC_WHITE;
			m_map_color[i][j][1] = EColor::CC_BLACK;
			m_before_map_color[i][j][0] = EColor::CC_WHITE;
			m_before_map_color[i][j][1] = EColor::CC_BLACK;
		}
	}
}

//텍스트, 배경색 모두 변경 함수
void CScreen::setColor(int color, int bgcolor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | (color & 0xf));
}

//텍스트 색상 변경 함수
void CScreen::setFontColor(int color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (info.wAttributes & 0xf0) | (color & 0xf));
}

//배경 색상 변경 함수
void CScreen::setBgColor(int bgcolor) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | (info.wAttributes & 0xf));
}
void CScreen::SetColor(EColor color, EColor bkColor)
{
	m_color = color;
	m_bkcolor = bkColor;
}
void CScreen::SetColor(EColor color)
{
	m_color = color;
}
void CScreen::SetBKColor(EColor bkColor)
{
	m_bkcolor = bkColor;
}
EColor CScreen::GetColor()
{
	return m_color;
}
EColor CScreen::GetBkColor()
{
	return m_bkcolor;
}
void CScreen::gotoxy(int x, int y)
{
	x = x * 2;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}
// 화면에 출력할 정보를 모두 지워줍니다. 
void CScreen::Clear() {
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			if (i == 0 || j == 0 || i == SCREEN_WIDTH-1 || j == SCREEN_HEIGHT-1) {
				strcpy(m_map[i][j], "▩");
				m_map[i][j][2] = '\0';
				m_map_color[i][j][0] = EColor::CC_BLACK;
				m_map_color[i][j][1] = EColor::CC_WHITE;
			}
			else {
				m_map[i][j][0] = ' ';
				m_map[i][j][1] = ' ';
				m_map_color[i][j][0] = EColor::CC_WHITE;
				m_map_color[i][j][1] = EColor::CC_BLACK;
			}
		}
	}
}
// 화면에 출력할 정보를 저장합니다. 
void CScreen::Print(int x, int y, char* str, int len) {
	if (len == 0) len = strlen(str);
	for (int i = 1; i <= len; i += 2) {
		if (x + i / 2 >= SCREEN_WIDTH-1 || y >= SCREEN_HEIGHT-1 || x + i / 2 <= 0 || y <= 0) continue;
		m_map[x + i / 2][y][0] = str[0 + i - 1];
		m_map[x + i / 2][y][1] = str[1 + i - 1];

		m_map_color[x + i / 2][y][0] = m_color;
		m_map_color[x + i / 2][y][1] = m_bkcolor;
	}
}
// 화면을 다시 그려줍니다. 
void CScreen::Draw() {
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			if (!(m_map[i][j][0] == m_before_map[i][j][0] && m_map[i][j][1] == m_before_map[i][j][1] && m_map_color[i][j][0]==m_before_map_color[i][j][0] && m_map_color[i][j][1] == m_before_map_color[i][j][1])) {
				setColor(m_map_color[i][j][0], m_map_color[i][j][1]);
				gotoxy(i, j);
				printf("%s", m_map[i][j]);
				m_before_map[i][j][0] = m_map[i][j][0];
				m_before_map[i][j][1] = m_map[i][j][1];
				m_before_map_color[i][j][0] = m_map_color[i][j][0];
				m_before_map_color[i][j][1] = m_map_color[i][j][1];
			}
		}
	}
	gotoxy(0, 0);
}

void CScreen::Draw_Clear()
{
	SetColor(EColor::CC_WHITE, EColor::CC_BLACK);
	setColor(m_color, m_bkcolor);
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			gotoxy(i, j);
			printf("%s", "  ");
		}
	}
}
void CScreen::Draw_Clear_Rect()
{
	this->Draw_Clear();


	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			m_map[i][j][0] = ' ';
			m_map[i][j][1] = ' ';
			m_map[i][j][2] = NULL;
			m_before_map[i][j][0] = ' ';
			m_before_map[i][j][1] = ' ';
			m_before_map[i][j][2] = NULL;
			m_map_color[i][j][0] = EColor::CC_WHITE;
			m_map_color[i][j][1] = EColor::CC_BLACK;
			m_before_map_color[i][j][0] = EColor::CC_WHITE;
			m_before_map_color[i][j][1] = EColor::CC_BLACK;
		}
	}

	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			if (i == 0 || j == 0 || i == SCREEN_WIDTH - 1 || j == SCREEN_HEIGHT - 1) {
				strcpy(m_map[i][j], "▩");
				m_map[i][j][2] = '\0';
				m_map_color[i][j][0] = EColor::CC_BLACK;
				m_map_color[i][j][1] = EColor::CC_WHITE;
			}
			else {
				m_map[i][j][0] = ' ';
				m_map[i][j][1] = ' ';
				m_map_color[i][j][0] = EColor::CC_WHITE;
				m_map_color[i][j][1] = EColor::CC_BLACK;
			}
		}
	}
	this->Draw();
}


