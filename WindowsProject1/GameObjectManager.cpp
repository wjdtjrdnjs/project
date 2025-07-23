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
void GameObjectManager::AddCrop(Crop* crop) { crops.push_back(crop); allObjects.push_back(crop); } //작물
void GameObjectManager::AddAnimal(Animal* animal) { animals.push_back(animal); allObjects.push_back(animal); }//동물
void GameObjectManager::AddFence(Fence* fence) { fences.push_back(fence); allObjects.push_back(fence);} //울타리



GameObjectManager& GameObjectManager::Instance()
{
    static GameObjectManager instance;
    return instance;
}

void GameObjectManager::Init(HWND hWnd_) {
    hWnd = hWnd_;
    InputManager::Instance().Init(hWnd);

    uiController = new InventoryUIController();  //UI컨트롤러 생성
    inventory = new InventoryComponent();       //엔벤토리 생성
    inventory->SetUIController(uiController);   //UI컨트롤러 연결

    player = new Player(inventory);    // 플레이어 생성 (인벤토리 주입)
    controller = new PlayerController(player, inventory);  // 플레이어컨트롤러 생성

    //상자 월드맵, 집, 동물 생성
    box = new Box(127, 285);  
    worldMap = new WorldMap();
    house = new House();
    animal = new Animal();
    MyRoomMap* myRoomMap = new MyRoomMap();

    // 렌더링 대상 등록
    AddGameObject(player);
    AddGameObject(box);
    AddGameObject(house);
    AddGameObject(animal);

    // 전역 접근용 인스턴스 설정
    SetPlayer(player);
    AddAnimal(animal);
    SetPlayerController(controller);

    // 렌더 매니저에  객체 설정
    RenderManager::Instance().SetBox(box);
    RenderManager::Instance().SetWorldMap(worldMap);
    RenderManager::Instance().SetHouse(house);
    RenderManager::Instance().SetMyRoomMap(myRoomMap);
}

void GameObjectManager::Update() //업데이트 함수
{
    InputManager::Instance().Update();       // 입력 상태 갱신
    GameObjectManager::Instance().UpdateAll();  // 모든 오브젝트 업데이트
}

void GameObjectManager::Render(HDC hdc, HWND hWnd)
{
    RenderManager::Instance().RenderAll(hdc, hWnd);  // 렌더 매니저 전달
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

void GameObjectManager::Release()  //리소스 해제
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

void GameObjectManager::AddGameObject(GameObject* obj) // 모든 객체를 allObjects에 등록
{
    if (obj)
        allObjects.push_back(obj);
}

void GameObjectManager::SetPlayerInsideHouse(bool inside)// 플레이어가 집 안에 있는지 여부 설정
{
    playerInsideHouse = inside;
    for (auto& obj : allObjects) {
        if (obj)
            obj->SetActive(obj->IsInsideHouse() == inside);// 집 내부 객체만 활성화
    }
}

void GameObjectManager::RemoveGameObject(GameObject* obj) {
    if (!obj) return;

    auto it = std::find(allObjects.begin(), allObjects.end(), obj);
    if (it != allObjects.end()) {
        allObjects.erase(it);
        delete obj; // 동적할당된 오브젝트일 경우
    }
}
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