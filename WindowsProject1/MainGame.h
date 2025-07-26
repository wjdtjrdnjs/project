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
	void SetHWND(HWND hwnd_) { hwnd = hwnd_; }// ������ �ڵ� ���� �Լ�
	HWND  GetHWND() { return hwnd; }// ������ �ڵ� ���� �Լ�
	void Init();
	void Render(HDC hdc);
	void Update();
	void Run();
	void Input(UINT message, WPARAM wParam, LPARAM lParam);
private:
	HWND hwnd;  // ������ �ڵ� ����� ��� ����
	MSG msg;
	
};

