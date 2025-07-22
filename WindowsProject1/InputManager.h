#pragma once
#include <Windows.h>
#include "SingletonT.h"



class InputManager : public SingletonT<InputManager>
{
public:
    void Init(HWND hwnd);
    void Update(); // 매 프레임 호출

    // 마우스
    POINT GetMousePosition();        // 마우스 좌표
    bool IsLeftClickUp();           // 좌클릭 감지
    bool IsLeftClickDown();
    bool IsLeftClickHeld();

    bool IsRightClickUp();           // 우클릭 감지
    bool IsRightClickDown();
    bool IsRightClickHeld();

    // 키보드
    bool IsKeyHeld(int vKey);        // 키가 눌려 있는 상태
    bool IsKeyDown(int vKey);        // 이번 프레임에 눌림
    bool IsKeyUp(int vKey);          // 이번 프레임에 뗌

    bool IsKeyPressedOnce(int key);
    int GetPressedNumberKey();
private:
    HWND hWnd = nullptr;
    POINT mousePos{ 0, 0 };

    bool mouseClicked = false;
    bool mouseClickedPrev = false;

    bool currentLeftClick = false;
    bool previousLeftClick = false;
    bool currentRightClick = false;
    bool previousRightClick = false;

    // 키 상태 추적
    BYTE currentKeys[256] = { 0 };
    BYTE previousKeys[256] = { 0 };
};



