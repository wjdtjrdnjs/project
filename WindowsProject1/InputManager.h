#pragma once
#include <Windows.h>
//������

class InputManager
{
public:
    static void Init(HWND hwnd);
    static void Update(); // �� ������ ȣ��
    static bool IsMouseClicked();  // ���� Ŭ�� ����
    static POINT GetMousePosition(); // Ŭ�� ��ǥ ��������

private:
    static HWND hWnd;
    static bool mouseClicked;
    static POINT mousePos;
};
