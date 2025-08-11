//#pragma once
//#include "WorldObject.h"
//#include "InventoryItem.h"
//#include <Windows.h>
//
////#define tileSize 32
//class Player;
//class NPC : public WorldObject
//{
//public:
//    NPC();
//    void Render(HDC hdc, int tileSize) override;
//    void SetTilePosition(int px, int py) override;
//    PlaceableType GetPlaceableType() const override;
//    RECT GetCollisionRect();
//
//    void Open();
//    void Close();
//    bool IsOpen() const;
//
//    void RenderUI(HDC hdc);
//    void RenderSlot(HDC hdc, int left, int top, const InventoryItem& item);
//    void RenderCursorItem(HDC hdc);
//
//    bool HandleClick(int mouseX, int mouseY, int button); // button: 1=left, 2=right
//    void HandleItemSlotLClick(InventoryItem* slot);
//    void HandleItemSlotRClick(InventoryItem* slot);
//
//    void AddItem(int slotIndex, const InventoryItem& item);
//    InventoryItem* GetItems() { return items; }
//
//    void SetPlayerToolbar(InventoryItem* toolbar);
//    void OnInteract(Player* player);  // 플레이어와 상호작용 (UI 열기)
//
//private:
//    int x, y;
//    bool isOpen = false;
//
//    const int SLOT_ROWS = 3;
//    const int SLOT_COLS = 9;
//    const int SLOT_SIZE = 50;
//    const int SLOT_MARGIN = 5;
//
//    const int UI_BASE_X = 360;
//    const int UI_BASE_Y = 150;
//    const int TOOLBAR_Y = 330;
//
//    HBITMAP bmp;
//    InventoryItem items[27];
//    InventoryItem* playerToolbar;
//};
