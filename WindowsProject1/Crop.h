#pragma once
#include "PlaceableObject.h"
#include <windows.h>
#include <vector>
#include "resource.h"
#include "CropType.h"
class PlayerController;

class Crop :public PlaceableObject {
public:
    Crop(CropType type);  //������
    ~Crop();            //�Ҹ���

    int GetX() const { return x; }  //�۹� ��ġ x
    int GetY() const { return y; }  //�۹� ��ġ y

    void Install(int x, int y, InventoryComponent& inventory) override;
    void Remove(int tileX, int tileY, InventoryComponent& inventory) override;
    void Render(HDC hdc);  //�۹� �̹��� ���
    void Update();  // ���� ����
    bool IsFullyGrown() const { return growthStage+1 >= maxGrowthStage; } //�۹� ������ �ִ� �ܰ����� Ȯ�� �Լ�
    void Harvest(); // ��Ȯ �� ó��
    void SetPosition(int x, int y) { this->x = x; this->y = y; }
    CropType GetType() const { return type; }  //���� �۹� Ÿ�� ���� (����, ����)
    int GetGrowthStage() const { return growthStage; } //���� �۹� ���� �ܰ� ���� (��Ȯ�� ���� �Լ�)

private:
    CropType type;     //�۹� Ÿ��(����, ����)
    int x = 0, y = 0;  //�۹� ���� ��ġ
    HBITMAP bitmap; 
    PlayerController* playercon = nullptr;
    int growthStage = 0;          //���� �۹� �ܰ�
    const int maxGrowthStage = 6; //�۹� ���� �ִ� �ܰ�
   
    std::vector<HBITMAP> growthBitmaps; //�۹� ���� �̹���

    int growthTimer = 0;       // ���� �ð�(ms)
    const int growthInterval = 1000; // 5�ʸ��� ���� (���� ����)
};
