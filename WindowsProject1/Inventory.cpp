#include "Inventory.h"

Inventory::Inventory(int rows, int cols) : rows(rows), cols(cols) {
    items.resize(rows * cols);  // �� �������� �ʱ�ȭ
}

void Inventory::AddItem(CropType type, int count) {
    // ������ �������� ������ ���ϰ�, ������ �� ĭ�� �߰�
    for (auto& item : items) {
        if (item.type == type) {
            item.count += count;
            return;
        }
    }
    for (auto& item : items) {
        if (item.type == CropType::None) {
            item.type = type;
            item.count = count;
            return;
        }
    }
}

bool Inventory::RemoveItem(int index, int count) {
    if (index < 0 || index >= (int)items.size()) return false;
    if (items[index].count < count) return false;

    items[index].count -= count;
    if (items[index].count == 0) {
        items[index].type = CropType::None;
    }
    return true;
}

InventoryItem Inventory::GetItem(int index) const {
    if (index < 0 || index >= (int)items.size()) return {};
    return items[index];
}

InventoryItem& Inventory::GetMutableItem(int index) {
    return items[index]; // index �˻� �ʿ� �� �߰�
}



void Inventory::Render(HDC hdc, int startX, int startY)
{
    const int slotSize = 50;
    const int slotPaddingX = 5;
    const int slotPaddingY = 1;  // Y ���� 51�� ����

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            RECT rect = {
                startX + x * (slotSize + slotPaddingX),
                startY + y * (slotSize + slotPaddingY),
                startX + x * (slotSize + slotPaddingX) + slotSize,
                startY + y * (slotSize + slotPaddingY) + slotSize
            };

            HBRUSH brush = CreateSolidBrush(RGB(220, 220, 220));
            FillRect(hdc, &rect, brush);
            FrameRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            DeleteObject(brush);
        }
    }
    
   
}


//
//void Inventory::HandleClick(int mouseX, int mouseY) {
//    // TODO: Ŭ�� ��ġ�� ���� � �������� ����ϰ� ó��
//}
