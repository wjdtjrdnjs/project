#define _CRT_SECURE_NO_WARNINGS

#include "Player.h"
#include "BitmapManager.h"
#include "TileData.h"
#include "PlayerInventory.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "Map.h"
#include "Box.h"
#include "CollisionManager.h"
#include "UIManager.h"

#include "Global.h" //충돌영역 on/off
#include <string>
#include <cmath>
constexpr int PLAYER_BMP_ORIGINAL_SIZE = 32;
constexpr int PLAYER_BMP_DRAW_SIZE = 48;
constexpr int PLAYER_OFFSET_X = (PLAYER_BMP_DRAW_SIZE - PLAYER_BMP_ORIGINAL_SIZE) / 2;
constexpr int PLAYER_OFFSET_Y = (PLAYER_BMP_DRAW_SIZE - PLAYER_BMP_ORIGINAL_SIZE);

Player::Player()
{
    // LoadSprites();
    inventory = new PlayerInventory(); //인벤토리 멤버 저장

    InventoryItem item = InventoryItem(SeedType::OnionSeed, 3); // 3개
    inventory->AddItem(0, item);
    item = InventoryItem(SeedType::StrawberrySeed, 3 ); // 3개
    inventory->AddItem(1, item);
    item = InventoryItem(PlaceableType::Fence, 3); // 3개
    inventory->AddItem(2, item);
    item = InventoryItem(ToolType::Axe, 1); // 3개
    inventory->AddItem(3, item);
    item = InventoryItem(ToolType::Hoe, 1); // 3개
    inventory->AddItem(4, item);
    item = InventoryItem(ToolType::Watering, 1); // 3개
    inventory->AddItem(5, item);


    OutputDebugStringA("플레이어 객체 생성완료\n");

}
void Player::Render(HDC hdc)
{
    HBITMAP hPlayerBmp = BitmapManager::Instance().GetPlayerBitmap(lastPressedDirection);
    if (hPlayerBmp) {
        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, hPlayerBmp);

        const int bmpSize = 32;            // 원래 비트맵 사이즈 (내부 기준)
        const int drawSize = 48;           // 키운 플레이어 사이즈 (예: 48x48)
        const int offsetX = (drawSize - 32) / 2;  // 8 (예시)
        const int offsetY = (drawSize - 32);      // 16 (예시)

        int pixelX = GetPixelX() - PLAYER_OFFSET_X;
        int pixelY = GetPixelY() - PLAYER_OFFSET_Y;
        // 그리고 픽셀 단위로 렌더
        TransparentBlt(
            hdc,
            pixelX,
            pixelY,
            PLAYER_BMP_DRAW_SIZE,
            PLAYER_BMP_DRAW_SIZE,
            memDC,
            0, 0, PLAYER_BMP_ORIGINAL_SIZE, PLAYER_BMP_ORIGINAL_SIZE,
            RGB(255, 255, 255)
        );

        if (g_bFenceRedFrameOn)
        {
            //박스 충돌영역
            RECT r;
            r.left = (x * 32) - offsetX + 15;
            r.top = (y * 32) - offsetY + 20;
            r.right = r.left + 23;
            r.bottom = r.top + 20;
            HBRUSH b = CreateSolidBrush(RGB(255, 0, 0));
            FrameRect(hdc, &r, b);
            DeleteObject(b);


              // 빨간색 브러시 생성
            auto plusRects = GetPlayerPlusRangeRects(static_cast<int>(x * 32), static_cast<int>(y * 32));

            HBRUSH brushRed = CreateSolidBrush(RGB(255, 0, 0));   // 빨간색 브러시
            HBRUSH brushGreen = CreateSolidBrush(RGB(0, 255, 0)); // 초록색 브러시

            // 빨간색 프레임: 중심 박스 (plusRects[0])
            FrameRect(hdc, &plusRects[0], brushRed);

            // 초록색 프레임: 주변 4방향 박스
            for (int i = 1; i < plusRects.size(); ++i) {
                FrameRect(hdc, &plusRects[i], brushGreen);
            }
            DeleteObject(brushRed);
            DeleteObject(brushGreen);

        }
   

        SelectObject(memDC, oldBmp);
        DeleteDC(memDC);
    }
}
void Player::SetPosition(float px, float py)
{
    x = px;
    y = py;
}

