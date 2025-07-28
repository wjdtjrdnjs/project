#include "Gigagenie.h"
#include "WorldObject.h"
#include "Map.h"
#include "Box.h"
#include "Player.h"
#include "Crop.h"
#include "Tree.h"
#include "House.h"
#include "Direction.h"
#include "House.h"
#include "Renderable.h"
#include "Fence.h"
#include "InputManager.h"
#include <string>
#include <iostream>

void Gigagenie::Update(float deltaTime)
{

    if (player)
    {
        player->Update(deltaTime);
        InPortal(); //��Ż ����

        //-------��ġ ����-------�ؾ���
        player->HandleLeftClick(currentMap()); //��Ŭ��
        player->HandleRightClick(currentMap()); //��Ŭ��
    }

}

void Gigagenie::Render(HDC hdc)
{
    if (!HasMaps()) return;

    maps[currentMapIndex].Render(hdc);
    player->Render(hdc);
 
}

void Gigagenie::addMap(const std::string& mapName, int width, int height, TileType type)
{
    Map newMap;
    newMap.name = mapName;
    newMap.initTiles( width, height , type);
    maps.push_back(newMap);
    OutputDebugStringA(("�� ���� "+ mapName + "\n").c_str());

    if (maps.size() == 1) //ù���̸� 0���� �ʱ�ȭ
        currentMapIndex = 0;
}

void Gigagenie::addObjectToCurrentMap(const std::string& mapName,TileType tileType, ObjectType objectType, int x, int y, CropType cropType)
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
        }
    }
}

void Gigagenie::addPlayer(int x, int y)  //�÷��̾� ���� �� ��ġ ����
{
    auto newPlayer = std::make_shared<Player>(); //����Ʈ�����ͷ� ����
    newPlayer->SetPosition(x, y); 

    player = newPlayer;

}

int Gigagenie::GetMapIndexByName(const std::string& mapName) { //�� �̸����� �ε��� ��ȯ
    for (int i = 0; i < (int)maps.size(); i++) {
        if (maps[i].name == mapName)
            return i;
    }
    return -1; // �� ã���� -1 ��ȯ
}

void Gigagenie::addPortal(const std::string& mapName, const RECT& rect, int targetMapIndex) //��Ż ����
{
    int index = GetMapIndexByName(mapName); //�� ��ȣ �˻�
    if (index != -1) { //������ �̸��� ���� ���ٸ� -1
        maps[index].AddPortalRect(rect, targetMapIndex);  //��Ż ���� �߰� ����, ���� �� ��ȣ
        OutputDebugStringA(("��Ż �߰�: " + mapName + "\n").c_str());
    }
}

void Gigagenie::ChangeMap(int index) //�ʰ� �÷��̾� ���� ��ġ ����
{
    if (index >= 0 && index < (int)maps.size()) { //�ε��� ���� Ȯ��
        currentMapIndex = index;        //addPortal���� �� �Է��� ��ȣ�� ������ ����
        player->SetPosition(5, 5); // �� �ʿ��� ���� ��ġ ����
        OutputDebugStringA("�� ��ȯ��\n");
    }
}

void Gigagenie::InPortal() //�÷��̾ ��Ż ������ �ִ��� Ȯ�� �� ����ȯ
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
//void Gigagenie::Update(float deltaTime)
//{
//    currentMap().Update(deltaTime);
//    if (player)  //�����ȵ�
//    {
//        player->Update(deltaTime, keyUp, keyDown, keyLeft, keyRight); //������ ����
//        MovePlayer(deltaTime); //�÷��̾� ������
//
//        // ��Ż üũ
//        float px_pixel = player->GetX() * 32;
//        float py_pixel = player->GetY() * 32;
//
//        char buffer[256];
//
//        sprintf_s(buffer, "�÷��̾� ��ġ: (%.2f, %.2f)\n", px_pixel, py_pixel);
//        OutputDebugStringA(buffer);
//
//        for (const auto& portal : currentMap().GetPortalRects()) {
//            RECT rect = portal.first;
//            int targetMapIndex = portal.second;
//
//            sprintf_s(buffer, "��Ż ����: left=%d, top=%d, right=%d, bottom=%d, ��ǥ��=%d\n",
//                rect.left, rect.top, rect.right, rect.bottom, targetMapIndex);
//            OutputDebugStringA(buffer);
//
//
//            if (px_pixel >= rect.left && px_pixel <= rect.right &&
//                py_pixel >= rect.top && py_pixel <= rect.bottom) {
//                ChangeMap(targetMapIndex);
//                OutputDebugStringA("��Ż ����, �� ����\n");
//                break;
//            }
//        }
//
//    }
//}

//
//void Gigagenie::OnKeyDown()
//{
//    if (key == 'E') {
//        auto& map = currentMap();
//        auto player = map.GetPlayer();
//
//        int px = static_cast<int>(player->GetX());
//        int py = static_cast<int>(player->GetY());
//
//        // 4���� ��ȣ�ۿ� ���� Ȯ��
//        for (auto [dx, dy] : directions) {
//            int tx = px + dx;
//            int ty = py + dy;
//
//            auto& tile = map.GetTile(tx, ty);
//            if (tile.object) {
//                tile.object->Interact(*player);
//                break;
//            }
//        }
//    }
//}



//
//void Gigagenie::ChangeMapToNext()
//{
//    if (currentMapIndex + 1 < (int)maps.size()) {
//        currentMapIndex++;
//        // �÷��̾� ���� ��ġ �缳��
//        player->SetPosition(50.f, 50.f); // ������ ���� ��ǥ�� �ٲ��ּ���
//        OutputDebugStringA("�� ��ȯ �Ϸ�\n");
//    }
//}







//void Gigagenie::TryHarvestCrop(int x, int y)
//{
//    Map& map = currentMap();
//    if (x < 0 || y < 0 || x >= map.getWidth() || y >= map.getHeight())
//        return;
//
//    TileData& tile = map.getTile(x, y);
//    if (tile.object && tile.object->GetObjectType() == ObjectType::Crop)
//    {
//        auto crop = std::dynamic_pointer_cast<Crop>(tile.object);
//        if (crop && crop->IsRipe()) {
//            crop->Harvest(); // ��Ȯ ó�� (�κ��丮�� �߰� ��)
//            tile.object = nullptr; // �ʿ��� ����
//        }
//    }
//}

//void Gigagenie::MovePlayer(Direction dir)
//{
//    Map& map = currentMap();
//    std::shared_ptr<Player> player = map.GetPlayer();
//
//    if (!player) return;
//
//    int tileX = player->GetTileX();
//    int tileY = player->GetTileY();
//
//    int dx = 0, dy = 0;
//    switch (dir)
//    {
//    case Direction::UP:    dy = -1; break;
//    case Direction::DOWN:  dy = 1;  break;
//    case Direction::LEFT:  dx = -1; break;
//    case Direction::RIGHT: dx = 1;  break;
//    default: return;
//    }
//
//    int newTileX = tileX + dx;
//    int newTileY = tileY + dy;
//
//    // �浹�˻� �Ǵ� �� ��� üũ�� ���⿡ �߰� ����
//
//    player->SetTilePosition(newTileX, newTileY);
//}
