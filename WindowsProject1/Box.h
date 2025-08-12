#pragma once
#include "WorldObject.h"
#include "InventoryItem.h"
#include <Windows.h>

//#define tileSize 32
class Player;
class Box: public WorldObject
{
public:
    Box();
    void Render(HDC hdc, int Tilesize) override;
    void SetTilePosition(int px, int py) override;
    PlaceableType GetPlaceableType() const override;
    RECT GetCollisionRect();

    void Open(); //����
    void Close(); //�ݱ�
    bool IsOpen() const;

    void RenderUI(HDC hdc);     // ���� ������ ĭ UI 

   

   bool HandleClick(int mouseX, int mouseY, int num);//���콺 ��Ŭ�� ���� Ȯ��(�ڽ� ĭ or �÷��̾� ����)
   void HandleItemSlotLClick(InventoryItem* slot);//���콺 ��Ŭ������ ���԰� ���� ��� �ִ� ������ ó�� �Լ�
   void HandleItemSlotRClick(InventoryItem* slot);

   void RenderSlot(HDC hdc, int left, int top, const InventoryItem& item);
   void RenderCursorItem(HDC hdc); //Ŭ���� �������� Ŀ���� �ٰ� �ϴ� �Լ�



    void AddItem(int slotIndex, const InventoryItem& item);
    InventoryItem* GetItems() { return items; }
    void SetPlayerToolbar(InventoryItem* toolbar);
    void OnInteract(Player* player);

private:
    int x, y;                  
    bool isOpen = false;
    int baseX = 360;
    int baseY = 150;
    bool playerNear = false;

    const int SLOT_ROWS = 3;
    const int SLOT_COLS = 9;
    const int SLOT_SIZE = 50;
    const int SLOT_MARGIN = 5;
    const int TOOLBAR_Y = 300;

    HBITMAP bmp;
    InventoryItem items[27];   // 3x9 �κ��丮 ����(�ӽ�)
    InventoryItem* playerToolbar;

    //InventoryItem heldItem;
    //HBITMAP hIconBitmap;
    //RECT iconRect;              // ������ ���� (3x9 Ÿ�� ũ��)
};

//public

// void HandleItemSlotRClick(InventoryItem* slot);//���콺 ��Ŭ������ ���԰� ���� ��� �ִ� ������ ó�� �Լ�

// std::vector<RECT>GetCollisionRects()const override;

// RECT GetBoundingBox() const; //���� �浹 ����(���� ������)
// 
// void SetPlayerNear(bool ch);
// bool IsPlayerNear() { return playerNear; }

    //std::vector<RECT> GetCollisionRects() const override;

      //void Interact(Player& player) override;

   // PlaceableType GetType() const override { return PlaceableType::Box;}
       // bool IsPlayerInRange(int playerX, int playerY); //�÷��̾ �ڽ� �ֺ��� �ִ� �� Ȯ��
   // bool IsMouseOverIcon(int mouseX, int mouseY);//���콺 Ŀ���� ���ھ����� ���� �ִ��� Ȯ��
    //Box(int x, int y);