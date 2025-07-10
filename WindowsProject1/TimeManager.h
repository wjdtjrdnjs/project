#pragma once
#include <windows.h>
//������
class TimeManager
{
private:
    static LARGE_INTEGER frequency;   // Ÿ�̸� �ֱ�
    static LARGE_INTEGER lastTime;    // ���� ������ �ð�
    static float deltaTime;           // ������ �� �ð� ���� (��)
    static float totalTime;           // ���α׷� ���� ���� ���� �ð� (��)

public:
    static void Init();               // �ʱ�ȭ (1ȸ��)
    static void Update();             // �� ������ ȣ��
    static float GetDeltaTime();      // deltaTime ��ȯ
    static float GetTotalTime();      // ��ü ��� �ð� ��ȯ
};
