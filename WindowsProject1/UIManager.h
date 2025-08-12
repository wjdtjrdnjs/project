#pragma once
#include "SingletonT.h"
#include "PlayerInventory.h"
#include "Box.h"
#include "NPC.h"

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
    void OpenNpcUI(NPC* npcItems, int boxSlotCount, PlayerInventory* playerItems, int playerSlotCount);

    void CloseBoxUI();
    void CloseNpcUI();

    void Update(float deltaTime);

    // 렌더 관련 함수
    void Render(HDC hdc);
    void RenderInventory(HDC hdc, PlayerInventory* playerInventory, int playerInventorySlotCount, int baseX, int baseY);

    //박스 UI
    void RenderBoxUI(HDC hdc, Box* box, PlayerInventory* playerInv);
    void SetOpenedBox(Box* box) { openedBox = box; }
    Box* GetOpenedBox() const { return openedBox; }
    bool IsBoxUIOpen() const { return openedBox != nullptr; }

    //NPC UI
    void RenderNpcUI(HDC hdc, NPC* npc, PlayerInventory* playerInv);
    void SetOpenedNpc(NPC* npc) { openednpc = npc; }
    NPC* GetOpenedNpc() const { return openednpc; }
    bool IsNpcUIOpen() const { return openednpc != nullptr; }



    void HandleClick(int mouseX, int mouseY, bool isRightClick);
    void SetPlayerInventory(PlayerInventory* inv);

    // 들고 있는 아이템 관련
    InventoryItem& GetHeldItem() { return heldItem; }
    void SetHeldItem(const InventoryItem& item) { heldItem = item; }
    void ClearHeldItem() { heldItem = InventoryItem(); } // NONE 상태로 초기화

    void RenderHeldItem(HDC hdc); // 마우스 커서 따라다니는 아이템 렌더링

 
    bool HasHeldItem() const { return !heldItem.IsEmpty(); }
private:
    UIManager() = default;
    ~UIManager() = default;
    bool isBoxUIOpen = false;
    bool isNpcUIOpen = false;

    PlayerInventory* player = nullptr;
    int playerInventorySlotCount = 0;

    Box* openedBox = nullptr;
    int openedBoxSlotCount = 0;

    NPC* openednpc = nullptr;
    int openednpcSlotCount = 0;

    InventoryItem heldItem;
    int baseX = 100;
    int baseY = 100;


   

    // 내부 렌더링 헬퍼 함수들
   /* void DrawInventoryGrid(HDC hdc, Box* boxItems, int boxSlotCount, int baseX, int baseY);
    void DrawToolbar(HDC hdc, InventoryItem* playerToolbar, int toolbarSlotCount, int baseX, int baseY);
    void DrawHeldItem(HDC hdc);*/
};
