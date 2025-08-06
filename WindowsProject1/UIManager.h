#pragma once
#include "SingletonT.h"
#include "PlayerInventory.h"
#include "Box.h"

constexpr int SLOT_SIZE = 50;
constexpr int SLOT_MARGIN = 5;
constexpr int BOX_BASE_X = 360;
constexpr int BOX_BASE_Y = 150;
constexpr int TOOLBAR_Y = BOX_BASE_Y + 3 * (SLOT_SIZE + 1) + 10;

class UIManager : public SingletonT<UIManager>
{
    friend class SingletonT<UIManager>;

public:
    void OpenBoxUI(Box* boxItems, int boxSlotCount, PlayerInventory* playerItems, int playerSlotCount);
    void CloseBoxUI();
    void Update(float deltaTime);

    // 렌더 관련 함수
    void Render(HDC hdc);
    void RenderInventory(HDC hdc, PlayerInventory* playerInventory, int playerInventorySlotCount, int baseX, int baseY);
    void RenderBoxUI(HDC hdc, Box* box, PlayerInventory* playerInv);

    void HandleClick(int mouseX, int mouseY, bool isRightClick);

    bool IsBoxUIOpen() const { return openedBox != nullptr; }

    void SetPlayerInventory(PlayerInventory* inv);

    // 들고 있는 아이템 관련
    InventoryItem& GetHeldItem() { return heldItem; }
    void SetHeldItem(const InventoryItem& item) { heldItem = item; }
    void ClearHeldItem() { heldItem = InventoryItem(); } // NONE 상태로 초기화

    void RenderHeldItem(HDC hdc); // 마우스 커서 따라다니는 아이템 렌더링

    // 열린 박스 관련
    void SetOpenedBox(Box* box) { openedBox = box; }
    Box* GetOpenedBox() const { return openedBox; }
    bool HasHeldItem() const { return !heldItem.IsEmpty(); }
private:
    UIManager() = default;
    ~UIManager() = default;
    bool isBoxUIOpen = false;

    PlayerInventory* player = nullptr;
    int playerInventorySlotCount = 0;

    Box* openedBox = nullptr;
    int openedBoxSlotCount = 0;

    InventoryItem heldItem;
    int baseX = 100;
    int baseY = 100;


   

    // 내부 렌더링 헬퍼 함수들
   /* void DrawInventoryGrid(HDC hdc, Box* boxItems, int boxSlotCount, int baseX, int baseY);
    void DrawToolbar(HDC hdc, InventoryItem* playerToolbar, int toolbarSlotCount, int baseX, int baseY);
    void DrawHeldItem(HDC hdc);*/
};
