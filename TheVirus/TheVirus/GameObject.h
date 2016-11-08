// 화면에 존재하는 게임오브젝트를 구성하는 클래스입니다.

#pragma once
#include"Screen.h"
#include<map>
class CGameObject {
private:
	// 좌표값을 갖는 변수입니다.
	float m_x, m_y;
	// 너비,높이 값을 갖는 변수입니다.
	int m_w, m_h;
public:
	// 소멸을 나타내는 플래그 입니다.
	bool bDieFlag;
	// 글자색과 배경색을 담는 변수입니다.
	EColor m_color, m_bkColor;
	// 출력할 이미지를 담는 변수 입니다.
	char m_img[2];
	// 여러 값을 담을 수 있는 맵타입의 변수입니다.
	// obj.var["키값"] = 숫자;
	// 이런식으로 배열의 Index를 문자열로 써서 값을 구할 수 있습니다.
	// Ex.) obj.var["Speed"] = 5; -> 오브젝트의 var변수의 Speed에 5를 대입한다.
	std::map<char*, int> var;

	CGameObject();
	CGameObject(float x, float y, char* img);
	CGameObject(float x, float y, int w, int h, char* img);
	CGameObject(float x, float y, int w, int h, char* img, EColor color);
	virtual ~CGameObject() {};
	
	// 오브젝트를 삭제합니다.
	void Destory();

	// 오브젝트를 그려줍니다.
	virtual void Draw();
	// 오브젝트를 움직여 줍니다.
	virtual void Move() {};
	// 오브젝트의 이벤트를 담습니다.
	virtual void Func() {};
	// 오브젝트가 충돌했을때, 실행되는 함수입니다.
	virtual void IsAttack(CGameObject* obj) {};

	// 이하는 Getter와 Setter와 Setter의 변형형 입니다.
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