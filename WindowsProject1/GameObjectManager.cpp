#include "GameObjectManager.h"
#include "Crop.h"
#include "Fence.h"
#include "Animal.h"
#include "Player.h"
#include "Map.h"
void GameObjectManager::AddCrop(Crop* crop) { crops.push_back(crop); }
void GameObjectManager::AddAnimal(Animal* animal) { animals.push_back(animal); }
void GameObjectManager::AddFence(Fence* fence) { fences.push_back(fence); } //��Ÿ��(�ӽ�)





Crop* GameObjectManager::GetCropAt(int tileX, int tileY) { //�ش� ��ġ �۹� ����
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

void GameObjectManager::UpdateAll() { //��� ��ü ���¸� �� ���� ������Ʈ
    player->UpdatePlayer();  //�÷��̾� 
    for (auto animal : animals)
        animal->Update();    //���� 
    for (auto crop : crops)
        crop->Update();      //�۹� 
}




void GameObjectManager::RemoveCrop(Crop* crop) {
    crops.erase(std::remove(crops.begin(), crops.end(), crop), crops.end());
}
void GameObjectManager::RemoveFence(Fence* fence)
{
    fences.erase(std::remove(fences.begin(), fences.end(), fence), fences.end());
}