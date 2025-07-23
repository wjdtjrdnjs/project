#define _CRT_SECURE_NO_WARNINGS
#include "PlayerController.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "RenderManager.h"
#include "Direction.h"
#include "Player.h"
#include "Fence.h"
#include "Box.h"
#include "WorldMap.h"
#include <string>


void PlayerController::Playermove() //플레이어 이동 처리
{
    int dx = 0, dy = 0;  //이동 방향 값을 저장할 변수
    if (InputManager::Instance().IsKeyHeld('A')) {
        dx = -5;
        player->SetDirection(Direction::LEFT);
    }
    else if (InputManager::Instance().IsKeyHeld('D')) {
        dx = 5;
        player->SetDirection(Direction::RIGHT);
    }
    else if (InputManager::Instance().IsKeyHeld('W')) {
        dy = -5;
        player->SetDirection(Direction::UP);
    }
    else if (InputManager::Instance().IsKeyHeld('S')) {
        dy = 5;
        player->SetDirection(Direction::DOWN);
    }
    //위치 우치 갱신
    player->SetPlusX(dx,dy);

    if (collisionMgr->playerCollided()) { // 충돌이 발생하면 이동 취소
        player->SetMinusY(dx, dy);
    }
}


void PlayerController::HandleToolSelection() { //번호 선택 함수
    for (int i = 0; i < 9; ++i) {
        if (InputManager::Instance().IsKeyDown('1' + i)) {
            selectedTool = i;
            if (player) {
                player->GetInventory()->SetSelectedTool(selectedTool);  // 선택된 툴을 인벤토리컴포넌트에 전달
                UpdatePlayerToolFromInventory(); //선택된 툴 정보를 플레이어한테 전달
                break;
            }
        }
    }
}

//코드 수정 필요
void PlayerController::HandleLeftClickAction() //좌클릭 액션 처리
{
    if (!player) return;
    POINT pt = InputManager::Instance().GetMousePosition();

    //타일 위치x,y
    int tileX = pt.x / tileSize;
    int tileY = pt.y / tileSize;

    //플레이어 범위 x,y
    int playerTileX = (player->GetX() + tileSize / 2) / tileSize;
    int playerTileY = (player->GetY() + tileSize / 2) / tileSize;

    if (abs(tileX - playerTileX) > 1 || abs(tileY - playerTileY) > 1) return;// 범위 밖 클릭 무시

    // 디버깅용 좌표 출력
    std::string debugMsg = "Left Click at (" + std::to_string(pt.x) + ", " + std::to_string(pt.y) + ")\n"; //디버깅 확인용 
    OutputDebugStringA(debugMsg.c_str());  
   
    InventoryComponent* inventory = player->GetInventory(); // 선택된 인벤토리 아이템 확인
    if (selectedTool < 0 || selectedTool >= 9) return; //selectedTool 범위 체크
    InventoryItem item  = (*inventory)[selectedTool];
    PlaceableObject* obj = nullptr;

    switch (item.toolType) //도구 종류에 따른 행돌
    {
    case Tool::hoe: //괭이
    {
        Crop* crop = GameObjectManager::Instance().GetCropAt(tileX, tileY);
        if (crop)
        {
            GameObjectManager::Instance().RemoveCrop(crop);  //땅위에 작물이 있으면 삭제
            delete crop;
        }
        GameObjectManager::Instance().GetWorldMap()->ToggleTile(tileX, tileY, 4); //땅 교체
        break;

    }
    case Tool::Axe: //도끼
    {
        //울타리 제거
        obj = GameObjectManager::Instance().GetFenceAt(tileX, tileY);
        if (obj) obj->Remove(tileX, tileY, (*inventory));
        break;
    }
    case Tool::watering: //물뿌리개
    {
        //땅에 물 주기
        GameObjectManager::Instance().GetWorldMap()->ToggleTile(tileX, tileY, 7);
        break;
    }
        
    default: //도구가 아닌 것
        obj = GameObjectManager::Instance().GetCropAt(tileX, tileY); //작물
        if (obj) obj->Remove(tileX, tileY, (*inventory));
        break;
    }
   
}
void PlayerController::HandleRightClickAction() //아이템을 들고 우클릭
{
    if (!player) return;
    POINT pt = InputManager::Instance().GetMousePosition();  //마우스가 클릭된 좌표를 가져옴

    //클릭한 타일 위치 
    int tileX = pt.x / tileSize;
    int tileY = pt.y / tileSize;

    // 디버깅 출력 좌표확인
    std::string debugMsg = "Right Click at (" + std::to_string(pt.x) + ", " + std::to_string(pt.y) + ")\n";
    OutputDebugStringA(debugMsg.c_str());
    if (abs(tileX - (player->GetX() + tileSize / 2) / tileSize) > 1 || abs(tileY - (player->GetY() + tileSize / 2) / tileSize) > 1) return;


    InventoryComponent* inventory = player->GetInventory(); //인벤토리 정보를 가져옴

    if (selectedTool < 0 || selectedTool >= 9) { //selectedTool 범위 체크
        return;
    }
    InventoryItem item = (*inventory)[selectedTool]; //선택된 아이템
    PlaceableObject* obj = nullptr;
     
    switch (item.cropType) //선택된 아이템 타입
    {
    case CropType::Strawberry_1:
        obj = new Crop(CropType::Strawberry);
        break;
    case CropType::Onion_1:
        obj = new Crop(CropType::Onion);
        break;
    case CropType::Fence:
        obj = new Fence();
        break;
    }
    if (obj)  obj->Install(tileX, tileY, (*inventory)); //타입 확인 후 설치
}


void PlayerController::UpdatePlayerToolFromInventory() //플레이어한테 도구 타입 전달
{
    InventoryItem* ivn = inventory->GetItems(); //인벤토리 객체를 포인터로 받음

    if (ivn[selectedTool].itemType == ItemType::TOOL) //전달받은 인벤토리와 선택된 툴 번호로  도구 타입인지 확인
    {
        player->SetEquippedTool(ivn[selectedTool].toolType);  //플레이어에게 무슨 도구인지 전달
    }
    else
    {
        player->SetEquippedTool(Tool::None); //플레이어에게 도구가 아님을 전달
    }
}


void PlayerController::UpdatePlayer()
{

    if (collisionMgr) collisionMgr->playerCollided(); //충돌감지

    if (playerstop) {  //박스 오픈 
       // OutputDebugStringA("박스 열림 상태 — 이동 막음\n"); //디버깅 확인용
        if (InputManager::Instance().IsLeftClickDown()) {
            POINT pt = InputManager::Instance().GetMousePosition();
            RenderManager::Instance().GetBox()->HandleClick(pt.x, pt.y, 1);
        }
        else if (InputManager::Instance().IsRightClickDown())
        {
            POINT pt = InputManager::Instance().GetMousePosition();
            RenderManager::Instance().GetBox()->HandleClick(pt.x, pt.y, 2);
        }
        return;  // 상자 열렸을 땐 이동 금지
    }
    else
    {
        //OutputDebugStringA("박스 닫힘 — 이동 가능\n"); //디버깅 확인용
        Playermove(); //플레이어 이동 처리
        HandleToolSelection(); //아이템창 아래(툴바) 번호 선택
        if (InputManager::Instance().IsLeftClickDown()) { //좌클릭
            HandleLeftClickAction();
        }
        if (InputManager::Instance().IsRightClickDown()) { //우클릭
            HandleRightClickAction();

        }
    }
   
}

