#include "Player.h"
#include "InputManager.h" 
#include "BitmapManager.h"
#include "RenderManager.h"
std::map<Direction, std::vector<HBITMAP>> ply;
Player::Player() : x(50), y(250), selectedCrop(CropType::Strawberry) 
{
   
    ply =BitmapManager::Instance().GetPlayerBitmaps();
  
    for (int i = 0; i < 9; i++) {  //플레이어 인벤토리 초기화
        inventory[i].type = CropType::None;
        inventory[i].count = 0;
    } 
    //기본 아이템
    inventory[0].type = CropType::Strawberry_1; //1번 딸기봉투와 5개
    inventory[0].count = 5;
    inventory[1].type = CropType::Onion_1;      //2번 양파봉투 5개
    inventory[1].count = 5;
    inventory[2].type = CropType::hoe;        //괭이
    inventory[2].count = 1;
    inventory[3].type = CropType::watering;     //물뿌리개
    inventory[3].count = 1;
}

Player::~Player()  //소멸자
{
    
}



void Player::RenderInventory(HDC hdc, int screenWidth, int screenHeight)  //플레이어 인벤토리 아래(툴바)
{
    int slotSize = 50;
    int startX = 10;
    int startY = screenHeight - slotSize - 10;

    for (int i = 0; i < 9; i++) { //9칸
        HBRUSH brush = nullptr;
        if (i == selectedTool)   //선택된 번호
            brush = CreateSolidBrush(RGB(150, 150, 150)); // 선택된 슬롯 강조
        else
            brush = CreateSolidBrush(RGB(200, 200, 200)); // 기본 색
        
        RECT slotRect = { startX + i * (slotSize + 5)+350, startY, startX + i * (slotSize + 5) + slotSize+350, startY + slotSize };

        FillRect(hdc, &slotRect, brush);
        FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));  // 테두리

        DeleteObject(brush);

        if (inventory[i].type != CropType::None) {
            HBITMAP bmp =BitmapManager::Instance().GetBitmapForCrop(inventory[i].type);
            HDC memDC = CreateCompatibleDC(hdc);
            HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
            BITMAP bm;
            GetObject(bmp, sizeof(BITMAP), &bm);

            int drawSize = 40;
            int offsetX = slotRect.left + (slotSize - drawSize) / 2;
            int offsetY = slotRect.top + (slotSize - drawSize) / 2;
          
            
            TransparentBlt(hdc,
                offsetX, offsetY,
                drawSize, drawSize, 
                memDC,
                0, 0, 
                bm.bmWidth,
                bm.bmHeight,
                RGB(255, 255, 255));
            std::string countText = std::to_string(inventory[i].count);
            //SetBkMode(hdc, TRANSPARENT);  //글자 배경을 투명으로 만든다
            TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), countText.length());
            SelectObject(memDC, oldBmp);
            DeleteDC(memDC);
        }

    }
}

void Player::AddItem(CropType type) {   //인벤토리에 아이템 추가 
    for (auto& slot : inventory) {//같은 타입이면 수량 증가
        if (slot.type == type) {
            slot.count++;
            return;
        }
    }
    for (auto& slot : inventory) {
        if (slot.type == CropType::None) { //같은 타입이 없으면 슬롯에 타입을 넣고 수량 추가
            slot.type = type;
            slot.count = 1;
            return;
        }
    }
}
void Player::Render(HDC hdc) //플레이어를 화면에 렌더링
{
    if (ply.empty()) return;

    // 현재 방향의 비트맵 리스트 가져오기
    auto& bitmaps = ply[currentDir];

    if (bitmaps.empty()) return;

    // 예를 들어 첫 번째 프레임만 사용 (나중에 애니메이션 프레임 관리 가능)
    HBITMAP currentBmp = bitmaps[0];
    if (!currentBmp) return;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, currentBmp);

    BITMAP bmpInfo;
    GetObject(currentBmp, sizeof(BITMAP), &bmpInfo);

    TransparentBlt(
        hdc,
        x, y,
        bmpInfo.bmWidth + playersize, bmpInfo.bmHeight + playersize,
        memDC,
        0, 0,
        bmpInfo.bmWidth, bmpInfo.bmHeight,
        RGB(255, 255, 255)
    );

    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}

void Player::UpdatePlayer()
{
    if (isBoxOpen) {  //박스 오픈 
        if (InputManager::Instance().IsLeftClickDown()) {
            POINT pt = InputManager::Instance().GetMousePosition();
            RenderManager::Instance().GetBox()->HandleClick(pt.x, pt.y, 1);
        }
        else if (InputManager::Instance().IsRightClickDown())
        {
            POINT pt = InputManager::Instance().GetMousePosition();
            RenderManager::Instance().GetBox()->HandleClick(pt.x, pt.y,2);
        }
        return;  // 상자 열렸을 땐 이동 금지
    }
    Playermove(); //플레이어 이동 처리
    HandleToolSelection(); //아이템창 아래(툴바) 번호 선택
    if (InputManager::Instance().IsLeftClickDown()) { //좌클릭
        HandleLeftClickAction();
    }
    if (InputManager::Instance().IsRightClickDown()) { //우클릭
    }
}

