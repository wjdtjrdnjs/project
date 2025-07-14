#pragma once
#include "Crop.h" 

struct InventoryItem {
    CropType type = CropType::None;
    int count = 0;
};
