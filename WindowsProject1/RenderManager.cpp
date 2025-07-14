#include "RenderManager.h"

Player* RenderManager::player = nullptr; //플레이어
Map* RenderManager::map = nullptr; //맵
Box* RenderManager::box = nullptr; //상자

std::vector<Crop*> RenderManager::crops;  //작물
std::vector<Animal*> RenderManager::animals; //동물
std::vector<Fence*> RenderManager::fences; //울타리(임시)

void RenderManager::SetPlayer(Player* p) { player = p; }
void RenderManager::SetMap(Map* m) { map = m; }
void RenderManager::SetBox(Box* b) { box = b; }
void RenderManager::AddCrop(Crop* crop) { crops.push_back(crop); }
void RenderManager::AddAnimal(Animal* animal) { animals.push_back(animal); }

void RenderManager::AddFence(Fence* fence) { fences.push_back(fence); } //울타리(임시)

void RenderManager::RenderAll(HDC hdc, HWND hWnd)
{
    RECT r;
    GetClientRect(hWnd, &r);
    if (map) map->Render(hdc); //맵
    for (auto& crop : crops) crop->Render(hdc); //작물
    for (auto& animal : animals) animal->Render(hdc); //동물 
    for (auto& fence : fences) fence->Render(hdc);//울타리(임시) 
   // if (box) box->Render(hdc); //박스 

   /* if (player->IsInventoryOpen()) {
        player->RenderFullInventory(hdc);
    }*/

   // if (box->IsOpen()) box->RenderUI(hdc); //박스 아이템 창

    if (player) 
    {
        player->Render(hdc); //플레이어
        player->RenderInventory(hdc, r.right, r.bottom); //플레이어 아래 인벤토라 창(툴바)
    }
}

void RenderManager::UpdateAll() { //모든 객체 상태를 한 번에 업데이트
    player->PlayerUpdate();  //플레이어 
    for (auto animal : animals)
        animal->Update();    //동물 
    for (auto crop : crops)
        crop->Update();      //작물 
}
Crop* RenderManager::GetCropAt(int tileX, int tileY) { //해당 위치 작물 리턴
    int px = tileX * tileSize;
    int py = tileY * tileSize;
    for (Crop* c : crops) {
        if (c->GetX() == px && c->GetY() == py) return c;
    }
    return nullptr;
}

Fence* RenderManager::GetFencepAt(int tileX, int tileY)
{
    int px = tileX * tileSize;
    int py = tileY * tileSize;
    for (Fence* f : fences) {
        if (f->GetX() == px && f->GetY() == py) return f;
    }
    return nullptr;
}

//void RenderManager::RemoveCrop(Crop* crop) { //작물 삭제
//    crops.erase(std::remove(crops.begin(), crops.end(), crop), crops.end());
//}
void RenderManager::RemoveCrop(Crop* crop) {
    crops.erase(std::remove(crops.begin(), crops.end(), crop), crops.end());


}