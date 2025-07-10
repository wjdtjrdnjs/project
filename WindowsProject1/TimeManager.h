#pragma once
#include <windows.h>
//진행중
class TimeManager
{
private:
    static LARGE_INTEGER frequency;   // 타이머 주기
    static LARGE_INTEGER lastTime;    // 이전 프레임 시간
    static float deltaTime;           // 프레임 간 시간 차이 (초)
    static float totalTime;           // 프로그램 시작 이후 누적 시간 (초)

public:
    static void Init();               // 초기화 (1회만)
    static void Update();             // 매 프레임 호출
    static float GetDeltaTime();      // deltaTime 반환
    static float GetTotalTime();      // 전체 경과 시간 반환
};
