#pragma once
#include <vector>
#include <windows.h>
#include <string>
#include "Crop.h"
#include "InventoryItem.h"  //  
class Inventory {
public:
    Inventory(int rows = 3, int cols = 9);

    void AddItem(CropType type, int count = 1);
    bool RemoveItem(int index, int count = 1);

    InventoryItem GetItem(int index) const;
    InventoryItem& GetMutableItem(int index);

    void Render(HDC hdc, int startX, int startY);
    //void HandleClick(int mouseX, int mouseY);

    int GetSlotCount() const { return (int)items.size(); }

private:
    std::vector<InventoryItem> items;
    int rows;
    int cols;
};