RECT Player::GetCollisionRects() const
{
    RECT r;
    const int tileSize = 32;

    // 실제 월드 좌표(px)
    int px = static_cast<int>(x * tileSize);
    int py = static_cast<int>(y * tileSize);

    const int offsetX = 7;  
    const int offsetY = 12;
    const int width = 23;
    const int height = 20;

    r.left = px + offsetX;
    r.top = py + offsetY;
    r.right = r.left + width;
    r.bottom = r.top + height;

    return { r };
}


void Player::Update(float deltaTime)
{
    HandleRightClick(); //우클릭
    HandleLeftClick();  //좌클릭
    HandleInput();  // 방향 입력 상태 갱신

    if (isInteracting) return; // UI 열려 있으면 이동 금지
        MovePlayer(deltaTime);

    //여기에 플레이어 마지막 움직임과 좌표를 가져옴
    //-------위치 점검-------해야함
   //HandleLeftClick(map); //좌클릭


}

void Player::MovePlayer(float deltaTime)
{
    float speed = 7.0f; // px/sec
    float dx = 0.0f, dy = 0.0f;


    if (keyUp)    dy -= 1.0f;
    if (keyDown)  dy += 1.0f;
    if (keyLeft)  dx -= 1.0f;
    if (keyRight) dx += 1.0f;

    // 대각선 이동 시 속도 보정 (정규화)
    if (dx != 0.0f && dy != 0.0f)
    {
        const float invSqrt2 = 0.7071f; // 1 / sqrt(2)
        dx *= invSqrt2;
        dy *= invSqrt2;
    }

    float newX = GetX() + dx * speed * deltaTime;
    float newY = GetY() + dy * speed * deltaTime;

    SetPosition(newX, newY);
}


void Player::HandleLeftClick()
{
    if (InputManager::Instance().IsLeftClickDown())
    {
        POINT mousePos = InputManager::Instance().GetMousePosition(); //마우스 좌표
       
        int worldX = mousePos.x;
        int worldY = mousePos.y;

     

        int tileX = worldX / 32;
        int tileY = worldY / 32;

        InventoryItem item = inventory->GetSelectedItem();
        ItemCategory category = item.GetCategory();

        if (UIManager::Instance().IsBoxUIOpen()) {  //박스 열림
            // int slotX = mousePos.x / 32;
             //   int slotY = mousePos.y / 32;
             // 박스 or 플레이어 슬롯 클릭 시에는 다른 처리 차단
            bool clickedOnSlot = UIManager::Instance().GetOpenedBox()->HandleClick(mousePos.x, mousePos.y, 1);
            if (clickedOnSlot) return;

            return; // 슬롯 외 클릭이더라도 무조건 차단
        }
        else
        {
            if (!CanInteractAt(worldX, worldY)) //플레이어 작동 범위
            {
                OutputDebugStringA("작동 범위 밖입니다.\n");
                return; // 범위 밖이면 설치 불가
            }
            switch (item.GetToolType()) //게임오브젝트 매니저로 이동
            {
            case ToolType::Hoe:GameObjectManager::Instance().CheckTile(tileX, tileY, category, ToolType::Hoe); return; //타일 변경
            case ToolType::Axe:OutputDebugStringA("도끼 !!!!!!!\n"); return;
            case ToolType::Watering:GameObjectManager::Instance().CheckTile(tileX, tileY, category, ToolType::Watering); return;

            }

            // 도구들고 좌클릭
            // 툴바 번호를 가져오고 인벤토리[번호] 타입 확인
            // tool일 때만 상호작용
            //
        }
      


        
    }
   

    // 상자가 안 열렸으면 일반 클릭 처리
    //TryPlaceObject();
}

void Player::OpenBox(Box* box)
{
    UIManager::Instance().SetOpenedBox(box);
    isInteracting = true; // 상호작용 상태로 변경
}


void Player::CloseBox()
{
    UIManager::Instance().SetOpenedBox(nullptr);
    isInteracting = false;
}

void Player::TryPlaceObject()
{
}


