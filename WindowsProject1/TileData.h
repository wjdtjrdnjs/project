#pragma once
#include <memory>
#include "Direction.h"
class WorldObject;
enum class TileType 
{  
    None,
    Grass, 
    Farmland,
    Water,
    Path

};
enum class ItemCategory {
    None,
    Tool,
    Crop,
    Seed,
    Placeable
};

enum class ToolType {
    None,
    Hoe,
    Axe,
    Watering
};

enum class CropType {
    None,
    Strawberry,
    Onion
};

enum class SeedType {
    None,
    StrawberrySeed,
    OnionSeed
};

// �ʿ��ϴٸ� PlaceableType �� ����
enum class PlaceableType {
    None,
    Box,
    Fence,
    Tree,
    House,
    Crop,
    NPC
};


struct TileData {
    TileType tileType;
    std::shared_ptr<WorldObject> object = nullptr;
};


struct PlayerData {
    float x, y;      // �ȼ� ��ǥ (��: 100.0f, 120.5f)
    float speed;     // �̵� �ӵ�
    Direction dir;
};


//�۹� ����
//if (isWateredCrop(tile)) {
//    auto crop = std::dynamic_pointer_cast<Crop>(tile.object);
//    crop->grow();
//}
//
//inline bool isWateredCrop(const TileData& tile) {
//    if (tile.object && tile.object->getTypeName() == "Crop") {
//        auto crop = std::dynamic_pointer_cast<Crop>(tile.object);
//        return crop && crop->isWatered;
//    }
//    return false;
//}