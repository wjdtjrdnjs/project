#pragma once
#include <Windows.h>
#include <string>
#include "ToolType.h"
#include "TileData.h"
class InventoryItem {
public:
    InventoryItem() : name(""), bitmap(nullptr), count(0), valid(false), //�⺻������
        objectType(ObjectType::None), cropType(CropType::None), toolType(ToolType::None)
    {
    }
    //����� ������
    InventoryItem(const std::string& name,  int count = 1, 
        ObjectType objectType = ObjectType::None,
        CropType cropType = CropType::None,
        ToolType toolType = ToolType::None
    )
        : name(name), count(count), valid(true), objectType(objectType), cropType(cropType), toolType(toolType)
    {
    }

    //�̸��� ���� ������ ��Ʈ���̶� ������Ʈ Ÿ���� �ҷ�������
    // �̸����� ��Ʈ���� �˻�

    bool IsValid() const { return valid; }
    std::string GetName() const { return name; } 
    HBITMAP GetBitmap() const { return bitmap; } //��Ʈ��

    //����
    int GetCount() const { return count; } //����
    void SetCount(int newCount) { count = newCount; }
    void AddCount(int delta) { count += delta; }
    void DecreaseItem(int delta) { count -= delta; }
    //��ȯ
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
