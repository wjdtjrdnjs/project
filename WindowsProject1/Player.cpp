#define _CRT_SECURE_NO_WARNINGS

#include "Player.h"
#include "BitmapManager.h"
#include "TileData.h"
#include "PlayerInventory.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "Map.h"
#include "CollisionManager.h"

#include "Global.h" //충돌영역 on/off
#include <string>

//#define tileSize 32

Player::Player()
{
    // LoadSprites();
    inventory = new PlayerInventory(); //인벤토리 멤버 저장

    InventoryItem item = InventoryItem("양파씨앗봉투", BitmapManager::Instance().GetCroptBitmap(CropType::onionseed), 3, ObjectType::Crop, CropType::Onion); // 3개
    inventory->AddItem(0, item);
    item = InventoryItem("딸기씨앗봉투", BitmapManager::Instance().GetCroptBitmap(CropType::strawberryseed), 3, ObjectType::Crop, CropType::Strawberry); // 3개
    inventory->AddItem(1, item);
    item = InventoryItem("Fence", BitmapManager::Instance().GetObjectBitmap(ObjectType::Fence), 3, ObjectType::Fence); // 3개
    inventory->AddItem(2, item);


    OutputDebugStringA("플레이어 객체 생성완료\n");

}
void Player::Render(HDC hdc)
{
    HBITMAP hPlayerBmp = BitmapManager::Instance().GetPlayerBitmap(lastPressedDirection);
    if (hPlayerBmp) {
        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, hPlayerBmp);

        const int bmpSize = 32;            // 원래 비트맵 사이즈 (내부 기준)
        const int drawSize = 48;           // 키운 플레이어 사이즈 (예: 48x48)
        const int offsetX = (drawSize - 32) / 2;  // 중앙 정렬
        const int offsetY = (drawSize - 32);      // 발을 타일에 맞추기
        int pixelX = static_cast<int>(x * 32) - offsetX;
        int pixelY = static_cast<int>(y * 32) - offsetY;

        TransparentBlt(
            hdc,
            static_cast<int>(x * 32) - offsetX,
            static_cast<int>(y * 32) - offsetY,
            Tilesize, Tilesize,
            memDC,
            0, 0, bmpSize, bmpSize,
            RGB(255,255,255)
        );

        if (g_bFenceRedFrameOn)
        {
            //박스 충돌영역
            RECT r;
            r.left = (x * 32) - offsetX + 15;
            r.top = (y * 32) - offsetY + 20;
            r.right = r.left + 23;
            r.bottom = r.top + 20;
            HBRUSH b = CreateSolidBrush(RGB(255, 0, 0));
            FrameRect(hdc, &r, b);
            DeleteObject(b);

            auto plusRects = GetPlayerPlusRangeRects(pixelX, pixelY);

            // 빨간색 브러시 생성
            HBRUSH brushPlus = CreateSolidBrush(RGB(0, 255, 0));

            for (const RECT& rect : plusRects) {
                FrameRect(hdc, &rect, brushPlus);
            }
            DeleteObject(brushPlus);

        }
   

        SelectObject(memDC, oldBmp);
        DeleteDC(memDC);
    }
}
void Player::SetPosition(float px, float py)
{
    x = px;
    y = py;
}

RECT Player::GetCollisionRects() const
{
    RECT r;
    const int tileSize = 32;

    // 실제 월드 좌표(px)
    int px = static_cast<int>(x * tileSize);
    int py = static_cast<int>(y * tileSize);

    // 보정값을 상수로 분리하면 의도 파악 쉬움
    const int offsetX = 7;   // 예: 중앙 정렬 보정
    const int offsetY = 12;
    const int width = 23;
    const int height = 20;

    r.left = px + offsetX;
    r.top = py + offsetY;
    r.right = r.left + width;
    r.bottom = r.top + height;

    return { r };
}


void Player::Update(float deltaTime)
{

    MovePlayer(deltaTime);
    //-------위치 점검-------해야함
   //HandleLeftClick(map); //좌클릭
   HandleRightClick(); //우클릭
   

}

