#pragma once
#include "CropType.h" 
#include "InventoryItem.h"

class InventoryUIController;

class InventoryComponent {
public:
    InventoryComponent(InventoryUIController* uiController = nullptr); //�ļ��ڿ� �κ��丮UI��Ʈ�ѷ� ����

    void AddItem(CropType type); //�۹� ������ �κ��丮�� �߰�

    InventoryItem& operator[](int index) {
        return inventory[index];
    }
    void SetUIController(InventoryUIController* controller);// UI ��Ʈ�ѷ� ����

    InventoryUIController* GetUIController()
    {
        return uicontroller;
    }
    void Render(HDC hdc);//�κ��丮UI ������
    
    
    InventoryItem* GetItems() { return inventory; } //�κ��丮 ������ �迭 ��ȯ
    
    void SetSelectedTool(int index) { tool = index; }

    int GetSelectedTool() { return tool; } //���� ���õ� �� ��ȯ
    bool getisboxopen() { return isBoxOpen; } //�ڽ��� �����ִ� �� ����

private:
    InventoryItem inventory[9]; //9ĭ �迭
    InventoryUIController* uicontroller = nullptr;
    int tool;
    bool isBoxOpen = false;
    bool isOpen = false;
};

