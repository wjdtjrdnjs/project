#include "Gigagenie.h"
#include "WorldObject.h"
#include "Map.h"
#include "Box.h"
#include "Player.h"
#include "Crop.h"
#include "Tree.h"
#include "Direction.h"

void Gigagenie::addMap(const std::string& mapName, int width, int height)
{
    Map newMap;
    newMap.name = mapName;
    newMap.initTiles(width, height);
    maps.push_back(newMap);
    OutputDebugStringA("맵 생성\n");

    if (maps.size() == 1) //첫맵이면 0으로 초기화
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
            obj = std::make_shared<Box>();  //객체생성과 스마트포인터 생성
        }
        else if (objectType == ObjectType::Crop)
        {
            obj = std::make_shared<Crop>(cropType); //작물 타입과 함께 객체생성과 스마트포인터 생성
        }
        else if((objectType == ObjectType::Player))
            obj = std::make_shared<Player>(); //작물 타입과 함께 객체생성과 스마트포인터 생성
        else if (objectType == ObjectType::Tree)
        {
            obj = std::make_shared<Tree>();  //객체생성과 스마트포인터 생성
        }

        /*else if (objectType == ObjectType::Crop)
            obj = std::make_shared<Crop>();*/
        // ... 다른 객체도 이어서

        if (obj)
        {
            tile.object = obj;
            obj->SetPosition(x, y);  // 필요 시 위치 설정

            //플레이어가 만들어지면
            if (objectType == ObjectType::Player)
                map.SetPlayer(std::dynamic_pointer_cast<Player>(obj));
        }

    }
}

void Gigagenie::MovePlayer(Direction dir)
{
    Map& map = currentMap();
    std::shared_ptr<Player> player = map.GetPlayer();

    if (!player) return;

    int tileX = player->GetTileX();
    int tileY = player->GetTileY();

    int dx = 0, dy = 0;
    switch (dir)
    {
    case Direction::UP:    dy = -1; break;
    case Direction::DOWN:  dy = 1;  break;
    case Direction::LEFT:  dx = -1; break;
    case Direction::RIGHT: dx = 1;  break;
    default: return;
    }

    int newTileX = tileX + dx;
    int newTileY = tileY + dy;

    // 충돌검사 또는 맵 경계 체크는 여기에 추가 가능

    player->SetTilePosition(newTileX, newTileY);
}
