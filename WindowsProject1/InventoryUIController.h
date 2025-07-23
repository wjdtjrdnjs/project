#pragma once
#include <windows.h>
#include "InventoryItem.h"

class InventoryComponent;
class InventoryUIController {
public:
    InventoryUIController();

    void Initialize(int slotCount);// �κ��丮 UI �ʱ�ȭ 
    
    void UpdateInventory(InventoryItem* items);// �κ��丮 ���� ����

    void ToolSelected(int index);// ���õ� �� ǥ��

    void Render(HDC hdc);//������

    int ProcessMouseClick(int mouseX, int mouseY); // ���콺 Ŭ�� �̺�Ʈ ó��, Ŭ���� ���� �ε��� ��ȯ

private:
    InventoryItem inventorySlots[9];
    int selectedSlot = -1;

    // ���� ��ġ �� ũ�� 
    static constexpr int slotSize = 40;
    static constexpr int slotPadding = 5;
    static constexpr int baseX = 10;
    static constexpr int baseY = 10;

    // ���� ��ǥ ��� �Լ�
    RECT GetSlotRect(int index) const;
};



