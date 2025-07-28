#include "Fence.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "TileData.h"
#include "WorldObject.h"


#include "Global.h" //�浹���� on/off

//RECT Fence::GetBoundingBox() const //��Ÿ�� �浹 ����
//{
//    BITMAP bmpInfo;
//    GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
//
//    RECT rect;
//    rect.left = x + 10;  // ��
//    rect.top = y;        //��
//    rect.right = rect.left + bmpInfo.bmWidth + Fencesize; //������
//    rect.bottom = rect.top + bmpInfo.bmHeight + Fencesize; //�Ʒ�
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
    hBmp = BitmapManager::Instance().GetObjectBitmap(ObjectType::Fence); //tmapManager���� ��Ÿ�� ��Ʈ�� �ڵ� �޾ƿ���
}

void Fence::SetTilePosition(int tileX, int tileY)
{
    x = tileX;
    y = tileY;
  
}

void Fence::Render(HDC hdc, int tilesize)
{
    if (!hBmp) return;
    // �ӽ� �޸� DC ����
    int px = tileX * tilesize;
    int py = tileY * tilesize;

    HDC memDC = CreateCompatibleDC(hdc);
    HGDIOBJ oldBmp = SelectObject(memDC, hBmp);

    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);

   

    TransparentBlt(hdc,
        px, py,
        15, 15,
        memDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 255, 255)
    );
    // ��Ÿ�� �浹 ���� (���� �׵θ�)
   /* if (g_bFenceRedFrameOn)
    {
        RECT r = GetBoundingBox();
        HBRUSH b = CreateSolidBrush(RGB(255, 0, 0));
        FrameRect(hdc, &r, b);
        DeleteObject(b);
    }*/

    // DC ����
    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}

ObjectType Fence::GetObjectType() const
{
    return ObjectType::Fence;
}

//void Fence::Install(int tileX, int tileY, InventoryComponent& inventory)
//{
//    int tool = inventory.GetSelectedTool();
//    if (tool >= 0 && tool < 9)
//    {
//        InventoryItem& item = inventory[tool];
//        if (item.count > 0 && !GameObjectManager::Instance().GetFenceAt(tileX, tileY)) // 1�� �̻��̰� ��ġ�� ��ġ�� ���� ��
//        {
//            Fence* fence = new Fence();  //��Ÿ�� ����
//            fence->SetPosition(tileX * tileSize, tileY * tileSize); //��ġ�� ��ġ
//            GameObjectManager::Instance().AddFence(fence);  //��Ÿ�� �߰�
//            item.count--;  // ����ִ� ������ -1
//            if (item.count == 0) //����ִ� ������ ������ 0���̴�
//                item.cropType = CropType::None; //�������� 0���� �� ����
//        }
//    }
//        
//}
//
//void Fence::Remove(int tileX, int tileY, InventoryComponent& inventory)
//{
//    
//    Fence* fence = GameObjectManager::Instance().GetFenceAt(tileX, tileY); //���õ� Ÿ�� ���� ������ �ִ��� Ȯ�� 
//    if (fence) { //��Ÿ���� ������ ����
//        GameObjectManager::Instance().RemoveFence(fence);  //��Ÿ�� ����
//        delete fence;  //�޸� ����
//        inventory.AddItem(CropType::Fence);  //�κ��丮�� �߰�
//    }
//
//}


