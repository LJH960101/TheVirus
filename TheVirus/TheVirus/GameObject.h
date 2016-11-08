// ȭ�鿡 �����ϴ� ���ӿ�����Ʈ�� �����ϴ� Ŭ�����Դϴ�.

#pragma once
#include"Screen.h"
#include<map>
class CGameObject {
private:
	// ��ǥ���� ���� �����Դϴ�.
	float m_x, m_y;
	// �ʺ�,���� ���� ���� �����Դϴ�.
	int m_w, m_h;
public:
	// �Ҹ��� ��Ÿ���� �÷��� �Դϴ�.
	bool bDieFlag;
	// ���ڻ��� ������ ��� �����Դϴ�.
	EColor m_color, m_bkColor;
	// ����� �̹����� ��� ���� �Դϴ�.
	char m_img[2];
	// ���� ���� ���� �� �ִ� ��Ÿ���� �����Դϴ�.
	// obj.var["Ű��"] = ����;
	// �̷������� �迭�� Index�� ���ڿ��� �Ἥ ���� ���� �� �ֽ��ϴ�.
	// Ex.) obj.var["Speed"] = 5; -> ������Ʈ�� var������ Speed�� 5�� �����Ѵ�.
	std::map<char*, int> var;

	CGameObject();
	CGameObject(float x, float y, char* img);
	CGameObject(float x, float y, int w, int h, char* img);
	CGameObject(float x, float y, int w, int h, char* img, EColor color);
	virtual ~CGameObject() {};
	
	// ������Ʈ�� �����մϴ�.
	void Destory();

	// ������Ʈ�� �׷��ݴϴ�.
	virtual void Draw();
	// ������Ʈ�� ������ �ݴϴ�.
	virtual void Move() {};
	// ������Ʈ�� �̺�Ʈ�� ����ϴ�.
	virtual void Func() {};
	// ������Ʈ�� �浹������, ����Ǵ� �Լ��Դϴ�.
	virtual void IsAttack(CGameObject* obj) {};

	// ���ϴ� Getter�� Setter�� Setter�� ������ �Դϴ�.
	void SetImg(char* img);

	void SetW(int w);
	void SetH(int h);
	int GetW();
	int GetH();
	void SetWH(int w, int h);

	void SetX(float x);
	void SetY(float y);
	void SetPosition(float x, float y);
	void PlusX(float x);
	void PlusY(float y);
	float GetX() const;
	float GetY() const;

	void PlusPosition(float x, float y);
	//////////////////
};