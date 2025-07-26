#pragma once
#include "WorldObject.h"
#include <Windows.h>

//#define tileSize 32

class Box: public WorldObject
{
public:
    Box();
    void Render(HDC hdc, int Tilesize) override;
    void SetTilePosition(int px, int py) override;
    ObjectType GetObjectType() const override;
   // ObjectType GetType() const override { return ObjectType::Box;}

    //Box(int x, int y);
   // void RenderUI(HDC hdc);     // ���� ������ ĭ UI 
   // bool IsPlayerInRange(int playerX, int playerY); //�÷��̾ �ڽ� �ֺ��� �ִ� �� Ȯ��
   // bool IsMouseOverIcon(int mouseX, int mouseY);//���콺 Ŀ���� ���ھ����� ���� �ִ��� Ȯ��
   // void Open(); //����
   // void Close(); //�ݱ�
   // bool IsOpen() const;
   // void HandleClick(int row, int col, int num); //���콺 ��Ŭ�� ���� Ȯ��(�ڽ� ĭ or �÷��̾� ����)
   // void RenderCursorItem(HDC hdc); //Ŭ���� �������� Ŀ���� �ٰ� �ϴ� �Լ�

   // void HandleItemSlotLClick(InventoryItem* slot);//���콺 ��Ŭ������ ���԰� ���� ��� �ִ� ������ ó�� �Լ�
   // void HandleItemSlotRClick(InventoryItem* slot);//���콺 ��Ŭ������ ���԰� ���� ��� �ִ� ������ ó�� �Լ�

   // std::vector<RECT>GetCollisionRects()const override;

   // RECT GetBoundingBox() const; //���� �浹 ����(���� ������)
   //// InventoryItem* GetItems();
   // void SetPlayerToolbar(InventoryItem* toolbar);
   // 
   // void SetPlayerNear(bool ch);
   // bool IsPlayerNear() { return playerNear; }
       
private:
    int x, y;                  
    bool isOpen = false;
    bool playerNear = false;
    HBITMAP bmp;
    //InventoryItem* playerToolbar[9];
    //InventoryItem items[3][9];    // 3x9 �κ��丮 ����(�ӽ�)
    //InventoryItem heldItem;
    //HBITMAP hIconBitmap;
    //RECT iconRect;              // ������ ���� (3x9 Ÿ�� ũ��)
};