void Player::HandleInput()
{
    keyUp = InputManager::Instance().IsKeyHeld('W');
    keyDown = InputManager::Instance().IsKeyHeld('S');
    keyLeft = InputManager::Instance().IsKeyHeld('A');
    keyRight = InputManager::Instance().IsKeyHeld('D');

    // 마지막으로 눌린 키 방향 저장 (애니메이션 등에 활용 가능)
    if (keyUp)        lastPressedDirection = Direction::UP; 
    else if (keyDown) lastPressedDirection = Direction::DOWN;
    else if (keyLeft) lastPressedDirection = Direction::LEFT;
    else if (keyRight)lastPressedDirection = Direction::RIGHT;


    if ((InputManager::Instance().IsKeyDown('E') || InputManager::Instance().IsKeyDown(VK_ESCAPE))
        && UIManager::Instance().IsBoxUIOpen())
    {
        OutputDebugStringA("상자 닫음!!!!!!!!!!");
        UIManager::Instance().CloseBoxUI();
        EndInteraction();
        return;
    }

    // 🔻 상호작용 시도: E (닫기 조건 위에서 막아둠)
    if (InputManager::Instance().IsKeyDown('E') && !isInteracting)
    {
        auto facingTile = GetFacingTilePos();
        int tileX = facingTile.first;
        int tileY = facingTile.second;

        if (tileX != -1 && tileY != -1)
        {
            OutputDebugStringA("상자 열림!!!!!!!!!!");

            GameObjectManager::Instance().InteractWithTile(tileX, tileY, *this);
        }
    }
  
    //마우스 휠로 인벤토리 툴바 아이템 선택
    int wheelDir = InputManager::Instance().GetWheelDirection();
    if (wheelDir != 0) {
        OutputDebugStringA("반응 있음\n");
        inventory->MoveSelectedSlot(wheelDir);  // 인벤토리 슬롯 이동
    }

    //카보드 눌림으로 인벤토리 툴바 선택
    for (int i = 0; i < 9; ++i) //번호 키 인벤 슬롯
    {
        if (InputManager::Instance().IsKeyDown('1' + i))
        {
            inventory->SetSelectedSlot(i);
            char msg[100];
            snprintf(msg, sizeof(msg), "선택한 슬롯 번호: %d (키: %c)\n", i, '1' + i);
            OutputDebugStringA(msg);
            break; // 한 번에 하나만 처리
        }
    }

}



std::pair<int, int> Player::GetFacingTilePos() const
{
    auto plusRects = GetPlayerPlusRangeRects(static_cast<int>(x * 32), static_cast<int>(y * 32));
    if (plusRects.empty()) return { -1, -1 };

    RECT targetRect{};
    switch (lastPressedDirection)
    {
    case Direction::UP:    targetRect = plusRects[1]; break;
    case Direction::DOWN:  targetRect = plusRects[2]; break;
    case Direction::LEFT:  targetRect = plusRects[3]; break;
    case Direction::RIGHT: targetRect = plusRects[4]; break;
    default: return { -1, -1 };
    }

    constexpr int TILE_SIZE = 32;
    return { targetRect.left / TILE_SIZE, targetRect.top / TILE_SIZE };
}


std::vector<RECT> Player::GetPlayerPlusRangeRects(int playerPixelX, int playerPixelY) const
{
    std::vector<RECT> rects;

    constexpr int TILE_SIZE = 32;

    int tileX = static_cast<int>(std::round(static_cast<float>(playerPixelX) / TILE_SIZE));
    int tileY = static_cast<int>(std::round(static_cast<float>(playerPixelY) / TILE_SIZE));

    // 주변 타일 오프셋
    const std::vector<std::pair<int, int>> offsets = {
        {0, 0},     // 중심
        {0, -1},    // 위
        {0, 1},     // 아래
        {-1, 0},    // 왼쪽
        {1, 0}      // 오른쪽
    };

    for (auto& offset : offsets) {
        int tx = tileX + offset.first;
        int ty = tileY + offset.second;

        RECT r;
        r.left = tx * TILE_SIZE;
        r.top = ty * TILE_SIZE;
        r.right = r.left + TILE_SIZE;
        r.bottom = r.top + TILE_SIZE;
        rects.push_back(r);
    }

    return rects;
}
bool Player::CanInteractAt(int targetPixelX, int targetPixelY)
{
    auto rects = GetPlayerPlusRangeRects(static_cast<int>(x * 32), static_cast<int>(y * 32));
    for (auto& r : rects) {
        if (targetPixelX >= r.left && targetPixelX < r.right &&
            targetPixelY >= r.top && targetPixelY < r.bottom)
            return true;
    }
    return false;
}

