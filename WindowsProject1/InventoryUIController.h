#pragma once
#include <windows.h>

#include "InventoryItem.h"
#include "CropType.h"

class InventoryComponent;

class InventoryUIController {
public:
    InventoryUIController();

    // 인벤토리 UI 초기화 (아이템 슬롯 개수, 위치 등)
    void Initialize(int slotCount);

    // 인벤토리 내용 갱신 (외부에서 인벤토리 아이템 배열을 받아서 UI에 반영)
    void UpdateInventory(InventoryItem* items);


    // 선택된 툴 표시 (InventoryComponent에서 호출)
    void ToolSelected(int index);

    // 렌더링 함수 (윈도우 DC나 렌더러에 맞게 수정 필요)
    void Render(HDC hdc);

    // 마우스 클릭 이벤트 처리, 클릭한 슬롯 인덱스 반환 (-1이면 없음)
    int ProcessMouseClick(int mouseX, int mouseY);

private:
    InventoryItem inventorySlots[9];
    int selectedSlot = -1;

    // 슬롯 위치 및 크기 (예: 9개 슬롯 가로 배열)
    static constexpr int slotSize = 40;
    static constexpr int slotPadding = 5;
    static constexpr int baseX = 10;
    static constexpr int baseY = 10;

    // 슬롯 좌표 계산 함수
    RECT GetSlotRect(int index) const;
};