void Player::MovePlayer(float deltaTime)
{
    float speed = 7.0f; // px/sec
    float dx = 0.0f, dy = 0.0f;

    HandleInput();  // 방향 입력 상태 갱신

    if (keyUp)    dy -= 1.0f;
    if (keyDown)  dy += 1.0f;
    if (keyLeft)  dx -= 1.0f;
    if (keyRight) dx += 1.0f;

    // 대각선 이동 시 속도 보정 (정규화)
    if (dx != 0.0f && dy != 0.0f)
    {
        const float invSqrt2 = 0.7071f; // 1 / sqrt(2)
        dx *= invSqrt2;
        dy *= invSqrt2;
    }

    float newX = GetX() + dx * speed * deltaTime;
    float newY = GetY() + dy * speed * deltaTime;




   

    SetPosition(newX, newY);
}


void Player::HandleInput()
{
    keyUp = InputManager::Instance().IsKeyHeld('W');
    keyDown = InputManager::Instance().IsKeyHeld('S');
    keyLeft = InputManager::Instance().IsKeyHeld('A');
    keyRight = InputManager::Instance().IsKeyHeld('D');

    // 마지막으로 눌린 키 방향 저장 (애니메이션 등에 활용 가능)
    if (keyUp)        lastPressedDirection = Direction::UP;
    else if (keyDown) lastPressedDirection = Direction::DOWN;
    else if (keyLeft) lastPressedDirection = Direction::LEFT;
    else if (keyRight)lastPressedDirection = Direction::RIGHT;


  

    for (int i = 0; i < 9; ++i) //번호 키 인벤 슬롯
    {
        if (InputManager::Instance().IsKeyDown('1' + i))
        {
            inventory->SetSelectedSlot(i);
            char msg[100];
            snprintf(msg, sizeof(msg), "선택한 슬롯 번호: %d (키: %c)\n", i, '1' + i);
            OutputDebugStringA(msg);
            break; // 한 번에 하나만 처리
        }
    }

}
std::vector<RECT> Player::GetPlayerPlusRangeRects(int playerPixelX, int playerPixelY) //플레이어 작동 범위
{
    std::vector<RECT> rects;

    // 1. 픽셀 좌표 -> 타일 좌표 변환
    int tileX = playerPixelX / 32;
    int tileY = playerPixelY / 32;

    // 2. 중심 타일과 상하좌우 4개 타일 좌표
    std::vector<std::pair<int, int>> plusTiles = {
        {tileX+1, tileY+1},         // 중심
        {tileX+1, tileY},     // 위
        {tileX+1, tileY + 2},     // 아래
        {tileX , tileY+1},     // 왼쪽
        {tileX + 2, tileY+1}      // 오른쪽
    };

    // 3. 각 타일 좌표 -> RECT 변환
    for (auto& t : plusTiles) {
        RECT r;
        r.left = t.first * 32;
        r.top = t.second * 32;
        r.right = r.left + 32;
        r.bottom = r.top + 32;

        rects.push_back(r);
    }

    return rects;
}


//void Player::HandleLeftClick() //좌클릭 사용
//{
//      //오브젝트 제거와 타일 변경으로 사용될 예정
//      
//    //if (InputManager::Instance().IsLeftClickUp())
//    //{
//    //    Tool tool = inventory->GetSelectedTool();
//
//    //    int tileX = static_cast<int>(x);
//    //    int tileY = static_cast<int>(y);
//
//    //    if (tool == Tool::hoe && map.GetTile(tileX, tileY) == TileType::Path) {
//    //        map.SetTile(tileX, tileY, TileType::Farmland);  //타일변경
//    //    }
//    //    else if (tool == Tool::watering && map.GetTile(tileX, tileY) == TileType::Farmland) {
//    //        map.WaterTile(tileX, tileY);  // 작물 성장
//    //    }
//    //    else if (tool == Tool::Axe && map.HasFenceAt(tileX, tileY)) {
//    //        map.RemoveFence(tileX, tileY); //울타리 삭제
//    //    }
//    //}
//}

bool Player::CanInteractAt(int targetPixelX, int targetPixelY)
{
    auto rects = GetPlayerPlusRangeRects(static_cast<int>(x * 32), static_cast<int>(y * 32));
    for (auto& r : rects) {
        if (targetPixelX >= r.left && targetPixelX < r.right &&
            targetPixelY >= r.top && targetPixelY < r.bottom)
            return true;
    }
    return false;
}





