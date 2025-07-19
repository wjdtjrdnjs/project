#include "RenderManager.h"
#include "GameObjectManager.h"
#include "Animal.h"
#include "House.h"
void RenderManager::SetHouse(House* h) { house = h; }
void RenderManager::SetMap(Map* m) { map = m; }
//void RenderManager::SetMyRoomMap(MyRoomMap* mym) { mymap = mym; }
void RenderManager::SetBox(Box* b) { box = b; }

void RenderManager::RenderAll(HDC hdc, HWND hWnd)
{
    RECT r;
    GetClientRect(hWnd, &r);

    if (map) map->Render(hdc);
    auto& crops = GameObjectManager::Instance().GetCrops();
    for (auto& crop : crops) crop->Render(hdc);

    auto& fences = GameObjectManager::Instance().GetFences();
    for (auto& fence : fences) fence->Render(hdc);

    if (box) box->Render(hdc);
    if (house) house->Render(hdc);

    Player* player = GameObjectManager::Instance().GetPlayer();
    if (player) {
        player->Render(hdc);
        player->RenderInventory(hdc, r.right, r.bottom);
    }

    if (box->IsOpen()) box->RenderUI(hdc);
}

