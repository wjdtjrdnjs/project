#pragma once

#include <Windows.h>
#include "Player.h"
#include "Map.h"



class Box {
public:
    Box(int x, int y);
    void Render(HDC hdc);       // ���� ������ �׸���
    void RenderUI(HDC hdc);     // ���� ������ ĭ UI 
    bool IsPlayerInRange(int playerX, int playerY); //�÷��̾ �ڽ� �ֺ��� �ִ� �� Ȯ��
    bool IsMouseOverIcon(int mouseX, int mouseY);//���콺 Ŀ���� ���ھ����� ���� �ִ��� Ȯ��
    void Open(); //����
    void Close(); //�ݱ�
    bool IsOpen() const;

    InventoryItem* GetItems();

private:
    int x, y;                  
    bool isOpen = false;
    InventoryItem items[27];    // 3x9 �κ��丮 ����(�ӽ�)
    HBITMAP hIconBitmap;
    RECT iconRect;              // ������ ���� (3x3 Ÿ�� ũ��)
};
