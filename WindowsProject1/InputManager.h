#pragma once
#include <Windows.h>
#include "SingletonT.h"



class InputManager : public SingletonT<InputManager>
{
public:
    void Init(HWND hwnd);
    void Update(); // �� ������ ȣ��

    // ���콺
    POINT GetMousePosition();        // ���콺 ��ǥ
    bool IsLeftClickUp();           // ��Ŭ�� ����
    bool IsLeftClickDown();
    bool IsLeftClickHeld();

    bool IsRightClickUp();           // ��Ŭ�� ����
    bool IsRightClickDown();
    bool IsRightClickHeld();

    // Ű����
    bool IsKeyHeld(int vKey);        // Ű�� ���� �ִ� ����
    bool IsKeyDown(int vKey);        // �̹� �����ӿ� ����
    bool IsKeyUp(int vKey);          // �̹� �����ӿ� ��

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

    // Ű ���� ����
    BYTE currentKeys[256] = { 0 };
    BYTE previousKeys[256] = { 0 };
};



