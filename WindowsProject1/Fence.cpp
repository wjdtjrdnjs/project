#include "Fence.h"
#include "Player.h"
#include "RenderManager.h"
Fence::Fence()
{
    // �����ڿ��� �� ���� ��Ʈ�� �ε�
    hBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(image), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBmp)
    {
        // �޸� DC ���� �� ��Ʈ�� ����
        HDC screenDC = GetDC(NULL);
        memDC = CreateCompatibleDC(screenDC);
        ReleaseDC(NULL, screenDC);

        SelectObject(memDC, hBmp);
    }
}

Fence::~Fence() //���� �Ҹ���
{
    if (memDC) DeleteDC(memDC);
    if (hBmp) DeleteObject(hBmp);
}

void Fence::Install(int tileX, int tileY, Player* player)
{
    int tool = player->GetSelectedTool();
    InventoryItem* inv = player->GetInventory();
        if (inv[tool].count > 0 && !RenderManager::GetFencepAt(tileX, tileY)) // 1�� �̻��� ��
        {
            StructureType baseCropType = StructureType::Fence; //ó���� ���
            Fence* fence = new Fence();  //���õ� �۹� ���� ������
            fence->SetPosition(tileX * tileSize, tileY * tileSize); //��ġ�� ��ġ
            RenderManager::AddFence(fence);  //�۹� �߰�

            inv[tool].count--;  // ����ִ� ������ -1
            if (inv[tool].count == 0) //����ִ� ������ ������ 0���̴�
               inv[tool].type = CropType::None; //�������� 0���� �� ����
        }
}

void Fence::Remove(int tileX, int tileY, Player* player)
{
}



void Fence::Render(HDC hdc)  //���� ����
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

