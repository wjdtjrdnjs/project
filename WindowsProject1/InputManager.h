#pragma once
#include <Windows.h>
//진행중

class InputManager
{
public:
    static void Init(HWND hwnd);
    static void Update(); // 매 프레임 호출
    static bool IsMouseClicked();  // 왼쪽 클릭 감지
    static POINT GetMousePosition(); // 클릭 좌표 가져오기

private:
    static HWND hWnd;
    static bool mouseClicked;
    static POINT mousePos;
};
