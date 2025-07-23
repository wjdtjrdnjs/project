#pragma once
#include "PlaceableObject.h"
#include <windows.h>
#include <vector>
#include "resource.h"
#include "CropType.h"
class PlayerController;

class Crop :public PlaceableObject {
public:
    Crop(CropType type);  //생성자
    ~Crop();            //소멸자

    int GetX() const { return x; }  //작물 위치 x
    int GetY() const { return y; }  //작물 위치 y

    void Install(int x, int y, InventoryComponent& inventory) override;
    void Remove(int tileX, int tileY, InventoryComponent& inventory) override;
    void Render(HDC hdc);  //작물 이미지 출력
    void Update();  // 성장 관리
    bool IsFullyGrown() const { return growthStage+1 >= maxGrowthStage; } //작물 성장이 최대 단계인지 확인 함수
    void Harvest(); // 수확 시 처리
    void SetPosition(int x, int y) { this->x = x; this->y = y; }
    CropType GetType() const { return type; }  //현재 작물 타입 리턴 (양파, 딸기)
    int GetGrowthStage() const { return growthStage; } //현재 작물 성장 단계 리턴 (수확을 위한 함수)

private:
    CropType type;     //작물 타입(딸기, 양파)
    int x = 0, y = 0;  //작물 심은 위치
    HBITMAP bitmap; 
    PlayerController* playercon = nullptr;
    int growthStage = 0;          //현재 작물 단계
    const int maxGrowthStage = 6; //작물 성장 최대 단계
   
    std::vector<HBITMAP> growthBitmaps; //작물 성장 이미지

    int growthTimer = 0;       // 누적 시간(ms)
    const int growthInterval = 1000; // 5초마다 성장 (임의 설정)
};
