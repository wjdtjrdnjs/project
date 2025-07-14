#include "Player.h"
#include "InputManager.h" 
#include <iostream>
#include <string>
#include "RenderManager.h"
#include "BitmapManager.h"

Player::Player() : x(50), y(250), selectedCrop(CropType::Strawberry) 
{
    selectedCrop = CropType::None;
    selectedTool = -1;

    // 생성자에서 한 번만 비트맵 로드
    for (int i = 0; i < 4; ++i) {
        HBITMAP player = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_IDLE + i), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR); //플레이어 벙향
        PLY.push_back(player);  //4장

    }
    hBmp = PLY[currentDir];
    for (int i = 0; i < 9; i++) {
        inventory[i].type = CropType::None;
        inventory[i].count = 0;
    }
    inventory[0].type = CropType::Strawberry_1; //1번 딸기봉투와 5개
    inventory[0].count = 5;
    inventory[1].type = CropType::Onion_1;      //2번 양파봉투 5개
    inventory[1].count = 5;
    inventory[2].type = CropType::Stone;        //괭이
    inventory[2].count = 1;
    inventory[3].type = CropType::Fence;        //울타리
    inventory[3].count = 10;
    if (hBmp)
    {
        // 메모리 DC 생성 후 비트맵 선택
        HDC screenDC = GetDC(NULL);
        memDC = CreateCompatibleDC(screenDC);
        ReleaseDC(NULL, screenDC);

        SelectObject(memDC, hBmp);
    }
}

Player::~Player()
{
    if (memDC) DeleteDC(memDC);
    if (hBmp) DeleteObject(hBmp);
}

bool Player::IsInPlayerRange(int tileX, int tileY, int playerX, int playerY)  //플레이어 사거리
{
    int playerTileX = playerX / tileSize;
    int playerTileY = playerY / tileSize;

    return abs(tileX - playerTileX) <= 1 && abs(tileY - playerTileY) <= 1;

}

void Player::RenderInventory(HDC hdc, int screenWidth, int screenHeight)  //플레이어 아래 인벤창(툴바)
{
    int slotSize = 50;
    int startX = 10;
    int startY = screenHeight - slotSize - 10;

    for (int i = 0; i < 9; i++) { //9칸
        HBRUSH brush = nullptr;
        if (i == selectedTool)   //선택된 번호
            brush = CreateSolidBrush(RGB(150, 150, 150)); // 선택된 슬롯 강조
        else
            brush = CreateSolidBrush(RGB(200, 200, 200)); // 기본 색
        
        RECT slotRect = { startX + i * (slotSize + 5)+350, startY, startX + i * (slotSize + 5) + slotSize+350, startY + slotSize };

        FillRect(hdc, &slotRect, brush);
        FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));  // 테두리

        DeleteObject(brush);

        if (inventory[i].type != CropType::None) {
            HBITMAP bmp = BitmapManager::GetBitmapForCrop(inventory[i].type);

           

            HDC memDC = CreateCompatibleDC(hdc);
            HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
            BITMAP bm;
            GetObject(bmp, sizeof(BITMAP), &bm);

            int drawSize = 40;
            int offsetX = slotRect.left + (slotSize - drawSize) / 2;
            int offsetY = slotRect.top + (slotSize - drawSize) / 2;
          
            
            TransparentBlt(hdc,
                offsetX, offsetY,
                drawSize, drawSize, 
                memDC,
                0, 0, 
                bm.bmWidth,
                bm.bmHeight,
                RGB(255, 255, 255));
            std::string countText = std::to_string(inventory[i].count);
            TextOutA(hdc, offsetX + 30, offsetY + 30, countText.c_str(), countText.length());
            SelectObject(memDC, oldBmp);
            DeleteDC(memDC);
        }

    }
}

void Player::AddItem(CropType type) {
    // 이미 존재하는 아이템이면 count 증가
    for (auto& slot : inventory) {
        if (slot.type == type) {
            slot.count++;
            return;
        }
    }

    // 빈 슬롯에 새로 추가
    for (auto& slot : inventory) {
        if (slot.type == CropType::None) {
            slot.type = type;
            slot.count = 1;
            return;
        }
    }

}

void Player::Render(HDC hdc)
{
    if (!hBmp || !memDC)
        return;

    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);

    TransparentBlt(
        hdc,
        x, y,
        bmp.bmWidth+ playersize, bmp.bmHeight+ playersize,
        memDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 255, 255)
    );
}

