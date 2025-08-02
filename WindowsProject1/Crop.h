#pragma once
#include "PlaceableObject.h"
#include <windows.h>
#include <vector>
#include "resource.h"
#include "WorldObject.h"
#include "TileData.h"
class PlayerController;
class Player;
class Crop :public WorldObject{
public:
    Crop(CropType type);  //생성자
    void Render(HDC hdc, int Tilesize) override;
    void SetTilePosition(int px, int py) override;
    ObjectType GetObjectType() const override;
    RECT GetCollisionRect();
    //void Interact(Player& player) override;
    // IsRipe() const { return ripe; }

  //  void Harvest()
   // {
        // 나중에 플레이어 인벤토리에 아이템 추가도 가능
        //ripe = false;
        // 사운드 재생, 애니메이션, 경험치 등도 여기에
   // }

    //~Crop();            //소멸자

    //int GetX() const { return x; }  //작물 위치 x
    //int GetY() const { return y; }  //작물 위치 y

    //void Install(int x, int y, InventoryComponent& inventory) override;
    //void Remove(int tileX, int tileY, InventoryComponent& inventory) override;
    //void Update();  // 성장 관리
    //bool IsFullyGrown() const { return growthStage+1 >= maxGrowthStage; } //작물 성장이 최대 단계인지 확인 함수
    //void Harvest(); // 수확 시 처리
    //void SetPosition(int x, int y) { this->x = x; this->y = y; }
    //CropType GetType() const { return type; }  //현재 작물 타입 리턴 (양파, 딸기)
    //int GetGrowthStage() const { return growthStage; } //현재 작물 성장 단계 리턴 (수확을 위한 함수)

private:
    CropType type;     //작물 타입(딸기, 양파)
    int x = 0, y = 0;  //작물 심은 위치
    bool ripe = FALSE;
    HBITMAP bitmap; 
    //PlayerController* playercon = nullptr;
    //int growthStage = 0;          //현재 작물 단계
    //const int maxGrowthStage = 6; //작물 성장 최대 단계
   
    //std::vector<HBITMAP> growthBitmaps; //작물 성장 이미지

    int growthTimer = 0;       // 누적 시간(ms)
    const int growthInterval = 1000; // 5초마다 성장 (임의 설정)
};
