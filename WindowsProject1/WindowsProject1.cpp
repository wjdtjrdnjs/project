// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "framework.h"
#include "WindowsProject1.h"
#include <windowsx.h>
#include <wingdi.h> 
#include <windows.h> 
#include <math.h> 
#include <iostream>
#include <string>
#include <vector>

//Objects 파일
//#include "Fence.h"
#include "Crop.h"
//#include "Animal.h"
#include "Player.h"
//#include "House.h"
//
////game파일
//#include "WorldMap.h"
////Managers파일
//#include "SingletonT.h"
//
//#include "RenderManager.h"
//#include "BitmapManager.h"
#include "InputManager.h"
//#include "GameObjectManager.h"
//#include "PlayerController.h"
//#include "CollisionManager.h"
#include "SingletonT.h"
#include "Global.h"
#include "MainGame.h"
#include "Gigagenie.h"
#include "WorldObject.h"
#include "Gigagenie.h"
#include "Box.h"
#include "TileData.h"
#include "BitmapManager.h"

MainGame game;

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
   // hModule = hInstance;//////////////////////////////////////
    // TODO: 여기에 코드를 입력합니다.
    //BitmapManager::Instance().Load(hInstance);
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
    MSG msg = { 0 };

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    LARGE_INTEGER prevTime;
    QueryPerformanceCounter(&prevTime);

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            LARGE_INTEGER currentTime;
            QueryPerformanceCounter(&currentTime);

            double deltaTime = double(currentTime.QuadPart - prevTime.QuadPart) / frequency.QuadPart;
            prevTime = currentTime;

            InputManager::Instance().Update();
            game.Update(static_cast<float>(deltaTime));

            InvalidateRect(game.GetHWND(), NULL, FALSE);
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
   BitmapManager::Instance().LoadAllBitmaps(); //모든 비트맵 로드

   InputManager::Instance().Init(hWnd);
   game.SetHWND(hWnd); //MainGame로 핸들 전달
   game.Init();  //게임 초기화

  // 

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {


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
        case IDM_ON:
            g_bFenceRedFrameOn = true;
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case IDM_OFF:
            g_bFenceRedFrameOn = false;
            InvalidateRect(hWnd, NULL, TRUE);
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
            // GameObjectManager::Instance().Update();
            // game->Update();
            InvalidateRect(hWnd, NULL, FALSE); // 화면 다시 그리
            break;
        }

        }

    }
    break;
    case WM_KEYDOWN: //상자 열기
    case WM_KEYUP:
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
        game.Input(message, wParam, lParam);
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT rect;
        GetClientRect(hWnd, &rect);

        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP backBuffer = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, backBuffer);

        // 배경 지우기
        FillRect(memDC, &rect, (HBRUSH)(COLOR_WINDOW + 1));

        // 게임 렌더링
         game.Render(memDC);

        // 백버퍼를 실제 화면에 출력
        BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);

        // 원래 선택된 비트맵 복원
        SelectObject(memDC, oldBitmap);

        // 자원 해제
        DeleteObject(backBuffer);
        DeleteDC(memDC);
        EndPaint(hWnd, &ps);
        return 0;
    }
    




    case WM_DESTROY:
        //KillTimer(hWnd, 999);  //타이머 종료
       // GameObjectManager::Instance().Release();
        //BitmapManager::Instance().Release();
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

//Box* box = GameObjectManager::Instance().GetBox();
       //if (wParam == 'E' && box->IsPlayerNear())
       //{
       //    if (box->IsOpen())
       //    {
       //        box->Close();
       //        box->SetPlayerNear(FALSE);
       //    }
       //    else
       //        box->Open();
       //}
       //else if (wParam == VK_ESCAPE)
       //{
       //    // ESC 키 처리
       //    if (box->IsOpen())
       //        box->Close();
       //}