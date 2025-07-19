#include "CollisionManager.h"
#include <windows.h>
#include "GameObjectManager.h"
#include "RenderManager.h"
#include "Box.h"
#include "Player.h"
#include "Fence.h"
#include "House.h"
bool CollisionManager::playerCollided()
{
    Player* player = GameObjectManager::Instance().GetPlayer();
    Box* box = RenderManager::Instance().GetBox();
    House* house = RenderManager::Instance().GetHouse();

    RECT playerBox = GameObjectManager::Instance().GetPlayer()->GetBoundingBox();  //  �÷��̾� �浹 ����
    RECT BoxBox = box->GetBoundingBox(); //���� �浹 ������ ������ 
    RECT houseBox = house->GetBoundingBox(); //�� ��ü �浹 ������ ������

    RECT intersect;


    auto& fences = GameObjectManager::Instance().GetFences();
    for (auto& fence : fences) 
    {
        RECT fenceBox = fence->GetBoundingBox();  //��Ÿ�� �浹 ���� ������ 
        if (IntersectRect(&intersect, &playerBox, &fenceBox)) {//��Ÿ���� �÷��̾ �浹�ߴ��� Ȯ��
            return true; // �浹 �߻�
        };
    }

    if (IntersectRect(&intersect, &playerBox, &BoxBox)) {//���ڿ� �÷��̾ �浹�ߴ��� Ȯ��
            return true; // �浹 �߻�
    }

    if (IntersectRect(&intersect, &playerBox, &houseBox)) {//���� �÷��̾ �浹�ߴ��� Ȯ��
        houseBox = house->GetDoorBoundingBox(); //���� �� �浹 �������� ��ü
        if (IntersectRect(&intersect, &playerBox, &houseBox))//�÷��̾ ���� ��Ҵ� �� Ȯ��
        {
            OutputDebugStringA("�� ���� ����\n");
        }
        return true; // �浹 �߻�
    }
    return false; // �浹 ����
      
}


