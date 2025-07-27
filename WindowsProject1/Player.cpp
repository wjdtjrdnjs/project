#define _CRT_SECURE_NO_WARNINGS

#include "Player.h"
#include "BitmapManager.h"
#include "TileData.h"
#include "PlayerInventory.h"


#include "Global.h" //충돌영역 on/off
#include <string>

//#define tileSize 32

Player::Player()
{
    // LoadSprites();
    inventory = new PlayerInventory(); //인벤토리 멤버 저장

    InventoryItem item("딸기씨앗봉투", BitmapManager::Instance().GetCroptBitmap(CropType::strawberryseed)); //인벤토리 슬롯 1번에 딸기씨앗 집어넣음
    inventory->AddItem(0, item);
     item = InventoryItem("양파씨앗봉투", BitmapManager::Instance().GetCroptBitmap(CropType::onionseed)); //양파 씨앗 넣음
    inventory->AddItem(1, item);

    OutputDebugStringA("플레이어 객체 생성완료\n");

}
void Player::Render(HDC hdc, int Tilesize, Direction dir)
{
    HBITMAP hPlayerBmp = BitmapManager::Instance().GetPlayerBitmap(dir);
    if (hPlayerBmp) {
        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, hPlayerBmp);

        const int bmpSize = 32;            // 원래 비트맵 사이즈 (내부 기준)
        const int drawSize = 48;           // 키운 플레이어 사이즈 (예: 48x48)
        const int offsetX = (drawSize - 32) / 2;  // 중앙 정렬
        const int offsetY = (drawSize - 32);      // 발을 타일에 맞추기

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
            // 상호작용
            r.left = (x * 32) - offsetX + 8;
            r.top = (y * 32) - offsetY + 12;
            r.right = r.left + 32;
            r.bottom = r.top + 32;
            b = CreateSolidBrush(RGB(0, 0, 255));
            FrameRect(hdc, &r, b);
            DeleteObject(b);
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

std::vector<RECT> Player::GetCollisionRects() const
{
    {
        RECT r;
        r.left = (x * 32) - 8 + 15;
        r.top = (y * 32) - 8 + 20;
        r.right = r.left + 23;
        r.bottom = r.top + 20;
        return { r };
    }
}

void Player::Update(float deltaTime, bool up, bool down, bool left, bool right)
{
    float dx = 0, dy = 0;
    if (up) dy -= 1;
    if (down) dy += 1;
    if (left) dx -= 1;
    if (right) dx += 1;

    // 대각선 속도 보정 (optional)
    if (dx != 0 && dy != 0) {
        dx *= 0.707f;
        dy *= 0.707f;
    }

    x += dx * speed * deltaTime;
    y += dy * speed * deltaTime;

    // TODO: 충돌 체크 후 위치 보정 필요
}



  

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