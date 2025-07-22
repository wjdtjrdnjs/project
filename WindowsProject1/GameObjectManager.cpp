#include "GameObjectManager.h"
#include "Player.h"
#include "Box.h"
#include "WorldMap.h"
#include "PlayerController.h"
#include "InventoryComponent.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "House.h"
#include "Animal.h"
#include "BitmapManager.h"
#include "GameObject.h"
#include <string>
void GameObjectManager::AddCrop(Crop* crop) { crops.push_back(crop); }

void GameObjectManager::AddAnimal(Animal* animal) { animals.push_back(animal); }
void GameObjectManager::AddFence(Fence* fence) { fences.push_back(fence); } //울타리(임시)



GameObjectManager& GameObjectManager::Instance()
{
    static GameObjectManager instance;
    return instance;
}

void GameObjectManager::Init(HWND hWnd_) {
    hWnd = hWnd_;
    InputManager::Instance().Init(hWnd);

    uiController = new InventoryUIController();
    inventory = new InventoryComponent();
    inventory->SetUIController(uiController);

    player = new Player(inventory);
    controller = new PlayerController(player, inventory);

    box = new Box(127, 285);
    worldMap = new WorldMap();
    house = new House();
    animal = new Animal();

   /* AddGameObject(player);
    AddGameObject(box);
    AddGameObject(house);
    AddGameObject(animal);*/

    GameObjectManager::Instance().SetPlayer(player);
    RenderManager::Instance().SetBox(box);
    RenderManager::Instance().SetWorldMap(worldMap);
    RenderManager::Instance().SetHouse(house);
    GameObjectManager::Instance().AddAnimal(animal);

    GameObjectManager::Instance().SetPlayer(player);
    GameObjectManager::Instance().SetPlayerController(controller);
}

void GameObjectManager::Update()
{
    InputManager::Instance().Update();
    GameObjectManager::Instance().UpdateAll();
}

void GameObjectManager::Render(HDC hdc, HWND hWnd)
{
    RenderManager::Instance().RenderAll(hdc, hWnd);
}


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

void GameObjectManager::Release()
{
    delete animal;
    delete box;
    delete house;
    delete worldMap;
    delete player;
    delete inventory;
    delete controller;
    animal = nullptr;
    box = nullptr;
    house = nullptr;
    worldMap = nullptr;
    player = nullptr;
    inventory = nullptr;
    controller = nullptr;
}

//void GameObjectManager::AddGameObject(GameObject* obj)
//{
//    if (obj)
//        allObjects.push_back(obj);
//}
//
//void GameObjectManager::SetPlayerInsideHouse(bool inside)
//{
//    playerInsideHouse = inside;
//    for (auto& obj : allObjects) {
//        if (obj)
//            obj->SetActive(obj->IsInsideHouse() == inside);
//    }
//}
//
//void GameObjectManager::RemoveGameObject(GameObject* obj) {
//    if (!obj) return;
//
//    auto it = std::find(allObjects.begin(), allObjects.end(), obj);
//    if (it != allObjects.end()) {
//        allObjects.erase(it);
//        delete obj; // 동적할당된 오브젝트일 경우
//    }
//}
void GameObjectManager::UpdateAll() { //모든 객체 상태를 한 번에 업데이트
    if (controller)
        controller->UpdatePlayer();

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