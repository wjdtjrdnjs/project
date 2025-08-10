#include "GameObjectManager.h"
#include "Map.h"
#include "Box.h"
#include "Crop.h"
#include "Tree.h"
#include "House.h"
#include "Fence.h"
#include "Player.h"
#include "Map.h"
#include "TileData.h"
#include "UIManager.h"
#include <memory>


void GameObjectManager::Init()
{

    Map& map = currentMap(); // 맵을 참조로 가져온다고 가정

    for (int y = 0; y < map.getHeight(); ++y)
    {
        for (int x = 0; x < map.getWidth(); ++x)
        {
            TileData& tile = map.getTile(x,y);

            tile.tileType = TileType::None;
            tile.object = nullptr; // 오브젝트 제거
        }
    }
}


void GameObjectManager::InteractWithTile(int tileX, int tileY, Player& player)
{
    static int lastTypeValue = -1;

    TileData tileData = currentMap().getTile(tileX, tileY);
    auto currentObject = tileData.object;

    if (currentObject)
    {
        int currentTypeValue = static_cast<int>(currentObject->GetPlaceableType());

        if (currentTypeValue == static_cast<int>(PlaceableType::Box) && !player.IsInteracting())
        {
            player.StartInteraction();
            Box* box = dynamic_cast<Box*>(currentObject.get());  // 
            if (box)
            {
               box->OnInteract(&player); // Box클래스를 거쳐서 ui매니저로 이동
            }
        }
    }
    else
    {
        if (lastTypeValue != -1)
        {
            OutputDebugStringA("해당 위치에 오브젝트가 없습니다 (nullptr).\n");
            lastTypeValue = -1;
        }
    }
}


void GameObjectManager::LoadMap(const std::string& mapName)
{
    //addPlayer(10, 10);
    //addMap(mapName, 40, 19, TileType::Grass);

    //// 맵에 따라 다른 오브젝트와 설정 추가

    //    RECT portalToMyroom = { 1260, 350, 1280, 416 }; //포탈 z위치 지정
    //    addPortal(mapName, portalToMyroom, 1); //포탈 생성

    //    // 230, 580, 320, 600
    //    // 
    //    //(포탈이름, x,y) 포탈 입장 후 플레이어 위치 설정 -진행 중-
    //    //포탈에 입장했을 때 플레이어 위치 설정 -- 나중에 추가 현재 


    //    for (int i = 0; i < 3; i++)
    //    {
    //        for (int j = 0; j < 3; j++)
    //        {
    //            addObjectToCurrentMap(mapName, 10 + i, 7 + j, TileType::Farmland, PlaceableType::Crop, CropType::Strawberry);
    //            addObjectToCurrentMap(mapName, 15 + i, 7 + j, TileType::Farmland, PlaceableType::Crop, CropType::Onion);
    //        }
    //    }

    //    addObjectToCurrentMap(mapName, 11, 6, TileType::None, PlaceableType::Box);
    //    addObjectToCurrentMap(mapName, 16, 6, TileType::None, PlaceableType::Box);
    //    addObjectToCurrentMap(mapName, 5, 3, TileType::None, PlaceableType::Tree);
    //    addObjectToCurrentMap(mapName, 3, 10, TileType::None, PlaceableType::House);
    //    addObjectToCurrentMap(mapName, 1, 1, TileType::None, PlaceableType::Fence);

    //    for (int i = 0; i < 32; i++)
    //    {
    //        for (int j = 0; j < 2; j++)
    //        {
    //            addObjectToCurrentMap(mapName, 8 + i, 11 + j, TileType::Path);
    //        }
    //    }
    //    for (int i = 0; i < 8; i++)
    //    {
    //        for (int j = 0; j < 2; j++)
    //        {
    //            addObjectToCurrentMap(mapName, 13 + j, 10 - i, TileType::Path);

    //        }
    //    }
    //    for (int i = 0; i < 6; i++)
    //    {
    //        addObjectToCurrentMap(mapName, 12 - i, 13 + i, TileType::Path);
    //        addObjectToCurrentMap(mapName, 13 - i, 13 + i, TileType::Path);
    //        addObjectToCurrentMap(mapName, 14 - i, 13 + i, TileType::Path);

    //    }
}
 