void Player::HandleRightClick() //우클릭으로 사용
{
    // 오브젝트 설치 함수로 사용 예정
    if (InputManager::Instance().IsRightClickUp())
    {
        ObjectType type = inventory->GetSelectedObjectType();
        CropType croptype = inventory->GetSelectedCropType();


        POINT p = InputManager::Instance().GetMousePosition();



        int worldX = p.x;
        int worldY = p.y;

        int tileX = worldX / 32;
        int tileY = worldY / 32;

        if (!CanInteractAt(worldX, worldY)) //플레이어 작동 범위
        {
            OutputDebugStringA("작동 범위 밖입니다.\n");
            return; // 범위 밖이면 설치 불가
        }
        
        switch (type)
        {
        case ObjectType::Fence:
        {
            if (GameObjectManager::Instance().CheckTile(tileX, tileY, type)) 
            {//타일체크함수
                OutputDebugStringA("울타리 설치\n");
                GameObjectManager::Instance().addObjectToCurrentMap("Farm", tileX, tileY, TileType::None, ObjectType::Fence);
                inventory->DecreaseItem(1);
            }
            break;
        }
        case ObjectType::Crop:
        {
            if (GameObjectManager::Instance().CheckTile(tileX, tileY, type)) //클릭한 타일의 오브젝트가 nuLL인지 확인
            {
                OutputDebugStringA("작물 설치\n");
                GameObjectManager::Instance().addObjectToCurrentMap("Farm", tileX, tileY, TileType::None, ObjectType::Crop, croptype);
                inventory->DecreaseItem(1); //아이템 수량 감소
            }
           
            break;
        }

        }
       
     
    }
          
}



void Player::SetKeyState(Direction dir, bool pressed)
{

    keyStates[dir] = pressed;

    if (pressed)
        lastPressedDirection = dir;

    SetDirection(lastPressedDirection);  // 방향 갱신

}

void Player::SetDirection(Direction dir)//플레이어 방향 전환을 위한 함수
{
    PlayerDirection = dir;

}

  

//bool Player::IsPlayerOnPortal(float px, float py)
//{
//    const int playerWidth = 32;
//    const int playerHeight = 32;
//
//    // 플레이어 좌표(px, py)는 중심 기준이라고 가정
//    // offsetX, offsetY는 플레이어 충돌박스를 포탈에 맞게 조정하기 위한 보정값
//
//    const int offsetX = 50; // 오른쪽 보정값
//    const int offsetY = 50; // 아래 보정값
//
//    RECT playerRect = {
//        static_cast<LONG>(px - playerWidth / 2 + offsetX),
//        static_cast<LONG>(py - playerHeight / 2 + offsetY),
//        static_cast<LONG>(px + playerWidth / 2 + offsetX),
//        static_cast<LONG>(py + playerHeight / 2 + offsetY)
//    };
//    char buffer[128];
//    sprintf_s(buffer, "플레이어 위치박스: L=%d, T=%d, R=%d, B=%d\n", playerRect.left, playerRect.top, playerRect.right, playerRect.bottom);
//    OutputDebugStringA(buffer);
//    // currentMap의 포탈 리스트를 가지고 있다고 가정
//    for (const auto& portal : currentMap().GetPortalRects()) {
//        const RECT& portalRect = portal.first;
//        int targetMap = portal.second;
//
//        if (playerRect.right >= portalRect.left &&
//            playerRect.left <= portalRect.right &&
//            playerRect.bottom >= portalRect.top &&
//            playerRect.top <= portalRect.bottom) {
//            OutputDebugStringA("포탈 감지: 충돌 성공!\n");
//            return true;
//        }
//    }
//    return false;
//}


//void Player::Render(HDC hdc, int Tilesize)
//{
//    //if (playerSprites.empty()) return;
//
//   // Direction dir = GetDirection();
//    //Tool currentTool = GetEquippedTool();
//
//   // const auto& dirMap = playerSprites.at(currentTool);
//   // const auto& bitmaps = dirMap.at(dir);
//   // HBITMAP currentBmp = nullptr;
//
//  //  currentBmp = bitmaps[0];
//   // if (!currentBmp) return;
//
//  /*  HDC memDC = CreateCompatibleDC(hdc);
//    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, currentBmp);*/
//    HBITMAP hBmp = BitmapManager::Instance().GetPlayerBitmap();
//    if (!hBmp) return;
//
//    BITMAP bmpInfo;
//    GetObject(hBmp, sizeof(bmpInfo), &bmpInfo);
//
//    HDC memDC = CreateCompatibleDC(hdc);
//    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, hBmp);
//
//    int drawSize = 64; // 플레이어 비트맵 높이
//
//    int footToBottom = 8; // 발 위치 조정값, 직접 조절해보세요
//
//    // 플레이어가 tileX, tileY 위치에 있을 때 픽셀 위치 계산
//
//    // Render 함수에서 실제 출력 위치 계산
//    int px = static_cast<int>(pixelX);
//    int py = static_cast<int>(pixelY) - drawSize;
//
//   /* char buf[100];
//    sprintf_s(buf, "pixelY: %d, renderY: %d\n", static_cast<int>(pixelY), py);
//    OutputDebugStringA(buf);*/
//
//    TransparentBlt(hdc, px, py, drawSize, drawSize, memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255));
//
//    SelectObject(memDC, oldBmp);
//    DeleteDC(memDC);
//}
//
//void Player::SetTilePosition(int x, int y)
//{
//    tileX = x;
//    tileY = y;
//    OutputDebugStringA("위치 세팅");
//    // 픽셀 위치는 타일 위치 기준으로 즉시 설정
//    pixelX = tileX * tileSize;
//    pixelY = tileY * tileSize;
//}
//
//ObjectType Player::GetObjectType() const
//{
//    return ObjectType::Player;
//}
//
//
//
//void Player::SetPosition(int px, int py)
//{
//    pixelX = static_cast<float>(px);
//    pixelY = static_cast<float>(py);
//}



