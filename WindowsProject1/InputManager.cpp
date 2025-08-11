#include "InputManager.h"
#include "Gigagenie.h"
#include "Direction.h"


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
    POINT p;
    GetCursorPos(&p);               // ȭ�� ��ǥ�� ���콺 ��ġ �ޱ�
    ScreenToClient(hWnd, &p);      // hwnd�� ���� ������ �ڵ�, Ŭ���̾�Ʈ ��ǥ�� ��ȯ
    return p;
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

bool InputManager::IsKeyPressed(int vKey)
{
    // ���� Ű ���°� ���� ���¸� true, �ƴϸ� false
    return (currentKeys[vKey] & 0x80) != 0;
}

void InputManager::ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_MOUSEWHEEL:
        wheelDelta += GET_WHEEL_DELTA_WPARAM(wParam);
        break;

    }
}


int InputManager::GetWheelDirection()
{
    if (wheelDelta >= 120) {
        wheelDelta = 0;
        return -1; // �Ʒ��� ����
    }
    else if (wheelDelta <= -120) {
        wheelDelta = 0;
        return 1; // ���� �ø�
    }
    return 0; // ��ȭ ����
}


bool InputManager::IsKeyPressedOnce(int key) {
    return (GetAsyncKeyState(key) & 0x0001); // �� �� �� ���� true
}

//void InputManager::HandleKey(WPARAM key)
//{
//    
//    switch (key) {
//    case VK_LEFT:
//        genie->MovePlayer(Direction::LEFT);
//        break;
//    case VK_RIGHT:
//        genie->MovePlayer(Direction::RIGHT);
//        break;
//    case VK_UP:
//        genie->MovePlayer(Direction::UP);
//        break;
//    case VK_DOWN:
//        genie->MovePlayer(Direction::DOWN);
//        break;
//    default:
//        break;
//    }
//}