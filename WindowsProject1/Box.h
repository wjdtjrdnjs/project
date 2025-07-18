#pragma once
#include <Windows.h>
#include "Map.h"
#include "Player.h"


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
    void HandleClick(int row, int col, int num); //���콺 ��Ŭ�� ���� Ȯ��(�ڽ� ĭ or �÷��̾� ����)
    void RenderCursorItem(HDC hdc); //Ŭ���� �������� Ŀ���� �ٰ� �ϴ� �Լ�
    void HandleItemSlotLClick(InventoryItem& slot);//���콺 ��Ŭ������ ���԰� ���� ��� �ִ� ������ ó�� �Լ�
    void HandleItemSlotRClick(InventoryItem& slot);//���콺 ��Ŭ������ ���԰� ���� ��� �ִ� ������ ó�� �Լ�

   // InventoryItem* GetItems();
    void SetPlayerToolbar(InventoryItem* toolbar) {
        playerToolbar = toolbar;
    }
private:
    int x, y;                  
    bool isOpen = false;
    InventoryItem* playerToolbar = nullptr;
    InventoryItem items[3][9];    // 3x9 �κ��丮 ����(�ӽ�)
    InventoryItem heldItem;
    HBITMAP hIconBitmap;
    RECT iconRect;              // ������ ���� (3x9 Ÿ�� ũ��)
};
