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

    for (int i = 0; i < 9; i++) {  //플레이어 인벤토리 초기화
        inventory[i].type = CropType::None;
        inventory[i].count = 0;
    }

    //기본 아이템
    inventory[0].type = CropType::Strawberry_1; //1번 딸기봉투와 5개
    inventory[0].count = 5;
    inventory[1].type = CropType::Onion_1;      //2번 양파봉투 5개
    inventory[1].count = 5;
    inventory[2].type = CropType::hoe;        //괭이
    inventory[2].count = 1;
    inventory[3].type = CropType::watering;     //물뿌리개
    inventory[3].count = 1;

}


void InventoryComponent::AddItem(CropType type) {   //인벤토리에 아이템 추가 
 
    for (auto& slot : inventory) {//같은 타입이면 수량 증가
        if (slot.type == type) {
            slot.count++;
            return;
        }
    }
    for (auto& slot : inventory) {
        if (slot.type == CropType::None) { //같은 타입이 없으면 슬롯에 타입을 넣고 수량 추가
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

