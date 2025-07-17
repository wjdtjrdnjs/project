#pragma once
#include <Windows.h>

class InputManager
{
public:
    static void Init(HWND hwnd);
    static void Update(); // �� ������ ȣ��

    // ���콺
    static POINT GetMousePosition();        // ���콺 ��ǥ
    static bool IsLeftClickUp();           // ��Ŭ�� ����
    static bool IsLeftClickDown();
    static bool IsLeftClickHeld();

    static bool IsRightClickUp();           // ��Ŭ�� ����
    static bool IsRightClickDown();
    static bool IsRightClickHeld();

    // Ű����
    static bool IsKeyHeld(int vKey);        // Ű�� ���� �ִ� ����
    static bool IsKeyDown(int vKey);        // �̹� �����ӿ� ����
    static bool IsKeyUp(int vKey);          // �̹� �����ӿ� ��

private:
    static HWND hWnd;
    static POINT mousePos;

    static bool mouseClicked;
    static bool mouseClickedPrev;


    static bool currentLeftClick;
    static bool previousLeftClick;
    static bool currentRightClick;
    static bool previousRightClick;

    // Ű ���� ����
    static BYTE currentKeys[256];
    static BYTE previousKeys[256];
};
