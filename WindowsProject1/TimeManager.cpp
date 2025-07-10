#include "TimeManager.h"
//ม๘วเม฿

LARGE_INTEGER TimeManager::frequency = { 0 };
LARGE_INTEGER TimeManager::lastTime = { 0 };
float TimeManager::deltaTime = 0.0f;
float TimeManager::totalTime = 0.0f;

void TimeManager::Init()
{
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&lastTime);
}

void TimeManager::Update()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);

    LONGLONG elapsed = currentTime.QuadPart - lastTime.QuadPart;
    deltaTime = static_cast<float>(elapsed) / frequency.QuadPart;
    totalTime += deltaTime;

    lastTime = currentTime;
}

float TimeManager::GetDeltaTime()
{
    return deltaTime;
}

float TimeManager::GetTotalTime()
{
    return totalTime;
}
