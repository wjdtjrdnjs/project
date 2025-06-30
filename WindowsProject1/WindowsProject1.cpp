// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"
#include <wingdi.h> 
#include <math.h> 

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

#define map_y 20
#define map_x 30
#define Inventory_x 3
#define Inventory_y 3
#define Inventory_main 5
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

   static int playerX = 100;         //플레이어 x위치
   static int playerY = 100;         //플레이어 y위치
   static bool Inventory = FALSE;    //인벤토리 온 오프
   const int TILE_SIZE = 16;         //바닥 사이즈
   static int map[map_y][map_x] = { 0 }; //맵
   static int Inventory_tile[Inventory_x][Inventory_y] = { 0 }; //3x3칸
   static int Inventory_m[Inventory_main] = { 0 };  // 아래 9줄
   static HBITMAP hPlayerBitmap, chicken, onion;
   const int playerSize = 25;           
   static int chicken_x = 150;         //닭 x위치
   static int chicken_y = 150;         //닭 x위치
    switch (message)
    {
    case WM_CREATE:
    {
        SetTimer(hWnd, 1, 16, NULL); //플레이어
        SetTimer(hWnd, 2, 300, NULL); // 닭
        hPlayerBitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR); //사람
        chicken = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP3), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR); //닭
        onion = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP4), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);//양파
       
        break;
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
            switch (wParam){ //플레이어 움직임
               
                case 1:
                {
                    if (GetKeyState(0x41) & 0x8000)
                        playerX -= 5;
                    if (GetKeyState(0x44) & 0x8000)
                        playerX += 5;
                    if (GetKeyState(0x57) & 0x8000)
                        playerY -= 5;
                    if (GetKeyState(0x53) & 0x8000)
                        playerY += 5;

                    //나중에 범위 설정

                    break;
                }             
                case 2: 
                {
                    //닭 움직임
                    chicken_x += (rand() % 10) - 5;
                    chicken_y += (rand() % 10) - 5;
                    break;
                    //나중에 범위 설정
                }
                case 3:
                {
                   
                    onion = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP3), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);//양파
                    break;
                }
            }
            InvalidateRect(hWnd, NULL, FALSE); // 화면 다시 그리기


        }
           break;
        case WM_KEYDOWN:
        {
            switch (wParam) {
            case 'I':
                Inventory = (Inventory == FALSE) ? TRUE : FALSE; //인벤토리 //!Inventory; 이것도 사용가능!
                InvalidateRect(hWnd, NULL, FALSE); // 화면 다시 그리기

            }
        }
        break;
        case WM_LBUTTONDOWN:
        {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);
            //타일 좌표
            int tileX = mouseX / TILE_SIZE; 
            int tileY = mouseY / TILE_SIZE;
            
            //플레이어 기준 3x3만 클릭되게 설정
            if (playerX - 16 < mouseX && playerX + playerSize + 16 > mouseX &&
                playerY - 16 < mouseY && playerY + playerSize + 16 > mouseY)
            {
                if (tileX >= 0 && tileX < map_x && tileY >= 0 && tileY < map_y)
                {
                    if (map[tileY][tileX] == 0)// 클릭한 타일이 흙이면 벽으로, 벽이면 흙으로
                    {
                       
                        map[tileY][tileX] = 1;
                        SetTimer(hWnd, 3, 500, NULL); //양파
                    }
                    else if (map[tileY][tileX] == 1)
                    {
                        map[tileY][tileX] = 0;
                    }
                    InvalidateRect(hWnd, NULL, FALSE);
                }
            }
                
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // 1. 메모리 DC 생성
            HDC memDC = CreateCompatibleDC(hdc);

            // 2. 화면과 같은 크기의 비트맵 생성
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            HBITMAP memBitmap = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
            HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);
            HBRUSH hBrush;



            // 3. 메모리 DC에 먼저 그림
            // 타일맵 그리기
            for (int y = 0; y < map_y; ++y)
            {
                for (int x = 0; x < map_x; ++x)
                {
                    RECT tileRect = {
                        x * TILE_SIZE,
                        y * TILE_SIZE,
                        (x + 1) * TILE_SIZE,
                        (y + 1) * TILE_SIZE
                    };
                    
                    if (map[y][x] == 0)
                    {
                        hBrush = CreateSolidBrush(RGB(180, 255, 180));
                        FillRect(memDC, &tileRect, hBrush);
                        DeleteObject(hBrush);
                    }
                    else
                    {
                        hBrush = CreateSolidBrush(RGB(139, 69, 19));
                        FillRect(memDC, &tileRect, hBrush);
                        DeleteObject(hBrush);

                        HDC onionDC = CreateCompatibleDC(hdc);
                        HBITMAP hOldonionBmp = (HBITMAP)SelectObject(onionDC, onion);

                        BITMAP onion_bmp;
                        GetObject(onion, sizeof(BITMAP), &onion_bmp);

                        // 실제 크기로 투명처리해서 출력
                        BOOL success_onion = TransparentBlt(
                            memDC,          // 출력 DC
                            x * TILE_SIZE,       // 출력 위치 X
                            y * TILE_SIZE-5,        // 출력 위치 Y
                            onion_bmp.bmWidth,    // 출력 너비 (21)
                            onion_bmp.bmHeight,   // 출력 높이 (28)
                            onionDC,      // 원본 DC
                            0, 0,          // 원본 비트맵 좌상단 좌표
                            onion_bmp.bmWidth,
                            onion_bmp.bmHeight,
                            RGB(255, 255, 255)  // 투명 처리할 색 (흰색)
                        );

                        SelectObject(onionDC, hOldonionBmp);
                        DeleteDC(onionDC);
                    }

                   
                }
            }
           

            //임시로 만든 인벤
            if (Inventory == TRUE)
            {
                for (int y = 0; y < Inventory_y; ++y)
                {
                    for (int x = 0; x < Inventory_x; ++x)
                    {
                        RECT Inven_Rect = {
                             x * (TILE_SIZE * 2),
                             y * (TILE_SIZE * 2),
                            (x + 1) * (TILE_SIZE * 2),
                            ( y + 1) * (TILE_SIZE * 2)
                        };

                        hBrush = CreateSolidBrush(RGB(139, 69, 19));

                        FillRect(memDC, &Inven_Rect, hBrush);
                        DeleteObject(hBrush);
                       
                    }
                    
                }
            }
           
           
            // 캐릭터 그리기
            HDC hPlayerDC = CreateCompatibleDC(hdc);
            HBITMAP hOldPlayerBmp = (HBITMAP)SelectObject(hPlayerDC, hPlayerBitmap);

            BITMAP bmp;
            GetObject(hPlayerBitmap, sizeof(BITMAP), &bmp);

            // 실제 크기로 투명처리해서 출력
            BOOL success = TransparentBlt(
               memDC,          // 출력 DC
                playerX,       // 출력 위치 X
                playerY,        // 출력 위치 Y
                bmp.bmWidth,    // 출력 너비 (21)
                bmp.bmHeight,   // 출력 높이 (28)
                hPlayerDC,      // 원본 DC
                0, 0,          // 원본 비트맵 좌상단 좌표
                bmp.bmWidth,
                bmp.bmHeight,
                RGB(255, 255, 255)  // 투명 처리할 색 (흰색)
            );
            SelectObject(hPlayerDC, hOldPlayerBmp);
            DeleteDC(hPlayerDC);


            //e닭
            HDC chickenDC = CreateCompatibleDC(hdc);
            HBITMAP hOldchickenBmp = (HBITMAP)SelectObject(chickenDC, chicken);

            BITMAP c_bmp;
            GetObject(chicken, sizeof(BITMAP), &c_bmp);

            // 실제 크기로 투명처리해서 출력
            BOOL success_chicken = TransparentBlt(
                memDC,          // 출력 DC
                chicken_x,       // 출력 위치 X
                chicken_y,        // 출력 위치 Y
                c_bmp.bmWidth,    // 출력 너비 (21)
                c_bmp.bmHeight,   // 출력 높이 (28)
                chickenDC,      // 원본 DC
                0, 0,          // 원본 비트맵 좌상단 좌표
                c_bmp.bmWidth,
                c_bmp.bmHeight,
                RGB(255, 255, 255)  // 투명 처리할 색 (흰색)
            );
            SelectObject(chickenDC, hOldchickenBmp);
            DeleteDC(chickenDC);


            

            // 4. 메모리 DC를 실제 DC에 복사
            BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, memDC, 0, 0, SRCCOPY);
            
            // 5. 리소스 정리
            SelectObject(memDC, oldBitmap);
            DeleteObject(memBitmap);
            DeleteDC(memDC);

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
        KillTimer(hWnd, 1); //플레이어 이동
        KillTimer(hWnd, 2); //닭 이동
        KillTimer(hWnd, 3); //양파 
        
        DeleteObject(hPlayerBitmap); //비트맵 이미지 제거
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
