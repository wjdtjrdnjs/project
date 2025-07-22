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
        player->SetDirection(LEFT);
    }
    else if (InputManager::Instance().IsKeyHeld('D')) {
        dx = 5;
        player->SetDirection(RIGHT); 
    }
    else if (InputManager::Instance().IsKeyHeld('W')) {
        dy = -5;
        player->SetDirection(UP);
    }
    else if (InputManager::Instance().IsKeyHeld('S')) {
        dy = 5;
        player->SetDirection(DOWN);
    }
    //위치 임시 설정
    player->SetPlusX(dx,dy);

    if (collisionMgr->playerCollided()) { // 충돌 검사
        //충돌이 발생하면 원래 위치로 되돌아감
        player->SetMinusY(dx, dy);
        OutputDebugStringA("충돌 발생\n");
    }
}


void PlayerController::HandleToolSelection() { //번호 선택 함수
    for (int i = 0; i < 9; ++i) {
        if (InputManager::Instance().IsKeyDown('1' + i)) {
            selectedTool = i;
            if (player) {
                player->GetInventory()->SetSelectedTool(selectedTool);  // 선택된 툴을 인벤토리에 전달
                OutputDebugStringA(("Selected slot cha5555555555555nged to: " + std::to_string(i) + "\n").c_str());
                break;
            }
           

        }
    }
}

//코드 수정 필요
void PlayerController::HandleLeftClickAction()//아이템을 들고 좌클릭
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

    //플레이어 위치 좌표 확인용
    std::string debugMsg = "Left Click at (" + std::to_string(pt.x) + ", " + std::to_string(pt.y) + ")\n"; //디버깅 확인용 
    OutputDebugStringA(debugMsg.c_str());  
    
    InventoryComponent* inventory = player->GetInventory();

    if (selectedTool < 0 || selectedTool >= 9) { //selectedTool 범위 체크
        OutputDebugStringA("Selected tool index out of range\n");
        return;
    }
    CropType selectedToolType = (*inventory)[selectedTool].type;
    PlaceableObject* obj = nullptr;
    switch (selectedToolType)
    {
    case CropType::hoe:
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
    case CropType::Axe:
    {
        obj = GameObjectManager::Instance().GetFenceAt(tileX, tileY); //울타리
        if (obj) obj->Remove(tileX, tileY, (*inventory));
        break;
    }
    case CropType::watering:
    {
        GameObjectManager::Instance().GetWorldMap()->ToggleTile(tileX, tileY, 7); //땅 교체
        break;
    }
        
    default:
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
    CropType selectedToolType = (*inventory)[selectedTool].type;
    PlaceableObject* obj = nullptr;

    switch (selectedToolType)
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
    if (obj)  obj->Install(tileX, tileY, (*inventory));
}

void PlayerController::HandleKeyDown(WPARAM wParam)  //사용 XXXXXXXXXXXXXX
{
   
    Box* box = RenderManager::Instance().GetBox();
    if (!box) return;

    //switch (wParam) {
    //case 'E':  // e 키로 상자 열고 닫기
    //{   OutputDebugStringA((std::to_string(1) + "\n").c_str());
    //     box->Open();
    //     box->SetPlayerToolbar(inventory->GetItems());
    // }
    //    break;

    //case VK_ESCAPE:  // ESC 키로 상자 닫기
    //    if (box->IsOpen())
    //        box->Close();
    //    break;
    //}

}


void PlayerController::UpdatePlayer()
{

    if (collisionMgr) collisionMgr->playerCollided();

    if (playerstop) {  //박스 오픈 
        OutputDebugStringA("박스 열림 상태 — 이동 막음\n");
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
        OutputDebugStringA("박스 닫힘 — 이동 가능\n");
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

