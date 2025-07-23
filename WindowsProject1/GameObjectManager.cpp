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
void GameObjectManager::AddCrop(Crop* crop) { crops.push_back(crop); allObjects.push_back(crop); } //�۹�
void GameObjectManager::AddAnimal(Animal* animal) { animals.push_back(animal); allObjects.push_back(animal); }//����
void GameObjectManager::AddFence(Fence* fence) { fences.push_back(fence); allObjects.push_back(fence);} //��Ÿ��



GameObjectManager& GameObjectManager::Instance()
{
    static GameObjectManager instance;
    return instance;
}

void GameObjectManager::Init(HWND hWnd_) {
    hWnd = hWnd_;
    InputManager::Instance().Init(hWnd);

    uiController = new InventoryUIController();  //UI��Ʈ�ѷ� ����
    inventory = new InventoryComponent();       //�����丮 ����
    inventory->SetUIController(uiController);   //UI��Ʈ�ѷ� ����

    player = new Player(inventory);    // �÷��̾� ���� (�κ��丮 ����)
    controller = new PlayerController(player, inventory);  // �÷��̾���Ʈ�ѷ� ����

    //���� �����, ��, ���� ����
    box = new Box(127, 285);  
    worldMap = new WorldMap();
    house = new House();
    animal = new Animal();
    MyRoomMap* myRoomMap = new MyRoomMap();

    // ������ ��� ���
    AddGameObject(player);
    AddGameObject(box);
    AddGameObject(house);
    AddGameObject(animal);

    // ���� ���ٿ� �ν��Ͻ� ����
    SetPlayer(player);
    AddAnimal(animal);
    SetPlayerController(controller);

    // ���� �Ŵ�����  ��ü ����
    RenderManager::Instance().SetBox(box);
    RenderManager::Instance().SetWorldMap(worldMap);
    RenderManager::Instance().SetHouse(house);
    RenderManager::Instance().SetMyRoomMap(myRoomMap);
}

void GameObjectManager::Update() //������Ʈ �Լ�
{
    InputManager::Instance().Update();       // �Է� ���� ����
    GameObjectManager::Instance().UpdateAll();  // ��� ������Ʈ ������Ʈ
}

void GameObjectManager::Render(HDC hdc, HWND hWnd)
{
    RenderManager::Instance().RenderAll(hdc, hWnd);  // ���� �Ŵ��� ����
}


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

void GameObjectManager::Release()  //���ҽ� ����
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

void GameObjectManager::AddGameObject(GameObject* obj) // ��� ��ü�� allObjects�� ���
{
    if (obj)
        allObjects.push_back(obj);
}

void GameObjectManager::SetPlayerInsideHouse(bool inside)// �÷��̾ �� �ȿ� �ִ��� ���� ����
{
    playerInsideHouse = inside;
    for (auto& obj : allObjects) {
        if (obj)
            obj->SetActive(obj->IsInsideHouse() == inside);// �� ���� ��ü�� Ȱ��ȭ
    }
}

void GameObjectManager::RemoveGameObject(GameObject* obj) {
    if (!obj) return;

    auto it = std::find(allObjects.begin(), allObjects.end(), obj);
    if (it != allObjects.end()) {
        allObjects.erase(it);
        delete obj; // �����Ҵ�� ������Ʈ�� ���
    }
}
void GameObjectManager::UpdateAll() { //��� ��ü ���¸� �� ���� ������Ʈ
    if (controller)
        controller->UpdatePlayer();

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