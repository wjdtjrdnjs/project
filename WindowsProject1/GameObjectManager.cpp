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
#include <memory>


void GameObjectManager::Init()
{

    Map& map = currentMap(); // ���� ������ �����´ٰ� ����

    for (int y = 0; y < map.getHeight(); ++y)
    {
        for (int x = 0; x < map.getWidth(); ++x)
        {
            TileData& tile = map.getTile(x,y);

            tile.tileType = TileType::None;
            tile.object = nullptr; // ������Ʈ ����
        }
    }
}

void GameObjectManager::LoadMap(const std::string& mapName)
{
    addPlayer(10, 10);
    addMap(mapName, 40, 19, TileType::Grass);

    // �ʿ� ���� �ٸ� ������Ʈ�� ���� �߰�

        RECT portalToMyroom = { 1260, 350, 1280, 416 }; //��Ż z��ġ ����
        addPortal(mapName, portalToMyroom, 1); //��Ż ����

        // 230, 580, 320, 600
        // 
        //(��Ż�̸�, x,y) ��Ż ���� �� �÷��̾� ��ġ ���� -���� ��-
        //��Ż�� �������� �� �÷��̾� ��ġ ���� -- ���߿� �߰� ���� 


        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                addObjectToCurrentMap(mapName, 10 + i, 7 + j, TileType::Farmland, ObjectType::Crop, CropType::Strawberry);
                addObjectToCurrentMap(mapName, 15 + i, 7 + j, TileType::Farmland, ObjectType::Crop, CropType::Onion);
            }
        }

        addObjectToCurrentMap(mapName, 11, 6, TileType::None, ObjectType::Box);
        addObjectToCurrentMap(mapName, 16, 6, TileType::None, ObjectType::Box);
        addObjectToCurrentMap(mapName, 5, 3, TileType::None, ObjectType::Tree);
        addObjectToCurrentMap(mapName, 3, 10, TileType::None, ObjectType::House);
        addObjectToCurrentMap(mapName, 1, 1, TileType::None, ObjectType::Fence);

        for (int i = 0; i < 32; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                addObjectToCurrentMap(mapName, 8 + i, 11 + j, TileType::Path);
            }
        }
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                addObjectToCurrentMap(mapName, 13 + j, 10 - i, TileType::Path);

            }
        }
        for (int i = 0; i < 6; i++)
        {
            addObjectToCurrentMap(mapName, 12 - i, 13 + i, TileType::Path);
            addObjectToCurrentMap(mapName, 13 - i, 13 + i, TileType::Path);
            addObjectToCurrentMap(mapName, 14 - i, 13 + i, TileType::Path);

        }
}
 

void GameObjectManager::Update(float deltaTime)
{
    player->Update(deltaTime);
}

void GameObjectManager::Render(HDC hdc)
{
    if (!HasMaps()) return;
    maps[currentMapIndex].Render(hdc);

    if (player)
    {
        player->Render(hdc);
        player->GetInventory()->InventoryUIRender(hdc);
    }
}


void GameObjectManager::addMap(const std::string& mapName, int width, int height, TileType type)
{
    Map newMap;
    newMap.name = mapName;
    newMap.initTiles(width, height, type);
    maps.push_back(newMap);
    OutputDebugStringA(("�� ���� " + mapName + "\n").c_str());

    if (maps.size() == 1) //ù���̸� 0���� �ʱ�ȭ
        currentMapIndex = 0;
}

void GameObjectManager::addObjectToCurrentMap(const std::string& mapName, int x, int y, TileType tileType, ObjectType objectType, CropType cropType)
{
    int mapIndex = GetMapIndexByName(mapName);
    if (mapIndex == -1) return; // ���� ������ ����

    Map& map = maps[mapIndex]; //�ε����� ������ ���� �� ����

    int index = y * map.getWidth() + x;
    TileData& tile = map.mapTiles[index]; //���� �� Ÿ�� ����

    if (tileType != TileType::None)  //Ÿ�� none�� �ƴ� �� ����
        tile.tileType = tileType;

    if (objectType != ObjectType::None && !tile.object)
    {
        std::shared_ptr<WorldObject> obj;
        switch (objectType)
        {
        case ObjectType::None:break;
        case ObjectType::Crop:obj = std::make_shared<Crop>(cropType); break;
        case ObjectType::Box:obj = std::make_shared<Box>(); break;
        case ObjectType::Tree:obj = std::make_shared<Tree>(); break;
        case ObjectType::House:obj = std::make_shared<House>(); break;
        case ObjectType::Fence:obj = std::make_shared<Fence>(); break;
        }

        if (obj)
        {
            tile.object = obj;
            obj->SetPosition(x, y);

            OutputDebugStringA("������Ʈ ����\n");


        }
    }
}

void GameObjectManager::addPlayer(int x, int y)  //�÷��̾� ���� �� ��ġ ����
{
    auto newPlayer = std::make_shared<Player>(); //����Ʈ�����ͷ� ����
    newPlayer->SetPosition(x, y);

    player = newPlayer;

}

int GameObjectManager::GetMapIndexByName(const std::string& mapName) { //�� �̸����� �ε��� ��ȯ
    for (int i = 0; i < (int)maps.size(); i++) {
        if (maps[i].name == mapName)
            return i;
    }
    return -1; // �� ã���� -1 ��ȯ
}

void GameObjectManager::addPortal(const std::string& mapName, const RECT& rect, int targetMapIndex) //��Ż ����
{
    int index = GetMapIndexByName(mapName); //�� ��ȣ �˻�
    if (index != -1) { //������ �̸��� ���� ���ٸ� -1
        maps[index].AddPortalRect(rect, targetMapIndex);  //��Ż ���� �߰� ����, ���� �� ��ȣ
        OutputDebugStringA(("��Ż �߰�: " + mapName + "\n").c_str());
    }
}

