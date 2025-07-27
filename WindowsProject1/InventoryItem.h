#pragma once
#include <Windows.h>
#include <string>
// InventoryItem.h
#pragma once
#include <Windows.h>
#include <string>

class InventoryItem {
public:
    InventoryItem() = default;

    InventoryItem(const std::string& name, HBITMAP bitmap)
        : name(name), bitmap(bitmap), valid(true) {
    }

    bool IsValid() const { return valid; }
    std::string GetName() const { return name; }
    HBITMAP GetBitmap() const { return bitmap; }

private:
    std::string name = "";
    HBITMAP bitmap = nullptr;
    bool valid = false;
};
