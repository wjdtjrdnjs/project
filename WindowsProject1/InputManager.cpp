#include "InputManager.h"

HWND InputManager::hWnd = nullptr;

bool InputManager::mouseClicked = false;
bool InputManager::mouseClickedPrev = false;

bool InputManager::currentLeftClick = false;
bool InputManager::previousLeftClick = false;
bool InputManager::currentRightClick = false;
bool InputManager::previousRightClick = false;

POINT InputManager::mousePos = { 0, 0 };

BYTE InputManager::currentKeys[256] = { 0 };
BYTE InputManager::previousKeys[256] = { 0 };

void InputManager::Init(HWND hwnd)
{
    hWnd = hwnd;
    (void)GetKeyboardState(currentKeys);  //���� �ʿ�
}

void InputManager::Update()
{
    // ���콺 ��ġ
    GetCursorPos(&mousePos);
    ScreenToClient(hWnd, &mousePos);

    // ���� Ŭ�� ���� ����
    previousLeftClick = currentLeftClick;
    previousRightClick = currentRightClick;

    // ���� Ŭ�� ���� ����
    currentLeftClick = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    currentRightClick = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;

    // Ű����
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

bool InputManager::IsRightClickUp()
{
    return !currentRightClick && previousLeftClick;
}

bool InputManager::IsRightClickDown()
{
    return currentRightClick && !previousLeftClick;
}

bool InputManager::IsRightClickHeld()
{
    return currentRightClick;
}

bool InputManager::IsLeftClickUp()
{
    return !currentLeftClick && previousLeftClick;
}

POINT InputManager::GetMousePosition()  //Ŭ���� ��ǥ
{
    return mousePos; 
}

// Ű�� ��� ���� �ִ� ��������
bool InputManager::IsKeyHeld(int vKey)
{
    return (currentKeys[vKey] & 0x80) != 0;
}

// �̹� �����ӿ� ���� ���
bool InputManager::IsKeyDown(int vKey)
{
    return ((currentKeys[vKey] & 0x80) != 0) &&
        ((previousKeys[vKey] & 0x80) == 0);
}

// �̹� �����ӿ� ������ ���
bool InputManager::IsKeyUp(int vKey)
{
    return ((currentKeys[vKey] & 0x80) == 0) &&
        ((previousKeys[vKey] & 0x80) != 0);
}
