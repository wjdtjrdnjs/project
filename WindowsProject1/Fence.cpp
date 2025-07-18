#include "Fence.h"
#include "Player.h"
#include "RenderManager.h"
Fence::Fence()
{

    hBmp = BitmapManager::Instance().GetBitmapFence();// itmapManager에서 울타리 비트맵 핸들 받아오기
}
RECT Fence::GetBoundingBox() //울타리 충돌 범위
{
    BITMAP bmpInfo;
    GetObject(hBmp, sizeof(BITMAP), &bmpInfo);

    RECT rect;
    rect.left = x + 10;  // 왼
    rect.top = y;        //위
    rect.right = rect.left + bmpInfo.bmWidth + Fencesize; //오른쪽
    rect.bottom = rect.top + bmpInfo.bmHeight + Fencesize; //아래

    return rect;
}

Fence::~Fence() //울타리 소멸자
{
}
void Fence::Install(int tileX, int tileY, Player* player)
{
    int tool = player->GetSelectedTool();
    InventoryItem* inv = player->GetInventory();
        if (inv[tool].count > 0 && !RenderManager::Instance().GetFenceAt(tileX, tileY)) // 1개 이상이고 위치가 겹치지 않을 때
        {
            Fence* fence = new Fence();  //울타리 생성
            fence->SetPosition(tileX * tileSize, tileY * tileSize); //설치할 위치
            RenderManager::Instance().AddFence(fence);  //울타리 추가
            inv[tool].count--;  // 들고있는 아이템 -1
            if (inv[tool].count == 0) //들고있는 아이템 개수가 0개이다
               inv[tool].type = CropType::None; //아이템이 0개면 빈 슬롯
        }
}

void Fence::Remove(int tileX, int tileY, Player* player)
{
    
    Fence* fence = RenderManager::Instance().GetFenceAt(tileX, tileY); //선택된 타일 위에 무엇이 있는지 확인 
    if (fence) { //울타리가 있으면 실행
        RenderManager::Instance().RemoveFence(fence);  //울타리 삭제
        delete fence;  //메모리 해제
        player->AddItem(CropType::Fence);  //인벤토리에 추가
    }

}

void Fence::Render(HDC hdc)  //울타리 생성
{
    if (!hBmp) return;
    // 임시 메모리 DC 생성
    HDC memDC = CreateCompatibleDC(hdc);
    HGDIOBJ oldBmp = SelectObject(memDC, hBmp);

    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);

    TransparentBlt(hdc,
        x + 10, y,
        bmp.bmWidth + Fencesize, bmp.bmHeight + Fencesize,
        memDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 255, 255)
    );
    // 울타리 충돌 범위 (빨간 테두리)
    RECT r = GetBoundingBox();
    HBRUSH b = CreateSolidBrush(RGB(255, 0, 0));
    FrameRect(hdc, &r, b);
    DeleteObject(b);
    // DC 정리
    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);

}
