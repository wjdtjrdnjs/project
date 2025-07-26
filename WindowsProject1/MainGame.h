#pragma once
#include <memory>
#include <windows.h>

class Gigagenie;
class MainGame
{
public:
	MainGame();
	~MainGame();
	std::unique_ptr<Gigagenie> genie;
	void SetHWND(HWND hwnd_) { hwnd = hwnd_; }// 윈도우 핸들 설정 함수
	HWND  GetHWND() { return hwnd; }// 윈도우 핸들 설정 함수
	void Init();
	void Render(HDC hdc);
	void Update();
	void Run();
	void Input(UINT message, WPARAM wParam, LPARAM lParam);
private:
	HWND hwnd;  // 윈도우 핸들 저장용 멤버 변수
	MSG msg;
	
};

