#pragma once
#include <Windows.h>

class InputManager
{
public:
    static void Init(HWND hwnd);
    static void Update(); // 매 프레임 호출

    // 마우스
    static POINT GetMousePosition();        // 마우스 좌표
    static bool IsLeftClickUp();           // 좌클릭 감지
    static bool IsLeftClickDown();
    static bool IsLeftClickHeld();

    static bool IsRightClickUp();           // 우클릭 감지
    static bool IsRightClickDown();
    static bool IsRightClickHeld();

    // 키보드
    static bool IsKeyHeld(int vKey);        // 키가 눌려 있는 상태
    static bool IsKeyDown(int vKey);        // 이번 프레임에 눌림
    static bool IsKeyUp(int vKey);          // 이번 프레임에 뗌

private:
    static HWND hWnd;
    static POINT mousePos;

    static bool mouseClicked;
    static bool mouseClickedPrev;


    static bool currentLeftClick;
    static bool previousLeftClick;
    static bool currentRightClick;
    static bool previousRightClick;

    // 키 상태 추적
    static BYTE currentKeys[256];
    static BYTE previousKeys[256];
};
