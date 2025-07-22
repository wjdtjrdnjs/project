#pragma once
#include "CropType.h" 
#include "InventoryItem.h"

class InventoryUIController;

class InventoryComponent {
public:
    InventoryComponent(InventoryUIController* uiController = nullptr);
    void AddItem(CropType type);		
    InventoryItem& operator[](int index) {
        return inventory[index];
    }
    void SetUIController(InventoryUIController* controller);
    InventoryUIController* GetUIController()
    {
        return uicontroller;
    }
    void Render(HDC hdc);
    
    
    InventoryItem* GetItems() { return inventory; }
    
    void SetSelectedTool(int index) { tool = index; }
    int GetSelectedTool() { return tool; }
    bool getisboxopen() { return isBoxOpen; }
private:
    InventoryItem inventory[9];
    InventoryUIController* uicontroller = nullptr;
    int tool;
    bool isBoxOpen = false;
    bool isOpen = false;
};

