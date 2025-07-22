#include "Fence.h"
#include "Player.h"
#include "RenderManager.h"
#include "GameObjectManager.h"
#include "PlayerController.h"
#include "InventoryComponent.h"
#include "InputManager.h"
Fence::Fence()
{
    hBmp = BitmapManager::Instance().GetBitmapFence();// itmapManager���� ��Ÿ�� ��Ʈ�� �ڵ� �޾ƿ���
}
RECT Fence::GetBoundingBox() const //��Ÿ�� �浹 ����
{
    BITMAP bmpInfo;
    GetObject(hBmp, sizeof(BITMAP), &bmpInfo);

    RECT rect;
    rect.left = x + 10;  // ��
    rect.top = y;        //��
    rect.right = rect.left + bmpInfo.bmWidth + Fencesize; //������
    rect.bottom = rect.top + bmpInfo.bmHeight + Fencesize; //�Ʒ�

    return rect;
}

std::vector<RECT> Fence::GetCollisionRects() const
{
    std::vector<RECT> rect;
    rect.push_back(GetBoundingBox());
    return rect;
}



Fence::~Fence() //��Ÿ�� �Ҹ���
{
}

void Fence::Install(int tileX, int tileY, InventoryComponent& inventory)
{
    int tool = InputManager::Instance().GetPressedNumberKey();
    int index = tool - 1;
    if (index >= 0 && index < 9)
    {
        InventoryItem& item = inventory[index];
        if (item.count > 0 && !GameObjectManager::Instance().GetFenceAt(tileX, tileY)) // 1�� �̻��̰� ��ġ�� ��ġ�� ���� ��
        {
            Fence* fence = new Fence();  //��Ÿ�� ����
            fence->SetPosition(tileX * tileSize, tileY * tileSize); //��ġ�� ��ġ
            GameObjectManager::Instance().AddFence(fence);  //��Ÿ�� �߰�
            item.count--;  // ����ִ� ������ -1
            if (item.count == 0) //����ִ� ������ ������ 0���̴�
                item.type = CropType::None; //�������� 0���� �� ����
        }
    }
        
}

void Fence::Remove(int tileX, int tileY, InventoryComponent& inventory)
{
    
    Fence* fence = GameObjectManager::Instance().GetFenceAt(tileX, tileY); //���õ� Ÿ�� ���� ������ �ִ��� Ȯ�� 
    if (fence) { //��Ÿ���� ������ ����
        GameObjectManager::Instance().RemoveFence(fence);  //��Ÿ�� ����
        delete fence;  //�޸� ����
        inventory.AddItem(CropType::Fence);  //�κ��丮�� �߰�
    }

}

void Fence::Render(HDC hdc)  //��Ÿ�� ����
{
    if (!hBmp) return;
    // �ӽ� �޸� DC ����
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
    // ��Ÿ�� �浹 ���� (���� �׵θ�)
    RECT r = GetBoundingBox();
    HBRUSH b = CreateSolidBrush(RGB(255, 0, 0));
    FrameRect(hdc, &r, b);
    DeleteObject(b);
    // DC ����
    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);

}
