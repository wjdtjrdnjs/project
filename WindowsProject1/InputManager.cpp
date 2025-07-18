#include "InputManager.h"
void InputManager::Init(HWND hwnd)
{
    hWnd = hwnd;
    (void)GetKeyboardState(currentKeys);  //조사 필요
}

void InputManager::Update()
{
    // 마우스 위치
    GetCursorPos(&mousePos);
    ScreenToClient(hWnd, &mousePos);

    // 이전 클릭 상태 저장
    previousLeftClick = currentLeftClick;
    previousRightClick = currentRightClick;

    // 현재 클릭 상태 감지
    currentLeftClick = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    currentRightClick = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;

    // 키보드
    memcpy(previousKeys, currentKeys, 256);
    (void)GetKeyboardState(currentKeys);
}

bool InputManager::IsLeftClickDown()
{
    return currentLeftClick && !previousLeftClick;
}

bool InputManager::IsLeftClickHeld()
{
    return currentLeftClick;
}


bool InputManager::IsLeftClickUp()
{
    return !currentLeftClick; // && previousLeftClick;
}


bool InputManager::IsRightClickUp()
{
    return !currentRightClick &&  previousRightClick;
    ;
}

bool InputManager::IsRightClickDown()
{
    return currentRightClick && !previousRightClick;
}

bool InputManager::IsRightClickHeld()
{
    return currentRightClick;
}


POINT InputManager::GetMousePosition()  //클릭한 좌표
{
    return mousePos; 
}

// 키가 계속 눌려 있는 상태인지
bool InputManager::IsKeyHeld(int vKey)
{
    return (currentKeys[vKey] & 0x80) != 0;
}

// 이번 프레임에 눌린 경우
bool InputManager::IsKeyDown(int vKey)
{
    return ((currentKeys[vKey] & 0x80) != 0) &&
        ((previousKeys[vKey] & 0x80) == 0);
}

// 이번 프레임에 떼어진 경우
bool InputManager::IsKeyUp(int vKey)
{
    return ((currentKeys[vKey] & 0x80) == 0) &&
        ((previousKeys[vKey] & 0x80) != 0);
}
