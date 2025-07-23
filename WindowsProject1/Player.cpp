#include "Player.h"
#include <string>
#include "BitmapManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "InventoryComponent.h"
#include "InventoryItem.h"
#include "PlaceableObject.h"
#include "Direction.h"

#include "Global.h" //충돌영역 on/off

Player::Player(InventoryComponent* inventoryComponent)
    : inventory(inventoryComponent) 
{
    LoadSprites();
}
Player::~Player()
{
    ReleaseResources();
}

std::vector<RECT> Player::GetCollisionRects() const
{
    //플레이어 여러 충돌 범위가 생길 시 벡터 사용해야함
    return { GetBoundingBox() };
}


void Player::ReleaseResources()
{
    if (hBmp)
    {
        DeleteObject(hBmp);
        hBmp = nullptr;
    }

    if (memDC)
    {
        DeleteDC(memDC);
        memDC = nullptr;
    }
}
void Player::Render(HDC hdc) //플레이어를 화면에 렌더링
{
    if (playerSprites.empty()) return;

    Direction dir = GetDirection();
    Tool currentTool = GetEquippedTool();

    const auto& dirMap = playerSprites.at(currentTool);
    const auto& bitmaps = dirMap.at(dir);
    HBITMAP currentBmp = nullptr;

        currentBmp = bitmaps[0];
    if (!currentBmp) return;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, currentBmp);

    BITMAP bmpInfo;
    GetObject(currentBmp, sizeof(BITMAP), &bmpInfo);

    TransparentBlt(
        hdc,
        x, y,
        bmpInfo.bmWidth + playerSize, bmpInfo.bmHeight + playerSize,
        memDC,
        0, 0,
        bmpInfo.bmWidth, bmpInfo.bmHeight,
        RGB(255, 255, 255)
    );
    if (g_bFenceRedFrameOn)
    {
        //플레이어 충돌 박스(빨간 테두리)
        RECT r = GetBoundingBox();
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        FrameRect(hdc, &r, hBrush);
        DeleteObject(hBrush);
    }
  

    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}




RECT Player::GetBoundingBox() const // 플레이어 충돌 범위 
{
    Tool currentTool = GetEquippedTool();
    Direction currentDir = GetDirection();

    // currentDir 키 존재 확인
    if (playerSprites.count(currentTool) == 0) {
        // 키가 없으면 빈 RECT 반환 (필요하면 로그 추가)
        RECT emptyRect = { 0, 0, 0, 0 };
        return emptyRect;
    }

    const auto& dirMap = playerSprites.at(currentTool);

    // 벡터가 비어있는지 확인
    if (dirMap.count(currentDir) == 0) {
        RECT emptyRect = { 0, 0, 0, 0 };
        return emptyRect;
    }
    const auto& frames = dirMap.at(currentDir);

    if (frames.empty()) return { 0, 0, 0, 0 };
    HBITMAP currentBmp = frames[0];

    BITMAP bmp;
    GetObject(currentBmp, sizeof(BITMAP), &bmp);

    RECT rect;
    rect.left = x + 24;
    rect.top = y + 36;
    rect.right = x + bmp.bmWidth + playerSize - 25;
    rect.bottom = y + bmp.bmHeight + playerSize - 20;

    return rect;
}

void Player::LoadSprites()
{
    for (int t = 0; t < 4; ++t) { // tool::hoe ~ tool::watering
        Tool toolType = static_cast<Tool>(t);

        for (int d = 0; d < 4; ++d) { // Direction::DOWN ~ LEFT
            Direction dir = static_cast<Direction>(d);
            //for (int f = 0; f < 4; ++f) {
                int resourceId = GetResourceId(toolType, dir);  // 각 프레임별 리소스 ID

                HBITMAP bmp = (HBITMAP)LoadImage(
                    GetModuleHandle(NULL),
                    MAKEINTRESOURCE(resourceId),
                    IMAGE_BITMAP,
                    0, 0,
                    LR_CREATEDIBSECTION);

                if (bmp) playerSprites[toolType][dir].push_back(bmp);
        }
    }
}

int Player::GetResourceId(Tool toolType, Direction dir)
{
    // 베이스 ID는 도구별로 다르게 설정
    switch (toolType) {
    case Tool::hoe:
        return IDB_BITMAP45 + static_cast<int>(dir);
    case Tool::Axe:
        return IDB_BITMAP35 + static_cast<int>(dir);
    case Tool::watering:
        return IDB_BITMAP31 + static_cast<int>(dir);
    case Tool::None:
        return IDB_BITMAP27 + static_cast<int>(dir);
    }
}