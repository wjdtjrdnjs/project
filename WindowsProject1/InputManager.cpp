#include "InputManager.h"
#include "Gigagenie.h"
#include "Direction.h"


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
    POINT p;
    GetCursorPos(&p);               // 화면 좌표로 마우스 위치 받기
    ScreenToClient(hWnd, &p);      // hwnd는 게임 윈도우 핸들, 클라이언트 좌표로 변환
    return p;
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

int InputManager::GetPressedNumberKey()
{
    for (int i = 0; i < 9; ++i) {
        // VK_1 ~ VK_9 = 0x31 ~ 0x39
        if (GetAsyncKeyState(0x31 + i) & 0x8000) {
            return i + 1; // 1~9 숫자 반환
        }
    }
    return 0; // 아무 것도 안 눌렸으면 0
}

bool InputManager::IsKeyPressed(int vKey)
{
    // 현재 키 상태가 눌린 상태면 true, 아니면 false
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
        return -1; // 아래로 내림
    }
    else if (wheelDelta <= -120) {
        wheelDelta = 0;
        return 1; // 위로 올림
    }
    return 0; // 변화 없음
}


bool InputManager::IsKeyPressedOnce(int key) {
    return (GetAsyncKeyState(key) & 0x0001); // ← 딱 한 번만 true
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