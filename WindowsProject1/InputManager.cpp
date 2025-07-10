#include "InputManager.h"
//진행중


HWND InputManager::hWnd = nullptr;
bool InputManager::mouseClicked = false;
POINT InputManager::mousePos = { 0, 0 };

void InputManager::Init(HWND hwnd)
{
    hWnd = hwnd;
}

void InputManager::Update()
{
    // 왼쪽 마우스 클릭 감지
    SHORT state = GetAsyncKeyState(VK_LBUTTON);
    if ((state & 0x8000)) {
        // 현재 마우스 위치 저장
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