void GameObjectManager::Update(float deltaTime)
{
    player->Update(deltaTime);
    currentMap().Update(deltaTime);
}

void GameObjectManager::Render(HDC hdc)
{
    if (!HasMaps()) return;
    maps[currentMapIndex].Render(hdc);

    if (player)
    {
        player->Render(hdc);
        UIManager::Instance().Render(hdc);
    }
}

bool GameObjectManager::IsFarmlandTile(int x, int y)
{
    Map& map = currentMap();
    TileData& tile = map.getTile(x, y);
    return tile.tileType == TileType::Farmland;
}


void GameObjectManager::addMap(const std::string& mapName, int width, int height, TileType type)
{
    Map newMap;
    newMap.name = mapName;
    newMap.initTiles(width, height, type);
    maps.push_back(newMap);
    OutputDebugStringA(("맵 생성 " + mapName + "\n").c_str());

    if (maps.size() == 1) //첫맵이면 0으로 초기화
        currentMapIndex = 0;
}

void GameObjectManager::addObjectToCurrentMap(const std::string& mapName, int x, int y, TileType tileType, PlaceableType placeableType, CropType cropType)
{
    int mapIndex = GetMapIndexByName(mapName);
    if (mapIndex == -1) return; // 맵이 없으면 리턴

    Map& map = maps[mapIndex]; //인덱스를 가져와 현재 맵 참조

    int index = y * map.getWidth() + x;
    TileData& tile = map.mapTiles[index]; //현재 맵 타일 참조

    if (tileType != TileType::None)  //타일 none이 아닐 때 변경
        tile.tileType = tileType;

    if (placeableType != PlaceableType::None && !tile.object)
    {
        std::shared_ptr<WorldObject> obj;

        switch (placeableType)
        {
        case PlaceableType::None:
            break;

        case PlaceableType::Crop:
            // 씨앗 타입을 실제 작물 타입으로 변환
            switch (cropType)
            {
            case CropType::Strawberry:
            case CropType::Onion:
                obj = std::make_shared<Crop>(cropType);
                break;
            }
            break;

        case PlaceableType::Box:
            obj = std::make_shared<Box>();
            break;

        case PlaceableType::Tree:
            obj = std::make_shared<Tree>();
            break;

        case PlaceableType::House:
            obj = std::make_shared<House>();
            break;

        case PlaceableType::Fence:
            obj = std::make_shared<Fence>();
            break;
        }

        if (obj)
        {
            tile.object = obj;
            obj->SetPosition(x, y);

            OutputDebugStringA("오브젝트 생성\n");


        }
    }
}

void GameObjectManager::addPlayer(int x, int y)  //플레이어 생성 및 위치 설정
{
    auto newPlayer = std::make_shared<Player>(); //스마트포인터로 생성
    newPlayer->SetPosition(x, y);

    player = newPlayer;
    UIManager::Instance().SetPlayerInventory(player->GetInventory()); //플레이어가 갖고 있는 인벤토리를 uimanager에 연결

}

int GameObjectManager::GetMapIndexByName(const std::string& mapName) { //맵 이름으로 인덱스 반환
    for (int i = 0; i < (int)maps.size(); i++) {
        if (maps[i].name == mapName)
            return i;
    }
    return -1; // 못 찾으면 -1 반환
}

void GameObjectManager::addPortal(const std::string& mapName, const RECT& rect, int targetMapIndex) //포탈 생성
{
    int index = GetMapIndexByName(mapName); //맵 번호 검사
    if (index != -1) { //동일한 이름의 맵이 없다면 -1
        maps[index].AddPortalRect(rect, targetMapIndex);  //포탈 벡터 추가 도형, 나올 맵 번호
        OutputDebugStringA(("포탈 추가: " + mapName + "\n").c_str());
    }
}

void GameObjectManager::ChangeMap(int index) //맵과 플레이어 시작 위치 변경
{
    if (index >= 0 && index < (int)maps.size()) { //인덱스 범위 확인
        currentMapIndex = index;        //addPortal만들 때 입력한 번호의 맵으로 변경
        player->SetPosition(5, 5); // 새 맵에서 시작 위치 설정
        OutputDebugStringA("맵 전환됨\n");
    }
}

