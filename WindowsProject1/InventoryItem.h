#pragma once
#include <Windows.h>
#include <string>
#include "ToolType.h"
#include "TileData.h"
class InventoryItem {
public:
    InventoryItem() : name(""), bitmap(nullptr), count(0), valid(false), //기본생성자
        objectType(ObjectType::None), cropType(CropType::None), toolType(ToolType::None)
    {
    }
    //사용자 생성자
    InventoryItem(const std::string& name,  int count = 1, 
        ObjectType objectType = ObjectType::None,
        CropType cropType = CropType::None,
        ToolType toolType = ToolType::None
    )
        : name(name), count(count), valid(true), objectType(objectType), cropType(cropType), toolType(toolType)
    {
    }

    //이름과 개수 넣으면 비트맵이랑 오브젝트 타입이 불러와지게
    // 이름으로 비트맵을 검색

    bool IsValid() const { return valid; }
    std::string GetName() const { return name; } 
    HBITMAP GetBitmap() const { return bitmap; } //바트맵

    //수량
    int GetCount() const { return count; } //수량
    void SetCount(int newCount) { count = newCount; }
    void AddCount(int delta) { count += delta; }
    void DecreaseItem(int delta) { count -= delta; }
    //반환
    ToolType GetToolType() const { return toolType; }
    ObjectType GetObjectType() const { return objectType; }
    CropType GetCropType() const { return cropType; }
private:
    std::string name = "";
    HBITMAP bitmap = nullptr;
    int count = 0;
    bool valid = false;
    ObjectType objectType = ObjectType::None;
    CropType cropType = CropType::None;
    ToolType toolType = ToolType::None;

};