void Player::Playermove() //플레이어 이동 처리
{
    // 이동 처리
    if (InputManager::Instance().IsKeyHeld('A')) {
        x -= 5;
        currentDir = LEFT;
    }
    else if (InputManager::Instance().IsKeyHeld('D')) {
        x += 5;
        currentDir = RIGHT;
    }
    else if (InputManager::Instance().IsKeyHeld('W')) {
        y -= 5;
        currentDir = UP;
    }
    else if (InputManager::Instance().IsKeyHeld('S')) {
        currentDir = DOWN;
    }
}
void Player::HandleToolSelection() { //번호 선택 함수
    for (int i = 0; i < 9; ++i) {
        if (InputManager::Instance().IsKeyDown('1' + i)) {
            selectedTool = i;
            break;
        }
    }
}
//코드 수정 필요
void Player::HandleLeftClickAction()//아이템을 들고 좌클릭
{
    POINT pt = InputManager::Instance().GetMousePosition();

    //타일 위치x,y
    int tileX = pt.x / tileSize;
    int tileY = pt.y / tileSize;


    std::string debugMsg = "Left Click at (" + std::to_string(pt.x) + ", " + std::to_string(pt.y) + ")\n"; //디버깅 확인용 
    OutputDebugStringA(debugMsg.c_str());
    Player* player = RenderManager::Instance().GetPlayer();  //플레이어 정보 호출

    if (!player) return; //생성죄지 않았다면 브레이크


    //플레이어 범위 x,y
    int playerTileX = (player->GetX() + tileSize / 2) / tileSize;
    int playerTileY = (player->GetY() + tileSize / 2) / tileSize;

    if (abs(tileX - playerTileX) > 1 || abs(tileY - playerTileY) > 1) return;// 범위 밖 클릭 무시

    if (inventory[selectedTool].type == CropType::hoe)  // 괭이일 때만 땅 교체 가능
    {
        Crop* crop = RenderManager::Instance().GetCropAt(tileX, tileY);
        if (crop)
        {
            RenderManager::Instance().RemoveCrop(crop);  //땅위에 작물이 있으면 삭제
            delete crop;
        }
        Map::ToggleTile(tileX, tileY, 4); //땅 교체
    }
    else if (inventory[selectedTool].type == CropType::Axe) //도끼 일때만 울타리 삭제
    {
        PlaceableObject* obj = RenderManager::Instance().GetFenceAt(tileX, tileY); //울타리

        if (obj) {
            obj->Remove(tileX, tileY, player);
        }

    }
    else if (inventory[selectedTool].type == CropType::watering) //물뿌리개
    {
        Map::ToggleTile(tileX, tileY, 7); //땅 교체

    }
    else // 괭이, 도끼 제외 작물 수확
    {
        PlaceableObject* obj = RenderManager::Instance().GetCropAt(tileX, tileY); //작물
        if (obj) {
            obj->Remove(tileX, tileY, player);
        }
    }
}
//코드 수정 필요
void Player::HandleRightClickAction() //아이템을 들고 우클릭
{
    POINT pt = InputManager::Instance().GetMousePosition();  //마우스가 클릭된 좌표를 가져옴

    //클릭한 타일 위치 
    int tileX = pt.x / tileSize;
    int tileY = pt.y / tileSize;
    // 디버깅 출력 좌표확인
    std::string debugMsg = "Right Click at (" + std::to_string(pt.x) + ", " + std::to_string(pt.y) + ")\n";
    OutputDebugStringA(debugMsg.c_str());

    Player* player = RenderManager::Instance().GetPlayer();//플레이어 정보 호출

    if (!player) return; //플레이어 정보가 존재하지 않는다면 종료

    if (abs(tileX - (player->GetX() + tileSize / 2) / tileSize) > 1 || abs(tileY - (player->GetY() + tileSize / 2) / tileSize) > 1) return;

    PlaceableObject* obj = nullptr;
    InventoryItem* inv = inventory; //인벤토리 정보를 가져옴

    switch (inv[selectedTool].type) {
    case CropType::Onion_1:
        obj = new Crop(CropType::Onion);
        break;
    case CropType::Strawberry_1:
        obj = new Crop(CropType::Strawberry);
        break;
    case CropType::Fence:
        obj = new Fence();
        break;
    }
    
    if (obj) {
        obj->Install(tileX, tileY, player);
    }
   
}

