// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"
#include <wingdi.h> 
#include <math.h> 
#include <iostream>
#include <list>
#include <vector>
#include "Player.h"
#include "Animal.h"
#include "Crop.h"
#include "Map.h"
#include "RenderManager.h"
#include "BitmapManager.h"
#include "InputManager.h"
#include "Box.h"
#include <windowsx.h>
#define MAX_LOADSTRING 100
// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    BitmapManager::Load(hInstance);
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
// 


#define Inventory_x 3
#define Inventory_y 3
Box* box = nullptr; 

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
 
    case WM_CREATE:
    {
        InputManager::Init(hWnd);

        Player* player = new Player();                 //플레이어 생성
        Animal* animal = new Animal();                 //동물 생성
        Map* map = new Map();                          //맵 생성
        box = new Box(300, 5);                         //상자 위치 전달

        //렌더 매니저에 등록
        RenderManager::SetPlayer(player);             
        RenderManager::AddAnimal(animal);
        RenderManager::SetMap(map);
        RenderManager::SetBox(box);

        SetTimer(hWnd, 999, 16, NULL); //플레이어 이동 타이머


        return 0;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
           
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
          }
          break;
      
    case WM_TIMER:
    {
        switch (wParam) 
        {
        case 999:
        {                            
            RenderManager::UpdateAll();  //모든 객체 업데이트
            InvalidateRect(hWnd, NULL, FALSE); // 화면 다시 그리
            break;
        }

        }

    }
    break;
    case WM_LBUTTONUP:
    {
        POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        //타일 위치x,y
        int tileX = pt.x / tileSize;
        int tileY = pt.y / tileSize;

        Player* player = RenderManager::GetPlayer();  //플레이어 정보 호출
        if (!player) break; //생성죄지 않았다면 브레이크

        int tool = player->GetSelectedTool();  //선택된 아이템(슬롯)

        //플레이어 범위 x,y
        int playerTileX = (player->GetX() + tileSize / 2) / tileSize;
        int playerTileY = (player->GetY() + tileSize / 2) / tileSize;

        if (abs(tileX - playerTileX) > 1 || abs(tileY - playerTileY) > 1) break; // 범위 밖 클릭 무시

        if (tool == 3)  // 괭이일 때만 땅 교체 가능
        {
            Crop* crop = RenderManager::GetCropAt(tileX, tileY);
            if (crop)
            {
                RenderManager::RemoveCrop(crop);  //땅위에 작물이 있으면 삭제
                delete crop;
            }
            Map::ToggleTile(tileX, tileY); //땅 교체
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else // 맨손 수확
        {
            Crop* crop = RenderManager::GetCropAt(tileX, tileY); // 선택된 타일 위에 무엇이 있는지 확인
            if (crop && crop->IsFullyGrown()) //작물이 있고 성장이 끝았을 때
            {
                CropType type = crop->GetType(); //작물 정보 가져옴
                RenderManager::RemoveCrop(crop);//작물 삭제
                delete crop;//작물 삭제
                player->AddItem(type); //인벤토리에 추가
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }    
        return 0;
    }
    case WM_RBUTTONDOWN:
    {
        int mouseX = GET_X_LPARAM(lParam);
        int mouseY = GET_Y_LPARAM(lParam);
        
        //클릭한 타일 위치 
        int tileX = mouseX / tileSize;
        int tileY = mouseY / tileSize;

        Player* player = RenderManager::GetPlayer();//플레이어 정보 호출
        if (!player) break; //생성되지 않았다면 브레이크

        int tool = player->GetSelectedTool();  //선택된 아이템(슬롯)
        CropType selectedCrop = player->GetSelectedCrop(); //선택된 작물(1,2)번 딸기와 양파

        if (abs(tileX - (player->GetX() + tileSize / 2) / tileSize) > 1 || abs(tileY - (player->GetY() + tileSize / 2) / tileSize) > 1) break;
        
        if (tool == 1 || tool == 2) // 현재는 1,2번이지만 나중에 들고있는 아이템으로 교체
        {
            if (Map::GetTile(tileX, tileY) == TILE_FARMLAND && !RenderManager::GetCropAt(tileX, tileY)) //타일이 밭(농지)이고 
            {
                InventoryItem* inv = player->GetInventory();  //아이템 타입을 가져옴

                for (int i = 0; i < 9; ++i)  //인벤토리 9칸
                {
                    if (inv[i].type == selectedCrop && inv[i].count > 0) //타입이 선택되고 1개 이상일 때
                    {
                        CropType baseCropType = CropType::None; //처음은 빈손
                        if (selectedCrop == CropType::Strawberry_1) baseCropType = CropType::Strawberry; //딸기씨앗 봉투면 딸기 
                        else if (selectedCrop == CropType::Onion_1) baseCropType = CropType::Onion;     //양파씨앗 봉투면 양파 

                        if (baseCropType != CropType::None) { //빈손이 아닐 때
                            Crop* crop = new Crop(baseCropType);  //선택된 작물 정보 가져옴
                            crop->SetPosition(tileX * tileSize, tileY * tileSize); //설치할 위치
                            RenderManager::AddCrop(crop);  //작물 추가
                            InvalidateRect(hWnd, NULL, FALSE);

                            inv[i].count--;  // 들고있는 아이템 -1
                            if (inv[i].count == 0) //들고있는 아이템 개수가 0개이다
                                inv[i].type = CropType::None; //아이템이 0개면 빈 슬롯
                        }
                        break;
                    }
                }
            }
        }
        else // 맨손 수확(우클릭 1,2번으로 수확 x)
        {
            Crop* crop = RenderManager::GetCropAt(tileX, tileY); //선택된 타일 위에 무엇이 있는지 확인 
            if (crop && crop->IsFullyGrown()) { //작물이 있고 성장이 끝았을 때
                CropType type = crop->GetType();  //작물 정보 가져옴
                RenderManager::RemoveCrop(crop);  //작물 삭제
                delete crop;  //작물 삭제
                player->AddItem(type);  //인벤토리에 추가
            }
           
        }
        return 0;
    }

    case WM_KEYDOWN: //상자 열기
    {
        Player* player = RenderManager::GetPlayer();
        if (!player || !box) break;

        int mouseX, mouseY;
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);
        mouseX = pt.x;
        mouseY = pt.y;

        if (wParam == 'E' && !player->IsBoxOpen()) {  //상자 열기
            if (box->IsPlayerInRange(player->GetX(), player->GetY()) &&
                box->IsMouseOverIcon(mouseX, mouseY)) {
                box->Open();    //상자 열기
                player->SetBoxOpen(true); //상자 열면 플레이어 이동 불가
            }
        }
        else if (wParam == 'E' || wParam == VK_ESCAPE && box->IsOpen() ) { //esc나 E로 상자 닫기
            box->Close();
            player->SetBoxOpen(false); //닫으면 플레이어 이동 가능
        }
        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        HDC memDC = CreateCompatibleDC(hdc);
        RECT rect;
        GetClientRect(hWnd, &rect);
        HBITMAP backBuffer = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
        SelectObject(memDC, backBuffer);

        FillRect(memDC, &rect, (HBRUSH)(COLOR_WINDOW + 1));

        RenderManager::RenderAll(memDC, hWnd); 

        BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);

        DeleteObject(backBuffer);
        DeleteDC(memDC);
        EndPaint(hWnd, &ps);
        return 0;
    }





    case WM_DESTROY:
        KillTimer(hWnd, 999);  //타이머 종료
        if (box) {  //상자 삭제
            delete box;
            box = nullptr;
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
