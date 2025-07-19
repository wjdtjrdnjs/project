#include "GameObjectManager.h"
#include "Crop.h"
#include "Fence.h"
#include "Animal.h"
#include "Player.h"
#include "Map.h"
void GameObjectManager::AddCrop(Crop* crop) { crops.push_back(crop); }
void GameObjectManager::AddAnimal(Animal* animal) { animals.push_back(animal); }
void GameObjectManager::AddFence(Fence* fence) { fences.push_back(fence); } //울타리(임시)





Crop* GameObjectManager::GetCropAt(int tileX, int tileY) { //해당 위치 작물 리턴
    int px = tileX * tileSize;
    int py = tileY * tileSize;
    for (Crop* c : crops) {
        if (c->GetX() == px && c->GetY() == py) return c;
    }

    return nullptr;
}

Fence* GameObjectManager::GetFenceAt(int tileX, int tileY)
{
    int px = tileX * tileSize;
    int py = tileY * tileSize;
    for (Fence* f : fences) {
        if (f->GetX() == px && f->GetY() == py) return f;
    }
    return nullptr;
}

void GameObjectManager::UpdateAll() { //모든 객체 상태를 한 번에 업데이트
    player->UpdatePlayer();  //플레이어 
    for (auto animal : animals)
        animal->Update();    //동물 
    for (auto crop : crops)
        crop->Update();      //작물 
}




void GameObjectManager::RemoveCrop(Crop* crop) {
    crops.erase(std::remove(crops.begin(), crops.end(), crop), crops.end());
}
void GameObjectManager::RemoveFence(Fence* fence)
{
    fences.erase(std::remove(fences.begin(), fences.end(), fence), fences.end());
}