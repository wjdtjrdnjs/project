#include "CollisionManager.h"
#include <windows.h>
#include "GameObjectManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "WorldMap.h"
#include "Box.h"
#include "Player.h"
#include "Fence.h"
#include "House.h"
bool CollisionManager::playerCollided()
{
    Player* player = GameObjectManager::Instance().GetPlayer();
    Box* box = RenderManager::Instance().GetBox();
    House* house = RenderManager::Instance().GetHouse();

    RECT playerBox = player->GetBoundingBox();
    RECT boxBox = box->GetBoundingBox();
    RECT houseBox = house->GetBoundingBox();

    RECT intersect;

    bool collided = false;

    // ��Ÿ�� �浹 �˻�
    auto& fences = GameObjectManager::Instance().GetFences();
    for (auto& fence : fences)
    {
        OutputDebugStringA("��Ÿ�� �浹 �߻�\n");

        if (!fence->IsActive()) continue; //��Ȱ��ȭ�� ��Ÿ��

        RECT fenceBox = fence->GetBoundingBox();
        if (IntersectRect(&intersect, &playerBox, &fenceBox))
        {
            collided = true;
        }
    }

    if (!box->IsActive()) return false; //��Ȱ��ȣ�� ����
    // ���� ��ħ(�̵� �Ұ�) �˻�
    if (IntersectRect(&intersect, &playerBox, &boxBox))
    {
        OutputDebugStringA("�ڽ� �浹 �߻�\n");
        collided = true;  // �̵� ����
    }
    else if (IsNearBox(playerBox, boxBox, 10))
    {
        box->SetPlayerNear(TRUE); // 10�ȼ� �̳� �����ϸ� ���� ����
    }
    else  
        box->SetPlayerNear(FALSE); //���� ���� �Ұ�

    if (!house->IsActive()) return collided;  //��Ȱ��ȭ�� ��

    // �� �浹 �˻�
    if (IntersectRect(&intersect, &playerBox, &houseBox))
    {
        OutputDebugStringA("�� �浹 �߻�\n");

        RECT doorBox = house->GetDoorBoundingBox(); //�� �浹  ����������
        if (IntersectRect(&intersect, &playerBox, &doorBox)) //�˻�
        {
            WorldMap* worldmap = GameObjectManager::Instance().GetWorldMap(); //���� 
            worldmap->MoveToRegion(1);  //���̷����� ����
            GameObjectManager::Instance().SetPlayerInsideHouse(true); 
            OutputDebugStringA("�� ���� ����\n");
        }
        collided = true;
    }

    //XXXXXXXXXXXXXXXXXXXXXX
    //if (GameObjectManager::Instance().IsPlayerInsideHouse()) {
    //    RECT playerBox = player->GetBoundingBox();

    //    MyRoomMap* mymap = RenderManager::Instance().GetMyRoomMap();
    //    if (mymap) {
    //        RECT doorBox = mymap->GetExitDoorBoundingBox();

    //        if (IntersectRect(&intersect, &playerBox, &doorBox)) {
    //            // ������ ������
    //            WorldMap* worldmap = GameObjectManager::Instance().GetWorldMap();
    //            worldmap->MoveToRegion(0);  // �ٱ� �� �ε���

    //            GameObjectManager::Instance().SetPlayerInsideHouse(false);
    //            OutputDebugStringA("������ ����\n");
    //        }
    //    }
    //}
    return collided;
}



bool CollisionManager::IsNearBox(const RECT& playerBox, const RECT& boxBox, int distance)
{
    RECT expandedBox = boxBox;
    // �ڽ� �ֺ����� distance ��ŭ Ȯ��
    InflateRect(&expandedBox, distance, distance);

    RECT intersect;
    return IntersectRect(&intersect, &playerBox, &expandedBox);
}

bool CollisionManager::IsTouching(const RECT& a, const RECT& b) {
    // ���� = ��谡 �´��� ����
    bool horizontalTouch = (a.right == b.left) || (a.left == b.right);
    bool verticalOverlap = !(a.bottom <= b.top || a.top >= b.bottom);

    bool verticalTouch = (a.bottom == b.top) || (a.top == b.bottom);
    bool horizontalOverlap = !(a.right <= b.left || a.left >= b.right);

    return (horizontalTouch && verticalOverlap) || (verticalTouch && horizontalOverlap);
}