//Player::~Player()
//{
//    ReleaseResources();
//}
//
//std::vector<RECT> Player::GetCollisionRects() const
//{
//    //플레이어 여러 충돌 범위가 생길 시 벡터 사용해야함
//    return { GetBoundingBox() };
//}
//
//
//void Player::ReleaseResources()
//{
//    if (hBmp)
//    {
//        DeleteObject(hBmp);
//        hBmp = nullptr;
//    }
//
//    if (memDC)
//    {
//        DeleteDC(memDC);
//        memDC = nullptr;
//    }
//}
//
//
//
//RECT Player::GetBoundingBox() const // 플레이어 충돌 범위 
//{
//    Tool currentTool = GetEquippedTool();
//    Direction currentDir = GetDirection();
//
//    // currentDir 키 존재 확인
//    if (playerSprites.count(currentTool) == 0) {
//        // 키가 없으면 빈 RECT 반환 (필요하면 로그 추가)
//        RECT emptyRect = { 0, 0, 0, 0 };
//        return emptyRect;
//    }
//
//    const auto& dirMap = playerSprites.at(currentTool);
//
//    // 벡터가 비어있는지 확인
//    if (dirMap.count(currentDir) == 0) {
//        RECT emptyRect = { 0, 0, 0, 0 };
//        return emptyRect;
//    }
//    const auto& frames = dirMap.at(currentDir);
//
//    if (frames.empty()) return { 0, 0, 0, 0 };
//    HBITMAP currentBmp = frames[0];
//
//    BITMAP bmp;
//    GetObject(currentBmp, sizeof(BITMAP), &bmp);
//
//    RECT rect;
//    rect.left = x + 24;
//    rect.top = y + 36;
//    rect.right = x + bmp.bmWidth + playerSize - 25;
//    rect.bottom = y + bmp.bmHeight + playerSize - 20;
//
//    return rect;
//}
//
//void Player::LoadSprites()
//{
//    for (int t = 0; t < 4; ++t) { // tool::hoe ~ tool::watering
//        Tool toolType = static_cast<Tool>(t);
//
//        for (int d = 0; d < 4; ++d) { // Direction::DOWN ~ LEFT
//            Direction dir = static_cast<Direction>(d);
//            //for (int f = 0; f < 4; ++f) {
//                int resourceId = GetResourceId(toolType, dir);  // 각 프레임별 리소스 ID
//
//                HBITMAP bmp = (HBITMAP)LoadImage(
//                    GetModuleHandle(NULL),
//                    MAKEINTRESOURCE(resourceId),
//                    IMAGE_BITMAP,
//                    0, 0,
//                    LR_CREATEDIBSECTION);
//
//                if (bmp) playerSprites[toolType][dir].push_back(bmp);
//        }
//    }
//}
//
//int Player::GetResourceId(Tool toolType, Direction dir)
//{
//    // 베이스 ID는 도구별로 다르게 설정
//    switch (toolType) {
//    case Tool::hoe:
//        return IDB_BITMAP45 + static_cast<int>(dir);
//    case Tool::Axe:
//        return IDB_BITMAP35 + static_cast<int>(dir);
//    case Tool::watering:
//        return IDB_BITMAP31 + static_cast<int>(dir);
//    case Tool::None:
//        return IDB_BITMAP27 + static_cast<int>(dir);
//    }
//}