#pragma once
#include "Crop.h" 
#include "ToolType.h"
enum class ItemType {
    NONE,
    CROP,
    TOOL
};

struct InventoryItem {
    ItemType itemType = ItemType::NONE;

    CropType cropType = CropType::None;  // 작물일 경우
    Tool toolType = Tool::hoe;

    int count = 0;
};