void GameObjectManager::ChangeTile(int x, int y)  //타일 변경
{
    Map& map = currentMap();
    TileData& tiledata = map.getTile(x, y);
    switch (tiledata.tileType)
    {
    case TileType::Path:tiledata.tileType = TileType::Grass; break;
    case TileType::Grass:tiledata.tileType = TileType::Path; break;
    }

}

void GameObjectManager::WaterTile(int x, int y) {
    Map& map = maps[currentMapIndex];  // 현재 맵 가져오기

    int tileIndex = y * map.getWidth() + x;
    if (tileIndex < 0 || tileIndex >= (int)map.mapTiles.size())
        return;

    TileData& tile = map.mapTiles[tileIndex];

    // Path이면 Farmland로 바꾸고, Farmland면 그대로
    if (tile.tileType == TileType::Path) {
        tile.tileType = TileType::Farmland;
    }

    // 작물이 있으면 물 준 상태로 설정
    if (tile.object) {
        Crop* crop = dynamic_cast<Crop*>(tile.object.get());
        if (crop) {
            crop->SetWatered(true);
        }
    }
}


void GameObjectManager::InPortal() //플레이어가 포탈 영역에 있는지 확인 후 맵전환
{
    //플레이어는 픽셀 좌표로 계산한다.
    float px_pixel = player->GetX() * 32;
    float py_pixel = player->GetY() * 32;

    for (const auto& portal : currentMap().GetPortalRects()) { //포탈 정보를 가져옴
        RECT rect = portal.first;  //도형 
        int targetMapIndex = portal.second; // 번호

        //IntersectRect 범위가 너무 안맞으면 사용 예정
        if (px_pixel >= rect.left && px_pixel <= rect.right &&
            py_pixel >= rect.top && py_pixel <= rect.bottom) { //플레이어와 포탈 범위가 닿으면//
            ChangeMap(targetMapIndex); // 저장되있던 번호의 맵으로 이동
            OutputDebugStringA("포탈 감지, 맵 변경\n");
            break;
        }
    }
}

