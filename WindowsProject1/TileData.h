#pragma once
#include <memory>
class WorldObject;
enum class TileType 
{  
    None,
    Grass, 
    Farmland,
    Water
};
enum class ObjectType
{
    None,
    Crop,
    Box,
    Player,
    Tree
};

enum class CropType
{
    None,
    Strawberry,
    Onion
};
struct TileData {
    TileType tileType;
    std::shared_ptr<WorldObject> object = nullptr;
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