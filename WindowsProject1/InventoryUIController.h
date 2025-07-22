#pragma once
#include <windows.h>

#include "InventoryItem.h"
#include "CropType.h"

class InventoryComponent;

class InventoryUIController {
public:
    InventoryUIController();

    // �κ��丮 UI �ʱ�ȭ (������ ���� ����, ��ġ ��)
    void Initialize(int slotCount);

    // �κ��丮 ���� ���� (�ܺο��� �κ��丮 ������ �迭�� �޾Ƽ� UI�� �ݿ�)
    void UpdateInventory(InventoryItem* items);


    // ���õ� �� ǥ�� (InventoryComponent���� ȣ��)
    void ToolSelected(int index);

    // ������ �Լ� (������ DC�� �������� �°� ���� �ʿ�)
    void Render(HDC hdc);

    // ���콺 Ŭ�� �̺�Ʈ ó��, Ŭ���� ���� �ε��� ��ȯ (-1�̸� ����)
    int ProcessMouseClick(int mouseX, int mouseY);

private:
    InventoryItem inventorySlots[9];
    int selectedSlot = -1;

    // ���� ��ġ �� ũ�� (��: 9�� ���� ���� �迭)
    static constexpr int slotSize = 40;
    static constexpr int slotPadding = 5;
    static constexpr int baseX = 10;
    static constexpr int baseY = 10;

    // ���� ��ǥ ��� �Լ�
    RECT GetSlotRect(int index) const;
};



