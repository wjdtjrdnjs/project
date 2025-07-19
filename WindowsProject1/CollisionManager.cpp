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

    RECT playerBox = GameObjectManager::Instance().GetPlayer()->GetBoundingBox();  //  플레이어 충돌 범위
    RECT BoxBox = box->GetBoundingBox(); //상자 충돌 영역을 가져옴 
    RECT houseBox = house->GetBoundingBox(); //집 전체 충돌 영역을 가져옴

    RECT intersect;


    auto& fences = GameObjectManager::Instance().GetFences();
    for (auto& fence : fences) 
    {
        RECT fenceBox = fence->GetBoundingBox();  //울타리 충돌 영역 가져옴 
        if (IntersectRect(&intersect, &playerBox, &fenceBox)) {//울타리와 플레이어가 충돌했는지 확인
            return true; // 충돌 발생
        };
    }

    if (IntersectRect(&intersect, &playerBox, &BoxBox)) {//상자와 플레이어가 충돌했는지 확인
            return true; // 충돌 발생
    }

    if (IntersectRect(&intersect, &playerBox, &houseBox)) {//집과 플레이어가 충돌했는지 확인
        houseBox = house->GetDoorBoundingBox(); //집의 문 충돌 영역으로 교체
        if (IntersectRect(&intersect, &playerBox, &houseBox))//플레이어가 문에 닿았는 지 확인
        {
            OutputDebugStringA("집 내부 입장\n");
        }
        return true; // 충돌 발생
    }
    return false; // 충돌 없음
      
}


