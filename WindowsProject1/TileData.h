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

// 필요하다면 PlaceableType 도 가능
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
    float x, y;      // 픽셀 좌표 (예: 100.0f, 120.5f)
    float speed;     // 이동 속도
    Direction dir;
};


//작물 성장
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