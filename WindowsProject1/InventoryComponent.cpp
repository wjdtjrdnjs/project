#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <windows.h>
#include "InventoryComponent.h"
#include "InventoryUIController.h"
#include "InventoryItem.h"
#include "Crop.h" 

InventoryComponent::InventoryComponent(InventoryUIController* uiController)
    : uicontroller(uiController), tool(0)
{

    for (int i = 0; i < 9; i++) {  //�÷��̾� �κ��丮 �ʱ�ȭ
        inventory[i].type = CropType::None;
        inventory[i].count = 0;
    }

    //�⺻ ������
    inventory[0].type = CropType::Strawberry_1; //1�� ��������� 5��
    inventory[0].count = 5;
    inventory[1].type = CropType::Onion_1;      //2�� ���ĺ��� 5��
    inventory[1].count = 5;
    inventory[2].type = CropType::hoe;        //����
    inventory[2].count = 1;
    inventory[3].type = CropType::watering;     //���Ѹ���
    inventory[3].count = 1;

}


void InventoryComponent::AddItem(CropType type) {   //�κ��丮�� ������ �߰� 
 
    for (auto& slot : inventory) {//���� Ÿ���̸� ���� ����
        if (slot.type == type) {
            slot.count++;
            return;
        }
    }
    for (auto& slot : inventory) {
        if (slot.type == CropType::None) { //���� Ÿ���� ������ ���Կ� Ÿ���� �ְ� ���� �߰�
            slot.type = type;
            slot.count = 1;
            return;
        }
    }
}

void InventoryComponent::SetUIController(InventoryUIController* controller)
{
    if (controller == nullptr) {
        OutputDebugString(L"SetUIController called with nullptr!\n");
        return;
    }
    uicontroller = controller;
    uicontroller->UpdateInventory(GetItems());
}

void InventoryComponent::Render(HDC hdc)
{
    if (uicontroller)
    {
        uicontroller->Render(hdc);
        uicontroller->ToolSelected(tool);
        uicontroller->UpdateInventory(GetItems());
    }
}

