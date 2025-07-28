#pragma once
#include <Windows.h>
#include <string>
#include "ToolType.h"
#include "TileData.h"
class InventoryItem {
public:
    InventoryItem() = default;

    InventoryItem(const std::string& name, HBITMAP bitmap, int count = 1)
        : name(name), bitmap(bitmap), count(count), valid(true) {
    }

    bool IsValid() const { return valid; }
    std::string GetName() const { return name; } 
    HBITMAP GetBitmap() const { return bitmap; } //¹ÙÆ®¸Ê
    int GetCount() const { return count; } //¼ö·®
    void SetCount(int newCount) { count = newCount; }
    void AddCount(int delta) { count += delta; }
    Tool GetToolType() const { return toolType; }
    ObjectType GetObjectType() const { return objectType; }
private:
    std::string name = "";
    HBITMAP bitmap = nullptr;
    int count = 0;
    bool valid = false;
    Tool toolType = Tool::None;
    ObjectType objectType = ObjectType::None;

};
