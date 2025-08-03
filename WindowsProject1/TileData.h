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
enum class ObjectType
{
    None,
    Crop,
    Box,
    Tree,
    House,
    Fence
};

enum class CropType
{
    None,
    Strawberry,
    Onion,
    strawberryseed,
    onionseed
};

enum class  ToolType {
    None = 0,
    hoe = 1,  //±™¿Ã
    Axe = 2,  //µµ≥¢
    watering = 3 //π∞ª—∏Æ∞≥
};


enum class AllType
{
    None,
    Crop,
    Box,
    Tree,
    House,
    Fence,
    Strawberry,
    Onion,
    strawberryseed,
    onionseed
};
struct TileData {
    TileType tileType;
    std::shared_ptr<WorldObject> object = nullptr;
};


struct PlayerData {
    float x, y;      // «»ºø ¡¬«• (øπ: 100.0f, 120.5f)
    float speed;     // ¿Ãµø º”µµ
    Direction dir;
};


//¿€π∞ º∫¿Â
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