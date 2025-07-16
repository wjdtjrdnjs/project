#include "Fence.h"
#include "Player.h"
#include "RenderManager.h"
Fence::Fence()
{
    // 생성자에서 한 번만 비트맵 로드
    hBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(image), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBmp)
    {
        // 메모리 DC 생성 후 비트맵 선택
        HDC screenDC = GetDC(NULL);
        memDC = CreateCompatibleDC(screenDC);
        ReleaseDC(NULL, screenDC);

        SelectObject(memDC, hBmp);
    }
}

Fence::~Fence() //동물 소멸자
{
    if (memDC) DeleteDC(memDC);
    if (hBmp) DeleteObject(hBmp);
}

void Fence::Install(int tileX, int tileY, Player* player)
{
    int tool = player->GetSelectedTool();
    InventoryItem* inv = player->GetInventory();
        if (inv[tool].count > 0 && !RenderManager::GetFenceAt(tileX, tileY)) // 1개 이상이고 위치가 겹치지 않을 때
        {
            Fence* fence = new Fence();  //울타리 생성
            fence->SetPosition(tileX * tileSize, tileY * tileSize); //설치할 위치
            RenderManager::AddFence(fence);  //울타리 추가

            inv[tool].count--;  // 들고있는 아이템 -1
            if (inv[tool].count == 0) //들고있는 아이템 개수가 0개이다
               inv[tool].type = CropType::None; //아이템이 0개면 빈 슬롯
        }
}

void Fence::Remove(int tileX, int tileY, Player* player)
{
    
    Fence* fence = RenderManager::GetFenceAt(tileX, tileY); //선택된 타일 위에 무엇이 있는지 확인 
    if (fence) { //울타리가 있으면 실행
        RenderManager::RemoveFence(fence);  //울타리 삭제
        delete fence;  //울타리 삭제
        player->AddItem(CropType::Fence);  //인벤토리에 추가
    }

}

void Fence::Render(HDC hdc)  //울타리 생성
{
    if (!hBmp || !memDC)
        return;

    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);

    TransparentBlt(
        hdc,
        x+10, y,
        bmp.bmWidth + Fencesize, bmp.bmHeight + Fencesize,
        memDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 255, 255)
    );
}
