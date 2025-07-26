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
        else if((objectType == ObjectType::Player))
            obj = std::make_shared<Player>(); //�۹� Ÿ�԰� �Բ� ��ü������ ����Ʈ������ ����
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

            //�÷��̾ ���������
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

    // �浹�˻� �Ǵ� �� ��� üũ�� ���⿡ �߰� ����

    player->SetTilePosition(newTileX, newTileY);
}
