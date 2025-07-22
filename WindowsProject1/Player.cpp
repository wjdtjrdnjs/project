#include "Player.h"
#include <string>
#include "BitmapManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "InventoryComponent.h"
#include "InventoryItem.h"
#include "PlaceableObject.h"
#include "Direction.h"


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

    // 현재 방향의 비트맵 리스트 가져오기
    auto& bitmaps = playerSprites[currentDir];

    if (bitmaps.empty()) return;


    // 예를 들어 첫 번째 프레임만 사용 (나중에 애니메이션 프레임 관리 가능)
    HBITMAP currentBmp = bitmaps[0];
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
    //플레이어 충돌 박스(빨간 테두리)
    RECT r = GetBoundingBox();
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
    FrameRect(hdc, &r, hBrush);
    DeleteObject(hBrush);

    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}




RECT Player::GetBoundingBox() const // 플레이어 충돌 범위 
{
    // currentDir 키 존재 확인
    if (playerSprites.count(currentDir) == 0) {
        // 키가 없으면 빈 RECT 반환 (필요하면 로그 추가)
        RECT emptyRect = { 0, 0, 0, 0 };
        return emptyRect;
    }

    const auto& frames = playerSprites.at(currentDir);

    // 벡터가 비어있는지 확인
    if (frames.empty()) {
        RECT emptyRect = { 0, 0, 0, 0 };
        return emptyRect;
    }

    HBITMAP currentBmp = frames.at(0);

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
    for (int i = 0; i < 4; ++i) {
        Direction dir = static_cast<Direction>(i);

        // 리소스 ID는 IDB_IDLE, IDB_IDLE + 1, IDB_IDLE + 2, ...
        int resourceId = IDB_IDLE + i;

        HBITMAP bmp = (HBITMAP)LoadImage(
            GetModuleHandle(NULL),
            MAKEINTRESOURCE(resourceId),
            IMAGE_BITMAP,
            0, 0,
            LR_CREATEDIBSECTION);

        if (bmp) {
            playerSprites[dir].push_back(bmp);
        }
        else {
            OutputDebugStringA(("플레이어 비트맵 로드 실패: ID " + std::to_string(resourceId) + "\n").c_str());
        }
    }
}