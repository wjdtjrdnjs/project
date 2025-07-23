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

    // 울타리 충돌 검사
    auto& fences = GameObjectManager::Instance().GetFences();
    for (auto& fence : fences)
    {
        OutputDebugStringA("울타리 충돌 발생\n");

        if (!fence->IsActive()) continue; //비활성화된 울타리

        RECT fenceBox = fence->GetBoundingBox();
        if (IntersectRect(&intersect, &playerBox, &fenceBox))
        {
            collided = true;
        }
    }

    if (!box->IsActive()) return false; //비활성호된 상자
    // 상자 겹침(이동 불가) 검사
    if (IntersectRect(&intersect, &playerBox, &boxBox))
    {
        OutputDebugStringA("박스 충돌 발생\n");
        collided = true;  // 이동 막음
    }
    else if (IsNearBox(playerBox, boxBox, 10))
    {
        box->SetPlayerNear(TRUE); // 10픽셀 이내 접근하면 상자 오픈
    }
    else  
        box->SetPlayerNear(FALSE); //상자 오픈 불가

    if (!house->IsActive()) return collided;  //비활성화된 집

    // 집 충돌 검사
    if (IntersectRect(&intersect, &playerBox, &houseBox))
    {
        OutputDebugStringA("집 충돌 발생\n");

        RECT doorBox = house->GetDoorBoundingBox(); //문 충돌  영역가져옴
        if (IntersectRect(&intersect, &playerBox, &doorBox)) //검사
        {
            WorldMap* worldmap = GameObjectManager::Instance().GetWorldMap(); //객제 
            worldmap->MoveToRegion(1);  //마이룸으로 입장
            GameObjectManager::Instance().SetPlayerInsideHouse(true); 
            OutputDebugStringA("집 내부 입장\n");
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
    //            // 밖으로 나가기
    //            WorldMap* worldmap = GameObjectManager::Instance().GetWorldMap();
    //            worldmap->MoveToRegion(0);  // 바깥 맵 인덱스

    //            GameObjectManager::Instance().SetPlayerInsideHouse(false);
    //            OutputDebugStringA("밖으로 나감\n");
    //        }
    //    }
    //}
    return collided;
}



bool CollisionManager::IsNearBox(const RECT& playerBox, const RECT& boxBox, int distance)
{
    RECT expandedBox = boxBox;
    // 박스 주변으로 distance 만큼 확장
    InflateRect(&expandedBox, distance, distance);

    RECT intersect;
    return IntersectRect(&intersect, &playerBox, &expandedBox);
}

bool CollisionManager::IsTouching(const RECT& a, const RECT& b) {
    // 닿음 = 경계가 맞닿은 상태
    bool horizontalTouch = (a.right == b.left) || (a.left == b.right);
    bool verticalOverlap = !(a.bottom <= b.top || a.top >= b.bottom);

    bool verticalTouch = (a.bottom == b.top) || (a.top == b.bottom);
    bool horizontalOverlap = !(a.right <= b.left || a.left >= b.right);

    return (horizontalTouch && verticalOverlap) || (verticalTouch && horizontalOverlap);
}