void Player::StartInteraction()
{
    isInteracting = true;
    OutputDebugStringA("상자와 상호작용 시작\n");

    // TODO: UI 열기 로직 추가
}

void Player::EndInteraction()
{
    isInteracting = false;
    OutputDebugStringA("상호작용 종료\n");
    // TODO: UI 닫기 로직 추가
}




void Player::HandleRightClick() //우클릭으로 사용
{
    // 오브젝트 설치 함수로 사용 예정
    if (InputManager::Instance().IsRightClickUp())
    {
     
        
            ///xxxxxxxxxxxxxxxxxxxxxx임시xxxxxxxxxxxxxxxxxxx
            if (UIManager::Instance().IsBoxUIOpen()) {
                POINT mousePos = InputManager::Instance().GetMousePosition();
                // int slotX = mousePos.x / 32;
                 //   int slotY = mousePos.y / 32;

                 // 박스 or 플레이어 슬롯 클릭 시에는 다른 처리 차단
                bool clickedOnSlot = UIManager::Instance().GetOpenedBox()->HandleClick(mousePos.x, mousePos.y, 2);
                if (clickedOnSlot) return;

                return; // 슬롯 외 클릭이더라도 무조건 차단
            }
        // 상자가 안 열렸으면 일반 클릭 처리
        //TryPlaceObject();

        InventoryItem selectedItem = inventory->GetSelectedItem();
        ItemCategory category = selectedItem.GetCategory();

        POINT p = InputManager::Instance().GetMousePosition();


        int worldX = p.x;
        int worldY = p.y;

        int tileX = worldX / 32;
        int tileY = worldY / 32;

        if (!CanInteractAt(worldX, worldY)) //플레이어 작동 범위
        {
            OutputDebugStringA("작동 범위 밖입니다.\n");
            return; // 범위 밖이면 설치 불가
        }
        if (GameObjectManager::Instance().CheckTile(tileX, tileY, category))
        {
            switch (category)
            {
            case ItemCategory::Placeable: //설치 가능한 오브젝트
            {
                PlaceableType placeable = inventory->GetSelectedPlaceable();
                 GameObjectManager::Instance().addObjectToCurrentMap("Farm", tileX, tileY, TileType::None, placeable);
                // 필요한 설치물 처리...
                break;
            }
            case ItemCategory::Seed:  //씨앗봉투 
            {
                SeedType croptype = inventory->GetSelectedSeedType();
                CropType type = CropType::None;

                switch (croptype) //무슨 씨앗봉투인지 감별
                {
                case SeedType::StrawberrySeed:  type = CropType::Strawberry; break;
                case SeedType::OnionSeed:  type = CropType::Onion; break;
                }
                GameObjectManager::Instance().addObjectToCurrentMap("Farm", tileX, tileY, TileType::None, PlaceableType::Crop, type);
               
                // 작물 설치 처리
                break;
            }
            // Tool 등 다른 카테고리도 처리 가능
            }
            inventory->DecreaseItem(1);

        }

        //switch (type)
        //{
        //case PlaceableType::Fence:
        //{
        //    if (GameObjectManager::Instance().CheckTile(tileX, tileY, type))
        //    {//타일체크함수
        //        OutputDebugStringA("울타리 설치\n");
        //        GameObjectManager::Instance().addObjectToCurrentMap("Farm", tileX, tileY, TileType::None, PlaceableType::Fence);
        //        inventory->DecreaseItem(1);
        //    }
        //    break;
        //}
        //case PlaceableType::Crop:
        //{
        //    if (GameObjectManager::Instance().CheckTile(tileX, tileY, type)) //클릭한 타일의 오브젝트가 nuLL인지 확인
        //    {
        //        OutputDebugStringA("작물 설치\n");
        //        GameObjectManager::Instance().addObjectToCurrentMap("Farm", tileX, tileY, TileType::None, PlaceableType::Crop, croptype);
        //        inventory->DecreaseItem(1); //아이템 수량 감소
        //    }

        //    break;
        //}

        //}


    }

}



void Player::SetKeyState(Direction dir, bool pressed)
{

    keyStates[dir] = pressed;

    if (pressed)
        lastPressedDirection = dir;

    SetDirection(lastPressedDirection);  // 방향 갱신

}

