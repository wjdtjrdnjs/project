#include "InputManager.h"
//������


HWND InputManager::hWnd = nullptr;
bool InputManager::mouseClicked = false;
POINT InputManager::mousePos = { 0, 0 };

void InputManager::Init(HWND hwnd)
{
    hWnd = hwnd;
}

void InputManager::Update()
{
    // ���� ���콺 Ŭ�� ����
    SHORT state = GetAsyncKeyState(VK_LBUTTON);
    if ((state & 0x8000)) {
        // ���� ���콺 ��ġ ����
        GetCursorPos(&mousePos);
        ScreenToClient(hWnd, &mousePos);

        mouseClicked = true;
    }
    else {
        mouseClicked = false;
    }
}

bool InputManager::IsMouseClicked()
{
    return mouseClicked;
}

POINT InputManager::GetMousePosition()
{
    return mousePos;
}
