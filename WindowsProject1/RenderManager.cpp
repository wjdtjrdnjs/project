#include "RenderManager.h"
#include "Animal.h"
#include "House.h"
void RenderManager::SetPlayer(Player* p) { player = p; }
void RenderManager::SetHouse(House* h) { house = h; }
void RenderManager::SetMap(Map* m) { map = m; }
//void RenderManager::SetMyRoomMap(MyRoomMap* mym) { mymap = mym; }
void RenderManager::SetBox(Box* b) { box = b; }
void RenderManager::AddCrop(Crop* crop) { crops.push_back(crop); }
void RenderManager::AddAnimal(Animal* animal) { animals.push_back(animal); }
void RenderManager::AddFence(Fence* fence) { fences.push_back(fence); } //울타리(임시)


void RenderManager::RenderAll(HDC hdc, HWND hWnd)
{
    RECT r;
    GetClientRect(hWnd, &r);
    if (map)map->Render(hdc); //맵
    for (auto& crop : crops) crop->Render(hdc); //작물
   // for (auto& animal : animals) animal->Render(hdc); //동물 
    for (auto& fence : fences) fence->Render(hdc);//울타리(임시) 
    if (box) box->Render(hdc); //박스      
    if (house) house->Render(hdc); //박스  

    if (player)
    {
        player->Render(hdc); //플레이어
        player->RenderInventory(hdc, r.right, r.bottom); //플레이어 아래 인벤토라 창(툴바)
    }

    if (box->IsOpen()) box->RenderUI(hdc); //박스 아이템 창

   //if (player->IsInventoryOpen()) { //
//     player->RenderFullInventory(hdc);
// }
}

void RenderManager::UpdateAll() { //모든 객체 상태를 한 번에 업데이트
    player->UpdatePlayer();  //플레이어 
    for (auto animal : animals)
        animal->Update();    //동물 
    for (auto crop : crops)
        crop->Update();      //작물 
}
Crop* RenderManager::GetCropAt(int tileX, int tileY) { //해당 위치 작물 리턴
    int px = tileX * tileSize;
    int py = tileY * tileSize;
    for (Crop* c : crops) {
        if (c->GetX() == px && c->GetY() == py) return c;
    }
  
    return nullptr;
}

bool RenderManager::playerCollided()
{
    RECT playerBox = player->GetBoundingBox();  //  플레이어 충돌 범위
    RECT intersect;
    for (Fence* f : fences) {
        RECT fenceBox = f->GetBoundingBox();  //울타리 충돌 영역 가져옴 
        if (IntersectRect(&intersect, &playerBox, &fenceBox)) {//울타리와 플레이어가 충돌했는지 확인
            return true; // 충돌 발생
        }
    }
    RECT BoxBox = box->GetBoundingBox(); //상자 충돌 영역을 가져옴 
    if (IntersectRect(&intersect, &playerBox, &BoxBox)) {//상자와 플레이어가 충돌했는지 확인
            return true; // 충돌 발생
    }

    RECT AnimalBox = animals[0]->GetBoundingBox(); //집 전체 충돌 영역을 가져옴
    if (IntersectRect(&intersect, &playerBox, &AnimalBox)) {//집과 플레이어가 충돌했는지 확인
        AnimalBox = animals[0]->GetDoorBoundingBox(); //집의 문 충돌 영역으로 교체
        if (IntersectRect(&intersect, &playerBox, &AnimalBox))//플레이어가 문에 닿았는 지 확인
        {
            OutputDebugStringA("집 내부 입장\n");
        }
        return true; // 충돌 발생
    }
    return false; // 충돌 없음
}



Fence* RenderManager::GetFenceAt(int tileX, int tileY)
{
    int px = tileX * tileSize;
    int py = tileY * tileSize;
    for (Fence* f : fences) {
        if (f->GetX() == px && f->GetY() == py) return f;
    }
    return nullptr;
}


void RenderManager::RemoveCrop(Crop* crop) {
    crops.erase(std::remove(crops.begin(), crops.end(), crop), crops.end());
}
void RenderManager::RemoveFence(Fence* fence)
{
    fences.erase(std::remove(fences.begin(), fences.end(), fence), fences.end());
}