bool GameObjectManager::CheckTile(int TileX, int TileY, ItemCategory type, ToolType tooltype)
{
    OutputDebugStringA("타일 검사 중!\n");
    Map map = currentMap();
    TileData tiledata = map.getTile(TileX, TileY);

    switch (type)
    {
    case ItemCategory::Tool:
        switch (tooltype)
        {
        case ToolType::Hoe:
            if (tiledata.tileType != TileType::None)
            {
                OutputDebugStringA("타일 변경이 가능합니다!\n");
                ChangeTile(TileX, TileY);
            }
            break;
        case ToolType::Watering:
            if (tiledata.tileType == TileType::Path || tiledata.tileType == TileType::Farmland) {
                OutputDebugStringA("물 뿌리는 중!!\n");
               WaterTile(TileX, TileY);
            }
            else {
                OutputDebugStringA("물 못 뿌림!!\n");
            }
            break;
        }
        break;

    case ItemCategory::Placeable:
    case ItemCategory::Seed:
        if (tiledata.object == nullptr)
        {
            OutputDebugStringA("설치가 가능합니다!\n");
            return true;
        }
        OutputDebugStringA("설치 불가!\n"); break;
    }
    return false;
}
//#include "GameObjectManager.h"
//#include "Player.h"
//#include "Box.h"
//#include "WorldMap.h"
//#include "PlayerController.h"
//#include "InventoryComponent.h"
//#include "RenderManager.h"
//#include "InputManager.h"
//#include "House.h"
//#include "Animal.h"
//#include "BitmapManager.h"
//#include "GameObject.h"
//#include <string>
//void GameObjectManager::AddCrop(Crop* crop) { crops.push_back(crop); allObjects.push_back(crop); } //작물
//void GameObjectManager::AddAnimal(Animal* animal) { animals.push_back(animal); allObjects.push_back(animal); }//동물
//void GameObjectManager::AddFence(Fence* fence) { fences.push_back(fence); allObjects.push_back(fence);} //울타리
//
//
//
//GameObjectManager& GameObjectManager::Instance()
//{
//    static GameObjectManager instance;
//    return instance;
//}
//
//void GameObjectManager::Init(HWND hWnd_) {
//    hWnd = hWnd_;
//    InputManager::Instance().Init(hWnd);
//
//    uiController = new InventoryUIController();  //UI컨트롤러 생성
//    inventory = new InventoryComponent();       //엔벤토리 생성
//    inventory->SetUIController(uiController);   //UI컨트롤러 연결
//
//    player = new Player(inventory);    // 플레이어 생성 (인벤토리 주입)
//    controller = new PlayerController(player, inventory);  // 플레이어컨트롤러 생성
//
//    //상자 월드맵, 집, 동물 생성
//    box = new Box(127, 285);  
//    worldMap = new WorldMap();
//    house = new House();
//    animal = new Animal();
//    MyRoomMap* myRoomMap = new MyRoomMap();
//
//    // 렌더링 대상 등록
//    AddGameObject(player);
//    AddGameObject(box);
//    AddGameObject(house);
//    AddGameObject(animal);
//
//    // 전역 접근용 인스턴스 설정
//    SetPlayer(player);
//    AddAnimal(animal);
//    SetPlayerController(controller);
//
//    // 렌더 매니저에  객체 설정
//    RenderManager::Instance().SetBox(box);
//    RenderManager::Instance().SetWorldMap(worldMap);
//    RenderManager::Instance().SetHouse(house);
//    RenderManager::Instance().SetMyRoomMap(myRoomMap);
//}
//
//void GameObjectManager::Update() //업데이트 함수
//{
//    InputManager::Instance().Update();       // 입력 상태 갱신
//    UpdateAll();  // 모든 오브젝트 업데이트
//}
//
//void GameObjectManager::Render(HDC hdc, HWND hWnd)
//{
//    RenderManager::Instance().RenderAll(hdc, hWnd);  // 렌더 매니저 전달
//}
//
//
//Crop* GameObjectManager::GetCropAt(int tileX, int tileY) { //해당 위치 작물 리턴
//    int px = tileX * tileSize;
//    int py = tileY * tileSize;
//    for (Crop* c : crops) {
//        if (c->GetX() == px && c->GetY() == py) return c;
//    }
//
//    return nullptr;
//}
//
//Fence* GameObjectManager::GetFenceAt(int tileX, int tileY)
//{
//    int px = tileX * tileSize;
//    int py = tileY * tileSize;
//    for (Fence* f : fences) {
//        if (f->GetX() == px && f->GetY() == py) return f;
//    }
//    return nullptr;
//}
//
//void GameObjectManager::Release()  //리소스 해제
//{
//    delete animal;
//    delete box;
//    delete house;
//    delete worldMap;
//    delete player;
//    delete inventory;
//    delete controller;
//    animal = nullptr;
//    box = nullptr;
//    house = nullptr;
//    worldMap = nullptr;
//    player = nullptr;
//    inventory = nullptr;
//    controller = nullptr;
//}
//
//void GameObjectManager::AddGameObject(GameObject* obj) // 모든 객체를 allObjects에 등록
//{
//    if (obj)
//        allObjects.push_back(obj);
//}
//
//void GameObjectManager::SetPlayerInsideHouse(bool inside)// 플레이어가 집 안에 있는지 여부 설정
//{
//    playerInsideHouse = inside;
//    for (auto& obj : allObjects) {
//        if (obj)
//            obj->SetActive(obj->IsInsideHouse() == inside);// 집 내부 객체만 활성화
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
//void GameObjectManager::UpdateAll() { //모든 객체 상태를 한 번에 업데이트
//    if (controller)
//        controller->UpdatePlayer();
//
//    for (auto animal : animals)
//        animal->Update();    //동물 
//    for (auto crop : crops)
//        crop->Update();      //작물 
//}
//
//
//
//
//void GameObjectManager::RemoveCrop(Crop* crop) {
//    crops.erase(std::remove(crops.begin(), crops.end(), crop), crops.end());
//}
//void GameObjectManager::RemoveFence(Fence* fence)
//{
//    fences.erase(std::remove(fences.begin(), fences.end(), fence), fences.end());
//}