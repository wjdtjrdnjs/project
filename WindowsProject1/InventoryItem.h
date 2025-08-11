#pragma once
#include <Windows.h>
#include <string>
#include "ToolType.h"
#include "TileData.h"

class InventoryItem {
public:
    InventoryItem() = default;

    // Tool 
     InventoryItem(ToolType type, int count = 1)
        : category(ItemCategory::Tool), toolType(type), count(count), valid(true) {
    }

    // Seed 
     InventoryItem(SeedType type, int count = 1)
        : category(ItemCategory::Seed), seedType(type), count(count), valid(true) {
    }

    // Crop 
     InventoryItem(CropType type, int count = 1)
        : category(ItemCategory::Crop), cropType(type), count(count), valid(true) {
    }

    // Placeable 
     InventoryItem(PlaceableType type, int count = 1)
        : category(ItemCategory::Placeable), placeableType(type), count(count), valid(true) {
    }


    // �Ӽ� ������ ���xxxx
    std::string GetName() const { return name; }
    HBITMAP GetBitmap() const { return bitmap; }

    //����
    int GetCount() const { return count; }
    void SetCount(int newCount) { count = newCount; }
    void AddCount(int delta) { count += delta; }
    void DecreaseItem(int delta) { count -= delta; }

    //��ȯ
    ItemCategory GetCategory() const { return category; }
    ToolType GetToolType() const { return toolType; }
    SeedType GetSeedType() const { return seedType; }
    CropType GetCropType() const { return cropType; }
    PlaceableType GetPlaceableType() const { return placeableType; }

    bool IsValid() const { return valid; }
    bool IsEmpty() const { return category == ItemCategory::None || count <= 0; }

    // ���� ���� ���� ���x
    bool CanStackWith(const InventoryItem& other) const;
    void Clear();

private:
    std::string name = "";
    HBITMAP bitmap = nullptr;

    int count = 0;
    bool valid = false;

    ItemCategory category = ItemCategory::None;

    // ���� Ÿ�Ե�
    ToolType toolType = ToolType::None;
    SeedType seedType = SeedType::None;
    CropType cropType = CropType::None;
    PlaceableType placeableType = PlaceableType::None;
};