void Player::SetDirection(Direction dir)//플레이어 방향 전환을 위한 함수
{
    //PlayerDirection = dir;

}





//void Player::HandleLeftClick() //좌클릭 사용
//{
//      //오브젝트 제거와 타일 변경으로 사용될 예정
//      
//    //if (InputManager::Instance().IsLeftClickUp())
//    //{
//    //    Tool tool = inventory->GetSelectedTool();
//
//    //    int tileX = static_cast<int>(x);
//    //    int tileY = static_cast<int>(y);
//
//    //    if (tool == Tool::hoe && map.GetTile(tileX, tileY) == TileType::Path) {
//    //        map.SetTile(tileX, tileY, TileType::Farmland);  //타일변경
//    //    }
//    //    else if (tool == Tool::watering && map.GetTile(tileX, tileY) == TileType::Farmland) {
//    //        map.WaterTile(tileX, tileY);  // 작물 성장
//    //    }
//    //    else if (tool == Tool::Axe && map.HasFenceAt(tileX, tileY)) {
//    //        map.RemoveFence(tileX, tileY); //울타리 삭제
//    //    }
//    //}
//}



//bool Player::IsPlayerOnPortal(float px, float py)
//{
//    const int playerWidth = 32;
//    const int playerHeight = 32;
//
//    // 플레이어 좌표(px, py)는 중심 기준이라고 가정
//    // offsetX, offsetY는 플레이어 충돌박스를 포탈에 맞게 조정하기 위한 보정값
//
//    const int offsetX = 50; // 오른쪽 보정값
//    const int offsetY = 50; // 아래 보정값
//
//    RECT playerRect = {
//        static_cast<LONG>(px - playerWidth / 2 + offsetX),
//        static_cast<LONG>(py - playerHeight / 2 + offsetY),
//        static_cast<LONG>(px + playerWidth / 2 + offsetX),
//        static_cast<LONG>(py + playerHeight / 2 + offsetY)
//    };
//    char buffer[128];
//    sprintf_s(buffer, "플레이어 위치박스: L=%d, T=%d, R=%d, B=%d\n", playerRect.left, playerRect.top, playerRect.right, playerRect.bottom);
//    OutputDebugStringA(buffer);
//    // currentMap의 포탈 리스트를 가지고 있다고 가정
//    for (const auto& portal : currentMap().GetPortalRects()) {
//        const RECT& portalRect = portal.first;
//        int targetMap = portal.second;
//
//        if (playerRect.right >= portalRect.left &&
//            playerRect.left <= portalRect.right &&
//            playerRect.bottom >= portalRect.top &&
//            playerRect.top <= portalRect.bottom) {
//            OutputDebugStringA("포탈 감지: 충돌 성공!\n");
//            return true;
//        }
//    }
//    return false;
//}


//void Player::Render(HDC hdc, int Tilesize)
//{
//    //if (playerSprites.empty()) return;
//
//   // Direction dir = GetDirection();
//    //Tool currentTool = GetEquippedTool();
//
//   // const auto& dirMap = playerSprites.at(currentTool);
//   // const auto& bitmaps = dirMap.at(dir);
//   // HBITMAP currentBmp = nullptr;
//
//  //  currentBmp = bitmaps[0];
//   // if (!currentBmp) return;
//
//  /*  HDC memDC = CreateCompatibleDC(hdc);
//    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, currentBmp);*/
//    HBITMAP hBmp = BitmapManager::Instance().GetPlayerBitmap();
//    if (!hBmp) return;
//
//    BITMAP bmpInfo;
//    GetObject(hBmp, sizeof(bmpInfo), &bmpInfo);
//
//    HDC memDC = CreateCompatibleDC(hdc);
//    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, hBmp);
//
//    int drawSize = 64; // 플레이어 비트맵 높이
//
//    int footToBottom = 8; // 발 위치 조정값, 직접 조절해보세요
//
//    // 플레이어가 tileX, tileY 위치에 있을 때 픽셀 위치 계산
//
//    // Render 함수에서 실제 출력 위치 계산
//    int px = static_cast<int>(pixelX);
//    int py = static_cast<int>(pixelY) - drawSize;
//
//   /* char buf[100];
//    sprintf_s(buf, "pixelY: %d, renderY: %d\n", static_cast<int>(pixelY), py);
//    OutputDebugStringA(buf);*/
//
//    TransparentBlt(hdc, px, py, drawSize, drawSize, memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255));
//
//    SelectObject(memDC, oldBmp);
//    DeleteDC(memDC);
//}
//
//void Player::SetTilePosition(int x, int y)
//{
//    tileX = x;
//    tileY = y;
//    OutputDebugStringA("위치 세팅");
//    // 픽셀 위치는 타일 위치 기준으로 즉시 설정
//    pixelX = tileX * tileSize;
//    pixelY = tileY * tileSize;
//}
//
//PlaceableType Player::GetPlaceableType() const
//{
//    return PlaceableType::Player;
//}
//
//
//
//void Player::SetPosition(int px, int py)
//{
//    pixelX = static_cast<float>(px);
//    pixelY = static_cast<float>(py);
//}



