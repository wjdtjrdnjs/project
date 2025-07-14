#include "RenderManager.h"

Player* RenderManager::player = nullptr; //�÷��̾�
Map* RenderManager::map = nullptr; //��
Box* RenderManager::box = nullptr; //����

std::vector<Crop*> RenderManager::crops;  //�۹�
std::vector<Animal*> RenderManager::animals; //����
std::vector<Fence*> RenderManager::fences; //��Ÿ��(�ӽ�)

void RenderManager::SetPlayer(Player* p) { player = p; }
void RenderManager::SetMap(Map* m) { map = m; }
void RenderManager::SetBox(Box* b) { box = b; }
void RenderManager::AddCrop(Crop* crop) { crops.push_back(crop); }
void RenderManager::AddAnimal(Animal* animal) { animals.push_back(animal); }

void RenderManager::AddFence(Fence* fence) { fences.push_back(fence); } //��Ÿ��(�ӽ�)

void RenderManager::RenderAll(HDC hdc, HWND hWnd)
{
    RECT r;
    GetClientRect(hWnd, &r);
    if (map) map->Render(hdc); //��
    for (auto& crop : crops) crop->Render(hdc); //�۹�
    for (auto& animal : animals) animal->Render(hdc); //���� 
    for (auto& fence : fences) fence->Render(hdc);//��Ÿ��(�ӽ�) 
   // if (box) box->Render(hdc); //�ڽ� 

   /* if (player->IsInventoryOpen()) {
        player->RenderFullInventory(hdc);
    }*/

   // if (box->IsOpen()) box->RenderUI(hdc); //�ڽ� ������ â

    if (player) 
    {
        player->Render(hdc); //�÷��̾�
        player->RenderInventory(hdc, r.right, r.bottom); //�÷��̾� �Ʒ� �κ���� â(����)
    }
}

void RenderManager::UpdateAll() { //��� ��ü ���¸� �� ���� ������Ʈ
    player->PlayerUpdate();  //�÷��̾� 
    for (auto animal : animals)
        animal->Update();    //���� 
    for (auto crop : crops)
        crop->Update();      //�۹� 
}
Crop* RenderManager::GetCropAt(int tileX, int tileY) { //�ش� ��ġ �۹� ����
    int px = tileX * tileSize;
    int py = tileY * tileSize;
    for (Crop* c : crops) {
        if (c->GetX() == px && c->GetY() == py) return c;
    }
    return nullptr;
}

Fence* RenderManager::GetFencepAt(int tileX, int tileY)
{
    int px = tileX * tileSize;
    int py = tileY * tileSize;
    for (Fence* f : fences) {
        if (f->GetX() == px && f->GetY() == py) return f;
    }
    return nullptr;
}

//void RenderManager::RemoveCrop(Crop* crop) { //�۹� ����
//    crops.erase(std::remove(crops.begin(), crops.end(), crop), crops.end());
//}
void RenderManager::RemoveCrop(Crop* crop) {
    crops.erase(std::remove(crops.begin(), crops.end(), crop), crops.end());


}