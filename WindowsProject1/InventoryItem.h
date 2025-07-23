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

    CropType cropType = CropType::None;  // �۹��� ���
    Tool toolType = Tool::hoe;

    int count = 0;
};
