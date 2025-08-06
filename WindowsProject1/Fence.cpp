#include "Fence.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "TileData.h"
#include "WorldObject.h"


#include "Global.h" //충돌영역 on/off

//RECT Fence::GetBoundingBox() const //울타리 충돌 범위
//{
//    BITMAP bmpInfo;
//    GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
//
//    RECT rect;
//    rect.left = x + 10;  // 왼
//    rect.top = y;        //위
//    rect.right = rect.left + bmpInfo.bmWidth + Fencesize; //오른쪽
//    rect.bottom = rect.top + bmpInfo.bmHeight + Fencesize; //아래
//
//    return rect;
//}

//std::vector<RECT> Fence::GetCollisionRects() const
//{
//    std::vector<RECT> rect;
//    rect.push_back(GetBoundingBox());
//    return rect;
//}


Fence::Fence()
{
    hBmp = BitmapManager::Instance().GetObjectBitmap(PlaceableType::Fence);
}


void Fence::SetTilePosition(int tileX, int tileY)
{
    x = tileX;
    y = tileY;
  
}

void Fence::Render(HDC hdc, int tilesize)
{
    if (!hBmp) return;
    // 임시 메모리 DC 생성
    int px = tileX * tilesize;
    int py = tileY * tilesize;

    HDC memDC = CreateCompatibleDC(hdc);
    HGDIOBJ oldBmp = SelectObject(memDC, hBmp);

    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);

  

    TransparentBlt(hdc,
        px+ 8, py+10,
        15, 15,
        memDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 255, 255)
    );
    // 울타리 충돌 범위 (빨간 테두리)
   /* if (g_bFenceRedFrameOn)
    {
        RECT r = GetBoundingBox();
        HBRUSH b = CreateSolidBrush(RGB(255, 0, 0));
        FrameRect(hdc, &r, b);
        DeleteObject(b);
    }*/
    if (g_bFenceRedFrameOn)
    {
        RECT r;
        r.left = px + 5;
        r.top = py + 5;
        r.right = r.left + 20;
        r.bottom = r.top + 20;
        HBRUSH red = CreateSolidBrush(RGB(255, 0, 0));
        FrameRect(hdc, &r, red);
        DeleteObject(red);
        //상호작용
        r.left = px;
        r.top = py;
        r.right = r.left + 32;
        r.bottom = r.top + 32;
        HBRUSH green = CreateSolidBrush(RGB(0, 255, 0));
        FrameRect(hdc, &r, green);
        DeleteObject(green);
    }

    // DC 정리
    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}

PlaceableType Fence::GetPlaceableType() const
{
    return PlaceableType::Fence;
}

RECT Fence::GetCollisionRect()
{

    int px = x * 32;
    int py = y * 32;

    RECT r;
    r.left = px + 5;
    r.top = py + 5;
    r.right = r.left + 20;
    r.bottom = r.top + 20;
    return RECT(r);
}

//void Fence::Install(int tileX, int tileY, InventoryComponent& inventory)
//{
//    int tool = inventory.GetSelectedTool();
//    if (tool >= 0 && tool < 9)
//    {
//        InventoryItem& item = inventory[tool];
//        if (item.count > 0 && !GameObjectManager::Instance().GetFenceAt(tileX, tileY)) // 1개 이상이고 위치가 겹치지 않을 때
//        {
//            Fence* fence = new Fence();  //울타리 생성
//            fence->SetPosition(tileX * tileSize, tileY * tileSize); //설치할 위치
//            GameObjectManager::Instance().AddFence(fence);  //울타리 추가
//            item.count--;  // 들고있는 아이템 -1
//            if (item.count == 0) //들고있는 아이템 개수가 0개이다
//                item.cropType = CropType::None; //아이템이 0개면 빈 슬롯
//        }
//    }
//        
//}
//
//void Fence::Remove(int tileX, int tileY, InventoryComponent& inventory)
//{
//    
//    Fence* fence = GameObjectManager::Instance().GetFenceAt(tileX, tileY); //선택된 타일 위에 무엇이 있는지 확인 
//    if (fence) { //울타리가 있으면 실행
//        GameObjectManager::Instance().RemoveFence(fence);  //울타리 삭제
//        delete fence;  //메모리 해제
//        inventory.AddItem(CropType::Fence);  //인벤토리에 추가
//    }
//
//}


