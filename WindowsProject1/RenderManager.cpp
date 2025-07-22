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
    if (worldMap)
    {
       
        worldMap->Render(hdc);

    }
    auto& crops = GameObjectManager::Instance().GetCrops();
    for (auto& crop : crops) crop->Render(hdc);

    auto& fences = GameObjectManager::Instance().GetFences();
    for (auto& fence : fences) fence->Render(hdc);

    if (box) box->Render(hdc);
    if (house) house->Render(hdc);
       
    Player* player = GameObjectManager::Instance().GetPlayer();
    InventoryComponent* inventory = player->GetInventory();

    if (player) {
        player->Render(hdc);
        if (inventory)
            inventory->Render(hdc); //인벤토리 UI
        if (box->IsOpen()) //상자 오픈
        {
            box->SetPlayerToolbar(inventory->GetItems()); //플레이어 아이템 전달
            box->RenderUI(hdc);
        }
    }

   
}

