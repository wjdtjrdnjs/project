#include "Gigagenie.h"
#include "WorldObject.h"
#include "Map.h"
#include "Box.h"
#include "Player.h"
#include "Crop.h"
#include "Tree.h"
#include "Direction.h"
#include "Renderable.h"
#include <string>
#include <iostream>

void Gigagenie::addMap(const std::string& mapName, int width, int height)
{
    Map newMap;
    newMap.name = mapName;
    newMap.initTiles(width, height);
    maps.push_back(newMap);
    OutputDebugStringA("�� ����\n");

    if (maps.size() == 1) //ù���̸� 0���� �ʱ�ȭ
        currentMapIndex = 0;
}

void Gigagenie::addObjectToCurrentMap(TileType tileType, ObjectType objectType, int x, int y, CropType cropType)
{
    Map& map = currentMap();

    int index = y * map.getWidth() + x;
    TileData& tile = map.mapTiles[index];

    if (tileType != TileType::None)
        tile.tileType = tileType;

    if (objectType != ObjectType::None && !tile.object)
    {
        std::shared_ptr<WorldObject> obj;
        if (objectType == ObjectType::Box)
        {
            obj = std::make_shared<Box>();  //��ü������ ����Ʈ������ ����
        }
        else if (objectType == ObjectType::Crop)
        {
            obj = std::make_shared<Crop>(cropType); //�۹� Ÿ�԰� �Բ� ��ü������ ����Ʈ������ ����
        }
        else if (objectType == ObjectType::Tree)
        {
            obj = std::make_shared<Tree>();  //��ü������ ����Ʈ������ ����
        }

        /*else if (objectType == ObjectType::Crop)
            obj = std::make_shared<Crop>();*/
        // ... �ٸ� ��ü�� �̾

        if (obj)
        {
            tile.object = obj;
            obj->SetPosition(x, y);  // �ʿ� �� ��ġ ����
        }

    }
}

void Gigagenie::addPlayer(int x, int y)
{
    auto newPlayer = std::make_shared<Player>();
    newPlayer->SetPosition(x, y);

    player = newPlayer;

}

void Gigagenie::SetKeyState(Direction dir, bool pressed)
{

    keyStates[dir] = pressed;

    if (pressed)
        lastPressedDirection = dir;

    SetDirection(lastPressedDirection);  // ���� ����

}
void Gigagenie::SetDirection(Direction dir)//�÷��̾� ���� ��ȯ�� ���� �Լ�
{
    PlayerDirection = dir;

}
void Gigagenie::Update(float deltaTime)
{
    currentMap().Update(deltaTime);
    if (player)  //�����ȵ�
    {
        player->Update(deltaTime, keyUp, keyDown, keyLeft, keyRight); //������ ����
        MovePlayer(deltaTime); //�÷��̾� ������
    }
}
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

void Gigagenie::MovePlayer(float deltaTime)
{
  
    if (player) {
        float speed = 5.0f;
        float dx = 0, dy = 0;

        if (keyStates[lastPressedDirection]) { // ���������� ���� ������ ���� �����ִ���  Ȯ��
            switch (lastPressedDirection) {
            case Direction::UP: dy = -1; break;
            case Direction::DOWN: dy = 1; break;
            case Direction::LEFT: dx = -1; break;
            case Direction::RIGHT: dx = 1; break;
            }

        }
        if(dx== 0 && dy == 0)
            OutputDebugStringA("�÷��̾� �̵�x\n");
        else 
            OutputDebugStringA("�÷��̾� �̵�o\n");


        // �÷��̾��� ���ο� ��ġ ��� (�̵� ���� * �ӵ� * �ð�)
        //Ű ������ ������ dx�� dy�� 0�� �����Ѵ�.
        float newX = player->GetX() + dx * speed * deltaTime;
        float newY = player->GetY() + dy * speed * deltaTime;



        player->SetPosition(newX, newY);
    }

   
}

void Gigagenie::PlayerRender(HDC hdc)
{
   
    if (player)  //64�� �� ������ �÷��̾� ��Ʈ���� �� Ű��Ű �����̴�
            player->Render(hdc, 64 , PlayerDirection);

    
        
}



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
