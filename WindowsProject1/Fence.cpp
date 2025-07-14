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
        if (inv[tool].count > 0 && !RenderManager::GetFencepAt(tileX, tileY)) // 1개 이상일 때
        {
            StructureType baseCropType = StructureType::Fence; //처음은 빈손
            Fence* fence = new Fence();  //선택된 작물 정보 가져옴
            fence->SetPosition(tileX * tileSize, tileY * tileSize); //설치할 위치
            RenderManager::AddFence(fence);  //작물 추가

            inv[tool].count--;  // 들고있는 아이템 -1
            if (inv[tool].count == 0) //들고있는 아이템 개수가 0개이다
               inv[tool].type = CropType::None; //아이템이 0개면 빈 슬롯
        }
}

void Fence::Remove(int tileX, int tileY, Player* player)
{
}



void Fence::Render(HDC hdc)  //동물 생성
{
    if (!hBmp || !memDC)
        return;

    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);

    TransparentBlt(
        hdc,
        x, y,
        bmp.bmWidth + Fencesize, bmp.bmHeight + Fencesize,
        memDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 255, 255)
    );
}

void Fence::Update()
{
}

