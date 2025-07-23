#pragma once
#include "CropType.h" 
#include "InventoryItem.h"

class InventoryUIController;

class InventoryComponent {
public:
    InventoryComponent(InventoryUIController* uiController = nullptr); //셍성자에 인벤토리UI컨트롤러 주입

    void AddItem(CropType type); //작물 아이템 인벤토리에 추가

    InventoryItem& operator[](int index) {
        return inventory[index];
    }
    void SetUIController(InventoryUIController* controller);// UI 컨트롤러 설정

    InventoryUIController* GetUIController()
    {
        return uicontroller;
    }
    void Render(HDC hdc);//인벤토리UI 렌더링
    
    
    InventoryItem* GetItems() { return inventory; } //인벤토리 아이템 배열 반환
    
    void SetSelectedTool(int index) { tool = index; }

    int GetSelectedTool() { return tool; } //현재 선택된 툴 반환
    bool getisboxopen() { return isBoxOpen; } //박스가 열려있는 지 여부

private:
    InventoryItem inventory[9]; //9칸 배열
    InventoryUIController* uicontroller = nullptr;
    int tool;
    bool isBoxOpen = false;
    bool isOpen = false;
};

