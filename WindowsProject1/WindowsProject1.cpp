// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"
#include <windowsx.h>
#include <wingdi.h> 
#include <math.h> 
#include <iostream>
#include <vector>

//Objects 파일
#include "Fence.h"
#include "Crop.h"
#include "Animal.h"
#include "Player.h"
#include "Inventory.h"
#include "Box.h"
#include "House.h"

//game파일
#include "Map.h"

//Managers파일
#include "SingletonT.h"

#include "RenderManager.h"
#include "BitmapManager.h"
#include "InputManager.h"
#include "GameObjectManager.h"

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
    BitmapManager::Instance().Load(hInstance);
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


Box* box = nullptr; 
Player* player = nullptr;
House* house = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
 
    case WM_CREATE:
    {
        InputManager::Instance().Init(hWnd);

        player = new Player();                 //플레이어 생성
        house = new House();                 //플레이어 생성
        Animal* animal = new Animal();         //동물 생성
        Map* map = new Map();                  //맵 생성
        box = new Box(127, 285);               //상자 위치 전달

        //렌더 매니저에 등록
        GameObjectManager::Instance().SetPlayer(player);
        RenderManager::Instance().SetHouse(house);
        GameObjectManager::Instance().AddAnimal(animal);
        RenderManager::Instance().SetMap(map);
        RenderManager::Instance().SetBox(box);

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
            InputManager::Instance().Update();  //모든 객체 업데이트
            GameObjectManager::Instance().UpdateAll();  //모든 객체 업데이트
            InvalidateRect(hWnd, NULL, FALSE); // 화면 다시 그리
            break;
        }

        }

    }
    break;  
    case WM_KEYDOWN: //상자 열기
    {

        Player* player = GameObjectManager::Instance().GetPlayer();
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
                box->SetPlayerToolbar(player->GetInventory());

            }
        }
        else if (wParam == 'E' || wParam == VK_ESCAPE && box->IsOpen() ) { //esc나 E로 상자 닫기
            box->Close();
           
            player->SetBoxOpen(false); //닫으면 플레이어 이동 가능
        }

        if (wParam == VK_TAB || wParam == 'I') {
            static bool inventoryOpen = false;
            inventoryOpen = !inventoryOpen;

            // 이 상태는 렌더 함수나 업데이트 루프에 반영해야 함
            player->SetInventoryOpen(inventoryOpen); 
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

        RenderManager::Instance().RenderAll(memDC, hWnd);
     
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
        BitmapManager::Instance().Release();
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
