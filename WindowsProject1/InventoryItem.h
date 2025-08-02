#pragma once
#include <Windows.h>
#include <string>
#include "ToolType.h"
#include "TileData.h"
class InventoryItem {
public:
    InventoryItem() : name(""), bitmap(nullptr), count(0), valid(false), //�⺻������
        objectType(ObjectType::None), croptype(CropType::None)
    {
    }
    //����� ������
    InventoryItem(const std::string& name, HBITMAP bitmap, int count = 1, ObjectType objectType = ObjectType::None, CropType cropType = CropType::None)
        : name(name), bitmap(bitmap), count(count), valid(true), objectType(objectType), croptype(cropType)
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
    Tool GetToolType() const { return toolType; }
    ObjectType GetObjectType() const { return objectType; }
    CropType GetCropType() const { return croptype; }
private:
    std::string name = "";
    HBITMAP bitmap = nullptr;
    int count = 0;
    bool valid = false;
    Tool toolType = Tool::None;
    ObjectType objectType = ObjectType::None;
    CropType croptype = CropType::None;

};
