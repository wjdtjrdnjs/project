#include "RenderManager.h"
#include "GameObjectManager.h"
#include "InventoryComponent.h"
#include "PlayerController.h"
#include "InventoryUIController.h"
#include <string>

#include "Animal.h"
#include "Crop.h"
void RenderManager::SetHouse(House* h) { house = h; }
void RenderManager::SetWorldMap(WorldMap* wm) { worldMap = wm; }
void RenderManager::SetMyRoomMap(MyRoomMap* mym) { mymap = mym; }
void RenderManager::SetBox(Box* b) { box = b; }

void RenderManager::RenderAll(HDC hdc, HWND hWnd)
{
    RECT r;
    GetClientRect(hWnd, &r);

    if (GameObjectManager::Instance().IsPlayerInsideHouse()) //플레이어가 집 내부에 입장
    {
        OutputDebugStringA("마이룸\n");
        mymap->Render(hdc);  //마이룸
    }
    else if (worldMap)
    {
        worldMap->Render(hdc); //월드 맵
    }

    //활성화된 작물만 렌더링
    auto& crops = GameObjectManager::Instance().GetCrops(); 
    for (auto& crop : crops)
        if (crop->IsActive())  
              crop->Render(hdc);

    //활성화된 울타리만 렌더링
    auto& fences = GameObjectManager::Instance().GetFences(); 
    for (auto& fence : fences)
        if (fence->IsActive())
             fence->Render(hdc);
   
    if (box && box->IsActive()) //활성화된 상자 렌더링
        box->Render(hdc); 

    if (house && house->IsActive())// 활성화된 집 렌더링
        house->Render(hdc); 
    Player* player = GameObjectManager::Instance().GetPlayer();  //player 객체 포인터 가져옴
    InventoryComponent* inventory = player->GetInventory();     //iinventory 객체 포인터 가져옴

    if (player) 
    {
        player->Render(hdc); //플레이어 렌더링
        if (inventory)
        {
            inventory->Render(hdc); //인벤토리 UI 렌더링
        }
        if (box && box->IsOpen()) //상자 오픈
        {
            box->SetPlayerToolbar(inventory->GetItems()); //플레이어 인벤토리를 상자에 전달
            box->RenderUI(hdc);   //상자와 플레이어 인벤토리 UI 
        }
    }

   
}