void GameObjectManager::ChangeMap(int index) //�ʰ� �÷��̾� ���� ��ġ ����
{
    if (index >= 0 && index < (int)maps.size()) { //�ε��� ���� Ȯ��
        currentMapIndex = index;        //addPortal���� �� �Է��� ��ȣ�� ������ ����
        player->SetPosition(5, 5); // �� �ʿ��� ���� ��ġ ����
        OutputDebugStringA("�� ��ȯ��\n");
    }
}


void GameObjectManager::InPortal() //�÷��̾ ��Ż ������ �ִ��� Ȯ�� �� ����ȯ
{
    //�÷��̾�� �ȼ� ��ǥ�� ����Ѵ�.
    float px_pixel = player->GetX() * 32;
    float py_pixel = player->GetY() * 32;

    for (const auto& portal : currentMap().GetPortalRects()) { //��Ż ������ ������
        RECT rect = portal.first;  //���� 
        int targetMapIndex = portal.second; // ��ȣ

        //IntersectRect ������ �ʹ� �ȸ����� ��� ����
        if (px_pixel >= rect.left && px_pixel <= rect.right &&
            py_pixel >= rect.top && py_pixel <= rect.bottom) { //�÷��̾�� ��Ż ������ ������//
            ChangeMap(targetMapIndex); // ������ִ� ��ȣ�� ������ �̵�
            OutputDebugStringA("��Ż ����, �� ����\n");
            break;
        }
    }
}
bool GameObjectManager::CheckTile(int TileX, int TileY, ObjectType type)
{
    OutputDebugStringA("Ÿ�� �˻� ��!\n");
    Map map = currentMap();
    TileData tiledata = map.getTile(TileX, TileY);
    if (tiledata.object == nullptr)
    {
        OutputDebugStringA("��ġ�� �����մϴ�!\n");
        return true;
     }
    OutputDebugStringA("��ġ �Ұ�!\n");

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
//void GameObjectManager::AddCrop(Crop* crop) { crops.push_back(crop); allObjects.push_back(crop); } //�۹�
//void GameObjectManager::AddAnimal(Animal* animal) { animals.push_back(animal); allObjects.push_back(animal); }//����
//void GameObjectManager::AddFence(Fence* fence) { fences.push_back(fence); allObjects.push_back(fence);} //��Ÿ��
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
//    uiController = new InventoryUIController();  //UI��Ʈ�ѷ� ����
//    inventory = new InventoryComponent();       //�����丮 ����
//    inventory->SetUIController(uiController);   //UI��Ʈ�ѷ� ����
//
//    player = new Player(inventory);    // �÷��̾� ���� (�κ��丮 ����)
//    controller = new PlayerController(player, inventory);  // �÷��̾���Ʈ�ѷ� ����
//
//    //���� �����, ��, ���� ����
//    box = new Box(127, 285);  
//    worldMap = new WorldMap();
//    house = new House();
//    animal = new Animal();
//    MyRoomMap* myRoomMap = new MyRoomMap();
//
//    // ������ ��� ���
//    AddGameObject(player);
//    AddGameObject(box);
//    AddGameObject(house);
//    AddGameObject(animal);
//
//    // ���� ���ٿ� �ν��Ͻ� ����
//    SetPlayer(player);
//    AddAnimal(animal);
//    SetPlayerController(controller);
//
//    // ���� �Ŵ�����  ��ü ����
//    RenderManager::Instance().SetBox(box);
//    RenderManager::Instance().SetWorldMap(worldMap);
//    RenderManager::Instance().SetHouse(house);
//    RenderManager::Instance().SetMyRoomMap(myRoomMap);
//}
//
//void GameObjectManager::Update() //������Ʈ �Լ�
//{
//    InputManager::Instance().Update();       // �Է� ���� ����
//    UpdateAll();  // ��� ������Ʈ ������Ʈ
//}
//
//void GameObjectManager::Render(HDC hdc, HWND hWnd)
//{
//    RenderManager::Instance().RenderAll(hdc, hWnd);  // ���� �Ŵ��� ����
//}
//
//
//Crop* GameObjectManager::GetCropAt(int tileX, int tileY) { //�ش� ��ġ �۹� ����
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
//void GameObjectManager::Release()  //���ҽ� ����
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
//void GameObjectManager::AddGameObject(GameObject* obj) // ��� ��ü�� allObjects�� ���
//{
//    if (obj)
//        allObjects.push_back(obj);
//}
//
//void GameObjectManager::SetPlayerInsideHouse(bool inside)// �÷��̾ �� �ȿ� �ִ��� ���� ����
//{
//    playerInsideHouse = inside;
//    for (auto& obj : allObjects) {
//        if (obj)
//            obj->SetActive(obj->IsInsideHouse() == inside);// �� ���� ��ü�� Ȱ��ȭ
//    }
//}
//
//void GameObjectManager::RemoveGameObject(GameObject* obj) {
//    if (!obj) return;
//
//    auto it = std::find(allObjects.begin(), allObjects.end(), obj);
//    if (it != allObjects.end()) {
//        allObjects.erase(it);
//        delete obj; // �����Ҵ�� ������Ʈ�� ���
//    }
//}
//void GameObjectManager::UpdateAll() { //��� ��ü ���¸� �� ���� ������Ʈ
//    if (controller)
//        controller->UpdatePlayer();
//
//    for (auto animal : animals)
//        animal->Update();    //���� 
//    for (auto crop : crops)
//        crop->Update();      //�۹� 
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