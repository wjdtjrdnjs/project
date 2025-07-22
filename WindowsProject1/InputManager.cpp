#include "InputManager.h"
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

int InputManager::GetPressedNumberKey()
{
    for (int i = 0; i < 9; ++i) {
        // VK_1 ~ VK_9 = 0x31 ~ 0x39
        if (GetAsyncKeyState(0x31 + i) & 0x8000) {
            return i + 1; // 1~9 ���� ��ȯ
        }
    }
    return 0; // �ƹ� �͵� �� �������� 0
}

bool InputManager::IsKeyPressedOnce(int key) {
    return (GetAsyncKeyState(key) & 0x0001); // �� �� �� ���� true
}

