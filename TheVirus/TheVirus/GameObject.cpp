#define _CRT_SECURE_NO_WARNINGS
#include"GameObject.h"
#include"externValue.h"
CGameObject::CGameObject() {
	bDieFlag = false;
	m_color = EColor::CC_WHITE;
	m_bkColor = EColor::CC_BLACK;
	m_x = 0;
	m_y = 0;
	m_w = 1;
	m_h = 1;
	strcpy(m_img, "¡Û");
}
CGameObject::CGameObject(float x, float y, char* img) : m_x(x), m_y(y) {
	bDieFlag = false;
	m_color = EColor::CC_WHITE;
	m_bkColor = EColor::CC_BLACK;
	m_w = 1;
	m_h = 1;
	m_img[0] = img[0];
	m_img[1] = img[1];
}
CGameObject::CGameObject(float x, float y, int w, int h, char* img) : m_x(x), m_y(y), m_w(w), m_h(h) {
	bDieFlag = false;
	m_color = EColor::CC_WHITE;
	m_bkColor = EColor::CC_BLACK;
	m_img[0] = img[0];
	m_img[1] = img[1];
}
CGameObject::CGameObject(float x, float y, int w, int h, char* img, EColor color) : m_x(x), m_y(y), m_w(w), m_h(h) {
	bDieFlag = false;
	m_color = color;
	m_bkColor = EColor::CC_BLACK;
	m_img[0] = img[0];
	m_img[1] = img[1];
}
void CGameObject::SetImg(char * img)
{
	m_img[0] = img[0];
	m_img[1] = img[1];
}
void CGameObject::SetW(int w) {
	m_w = w;
}
void CGameObject::SetH(int h) {
	m_h = h;
}
int CGameObject::GetW() {
	return m_w;
}
int CGameObject::GetH() {
	return m_h;
}
void CGameObject::SetWH(int w, int h)
{
	m_w = w;
	m_h = h;
}
void CGameObject::SetX(float x) {
	m_x = x;
}
void CGameObject::SetY(float y) {
	m_y = y;
}
void CGameObject::SetPosition(float x, float y) {
	SetX(x);
	SetY(y);
}
void CGameObject::PlusX(float x) {
	m_x += x;
}
void CGameObject::PlusY(float y) {
	m_y += y;
}
void CGameObject::PlusPosition(float x, float y) {
	PlusX(x);
	PlusY(y);
}
void CGameObject::Destory()
{
	bDieFlag = true;
}
void CGameObject::Draw()
{
	EColor oldColor = Screen->GetColor();
	EColor oldBkColor = Screen->GetBkColor();

	Screen->SetColor(m_color, m_bkColor);
	for (int i = 0; i < GetW(); i++) {
		for (int j = 0; j < GetH(); j++) {
			Screen->Print(GetX() + i, GetY() + j, m_img, 2);
		}
	}
	Screen->SetColor(oldColor, oldBkColor);
}
float CGameObject::GetX() const { return m_x; }
float CGameObject::GetY() const { return m_y; }