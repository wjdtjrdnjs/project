#include "InventoryItem.h"

void InventoryItem::Clear()
{
    category = ItemCategory::None;
    toolType = ToolType::None;
    seedType = SeedType::None;
    cropType = CropType::None;
    placeableType = PlaceableType::None;
    count = 0;
    valid = false;
    name = "";
    bitmap = nullptr;
}

bool InventoryItem::CanStackWith(const InventoryItem& other) const
{
    if (category != other.category) return false;

    switch (category) {
    case ItemCategory::Tool:
        return toolType == other.toolType;
    case ItemCategory::Seed:
        return seedType == other.seedType;
    case ItemCategory::Crop:
        return cropType == other.cropType;
    case ItemCategory::Placeable:
        return placeableType == other.placeableType;
    default:
        return false;
    }
}