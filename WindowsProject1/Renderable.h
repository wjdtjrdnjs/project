#pragma once
#include<functional>
#include<windows.h>

struct Renderable {
    float renderY; // ���� ����
    std::function<void(HDC)> drawFunc;
};