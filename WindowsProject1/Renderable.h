#pragma once
#include<functional>
#include<windows.h>

struct Renderable {
    float renderY; // 정렬 기준
    std::function<void(HDC)> drawFunc;
};