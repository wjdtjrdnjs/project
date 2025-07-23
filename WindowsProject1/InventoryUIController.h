#pragma once
#include <windows.h>
#include "InventoryItem.h"

class InventoryComponent;
class InventoryUIController {
public:
    InventoryUIController();

    void Initialize(int slotCount);// 인벤토리 UI 초기화 
    
    void UpdateInventory(InventoryItem* items);// 인벤토리 내용 갱신

    void ToolSelected(int index);// 선택된 툴 표시

    void Render(HDC hdc);//렌더링

    int ProcessMouseClick(int mouseX, int mouseY); // 마우스 클릭 이벤트 처리, 클릭한 슬롯 인덱스 반환

private:
    InventoryItem inventorySlots[9];
    int selectedSlot = -1;

    // 슬롯 위치 및 크기 
    static constexpr int slotSize = 40;
    static constexpr int slotPadding = 5;
    static constexpr int baseX = 10;
    static constexpr int baseY = 10;

    // 슬롯 좌표 계산 함수
    RECT GetSlotRect(int index) const;
};