void Player::PlayerUpdate()
{
    if (isBoxOpen) return;
    Playermove(); //플레이어 이동 처리
    HandleToolSelection(); //아이템창 아래(툴바) 번호 선택
    if (InputManager::IsLeftClickDown()) { //좌클릭
        HandleLeftClickAction();
    }
    if (InputManager::IsRightClickDown()) { //우클릭
        HandleRightClickAction();
    }
    UpdateBitmap(); //비트맵 갱신
  

}

void Player::Playermove()
{
    // 이동 처리
    if (InputManager::IsKeyHeld('A')) {
        x -= 5;
        currentDir = LEFT;
    }
    else if (InputManager::IsKeyHeld('D')) {
        x += 5;
        currentDir = RIGHT;
    }
    else if (InputManager::IsKeyHeld('W')) {
        y -= 5;
        currentDir = UP;
    }
    else if (InputManager::IsKeyHeld('S')) {
        y += 5;
        currentDir = DOWN;
    }
   
}

void Player::HandleToolSelection() {
    if (InputManager::IsKeyDown('1')) selectedTool = 0;      
    else if (InputManager::IsKeyDown('2')) selectedTool = 1;     
    else if (InputManager::IsKeyDown('3')) selectedTool = 2;
    else if (InputManager::IsKeyDown('4')) selectedTool = 3;
    else if (InputManager::IsKeyDown('5')) selectedTool = 4;
    else if (InputManager::IsKeyDown('6')) selectedTool = 5;
    else if (InputManager::IsKeyDown('7')) selectedTool = 6;
    else if (InputManager::IsKeyDown('8')) selectedTool = 7;
    else if (InputManager::IsKeyDown('9')) selectedTool = 8;
}

void Player::HandleLeftClickAction()
{

        POINT pt =  InputManager::GetMousePosition();
         //타일 위치x,y
         int tileX = pt.x / tileSize;
         int tileY = pt.y / tileSize;

         Player* player = RenderManager::GetPlayer();  //플레이어 정보 호출
         if (!player) return; //생성죄지 않았다면 브레이크

         int tool = player->GetSelectedTool();  //선택된 아이템(슬롯)

         //플레이어 범위 x,y
         int playerTileX = (player->GetX() + tileSize / 2) / tileSize;
         int playerTileY = (player->GetY() + tileSize / 2) / tileSize;

         if (abs(tileX - playerTileX) > 1 || abs(tileY - playerTileY) > 1) return;// 범위 밖 클릭 무시

         if (inventory[tool].type == CropType::Stone)  // 괭이일 때만 땅 교체 가능
         {
             Crop* crop = RenderManager::GetCropAt(tileX, tileY);
             if (crop)
             {
                 RenderManager::RemoveCrop(crop);  //땅위에 작물이 있으면 삭제
                 delete crop;
             }
             Map::ToggleTile(tileX, tileY); //땅 교체
         }
         else // 맨손 수확
         {
             PlaceableObject* obj = RenderManager::GetCropAt(tileX, tileY); //해당 좌표에 무엇이 있는지 확인하고 삭제(작물, 울타리)
             if (obj) {

                 obj->Remove(tileX, tileY, player);

             }
            
          
         }
}

void Player::HandleRightClickAction()
{
    POINT pt = InputManager::GetMousePosition();  //마우스가 클릭된 좌표를 가져옴


    //클릭한 타일 위치 
    int tileX = pt.x / tileSize;
    int tileY = pt.y / tileSize;

    Player* player = RenderManager::GetPlayer();//플레이어 정보 호출
    if (!player) return; //플레이어 정보가 존재하지 않는다면 종료
    if (abs(tileX - (player->GetX() + tileSize / 2) / tileSize) > 1 || abs(tileY - (player->GetY() + tileSize / 2) / tileSize) > 1) return;

    PlaceableObject* obj = nullptr;
    int tool = player->GetSelectedTool();
    InventoryItem* inv = player->GetInventory();

    switch (inv[tool].type) {
    case CropType::Onion_1:
        obj = new Crop(CropType::Onion);
        break;
    case CropType::Strawberry_1:
        obj = new Crop(CropType::Strawberry);
        break;
    case CropType::Fence:
        obj = new Fence();
        break;
    }
    
    if (obj) {
        obj->Install(tileX, tileY, player);
    }
   
}

void Player::UpdateBitmap()
{
    // 이미지 핸들 업데이트
    hBmp = PLY[currentDir];
    if (memDC && hBmp) {
        SelectObject(memDC, hBmp);
    }
}