//Player::~Player()
//{
//    ReleaseResources();
//}
//
//std::vector<RECT> Player::GetCollisionRects() const
//{
//    //플레이어 여러 충돌 범위가 생길 시 벡터 사용해야함
//    return { GetBoundingBox() };
//}
//
//
//void Player::ReleaseResources()
//{
//    if (hBmp)
//    {
//        DeleteObject(hBmp);
//        hBmp = nullptr;
//    }
//
//    if (memDC)
//    {
//        DeleteDC(memDC);
//        memDC = nullptr;
//    }
//}
//
//
//
//RECT Player::GetBoundingBox() const // 플레이어 충돌 범위 
//{
//    Tool currentTool = GetEquippedTool();
//    Direction currentDir = GetDirection();
//
//    // currentDir 키 존재 확인
//    if (playerSprites.count(currentTool) == 0) {
//        // 키가 없으면 빈 RECT 반환 (필요하면 로그 추가)
//        RECT emptyRect = { 0, 0, 0, 0 };
//        return emptyRect;
//    }
//
//    const auto& dirMap = playerSprites.at(currentTool);
//
//    // 벡터가 비어있는지 확인
//    if (dirMap.count(currentDir) == 0) {
//        RECT emptyRect = { 0, 0, 0, 0 };
//        return emptyRect;
//    }
//    const auto& frames = dirMap.at(currentDir);
//
//    if (frames.empty()) return { 0, 0, 0, 0 };
//    HBITMAP currentBmp = frames[0];
//
//    BITMAP bmp;
//    GetObject(currentBmp, sizeof(BITMAP), &bmp);
//
//    RECT rect;
//    rect.left = x + 24;
//    rect.top = y + 36;
//    rect.right = x + bmp.bmWidth + playerSize - 25;
//    rect.bottom = y + bmp.bmHeight + playerSize - 20;
//
//    return rect;
//}
//
//void Player::LoadSprites()
//{
//    for (int t = 0; t < 4; ++t) { // tool::hoe ~ tool::watering
//        Tool toolType = static_cast<Tool>(t);
//
//        for (int d = 0; d < 4; ++d) { // Direction::DOWN ~ LEFT
//            Direction dir = static_cast<Direction>(d);
//            //for (int f = 0; f < 4; ++f) {
//                int resourceId = GetResourceId(toolType, dir);  // 각 프레임별 리소스 ID
//
//                HBITMAP bmp = (HBITMAP)LoadImage(
//                    GetModuleHandle(NULL),
//                    MAKEINTRESOURCE(resourceId),
//                    IMAGE_BITMAP,
//                    0, 0,
//                    LR_CREATEDIBSECTION);
//
//                if (bmp) playerSprites[toolType][dir].push_back(bmp);
//        }
//    }
//}
//
//int Player::GetResourceId(Tool toolType, Direction dir)
//{
//    // 베이스 ID는 도구별로 다르게 설정
//    switch (toolType) {
//    case Tool::hoe:
//        return IDB_BITMAP45 + static_cast<int>(dir);
//    case Tool::Axe:
//        return IDB_BITMAP35 + static_cast<int>(dir);
//    case Tool::watering:
//        return IDB_BITMAP31 + static_cast<int>(dir);
//    case Tool::None:
//        return IDB_BITMAP27 + static_cast<int>(dir);
//    }
//}