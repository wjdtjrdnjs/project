// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"
#include <wingdi.h> 
#include <math.h> 
#include <iostream>
#include <list>
#include <vector>


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

#define map_y 23 
#define map_x 49
#define Inventory_x 3
#define Inventory_y 3


enum CropType { ONION, STRAWBERRY }; //작물 종류: 양파, 딸기

 class crop  //작물 정보
{
    public:
    int image = 1;  //작물 성장 단계 1~6
    int x = 0;      //위치 x
    int y = 0;      //위치 y
    int Ex = 0;     // 작물 경험치
    int cn = 0;
    CropType type; //작물 타입

};

 class Player //사용자
 {
 public:
     int image = 1;      //플레이어 이동 방향 사진 1~4
     int playerX = 100;  //위치x
     int playerY = 100;  //위치 y
     const int playerSize = 35; //플레이어 사이즈
 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   static Player p;  //플레이어 정보
   static int ch = 1;                  //플레이어 들고 있는 아이템 
   static int wasd = 0;                //플레이어 이동 방향
   static bool Inventory = FALSE;      //인벤토리 온 오프

   static int map[map_y][map_x] = { 0 };                    //맵
   static int Inventory_tile[Inventory_x][Inventory_y] = { 0 }; //3x3칸(xxxxxxxxxxx)
   static int TILE_SIZE = 26;           //바닥 타일 사이즈

   static int chicken_x = 150;         //닭 x위치
   static int chicken_y = 150;         //닭 y위치
   
   static int on_o = 0; //수확 양파(xxxxxxxxxxxxx)

   static HBITMAP chicken, Tile, on;        //닭, 타일, 수확 양파(xxxxxxx)
   static std::list<crop> iList;                  //작물 정보
   static std::vector<HBITMAP> onionBitmaps;      //양파 리소스
   static std::vector<HBITMAP> Strawberrybitmaps; //딸기 리소스
   static std::vector<HBITMAP> hPlayerBitmaps;    //플레이어 리소스
    switch (message)
    {
    case WM_CREATE:
    {
        SetTimer(hWnd, 999, 16, NULL); //플레이어 이동 타이머
        SetTimer(hWnd, 998, 300, NULL); // 닭 이동 타이머
        SetTimer(hWnd, 1, 300, NULL); //작물 성장 타이머

        for (int i = 0; i < 4; ++i) {
            HBITMAP hPlayerbmp = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_IDLE+i), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR); //플레이어
            hPlayerBitmaps.push_back(hPlayerbmp);  //4장

        }
        chicken = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP3), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR); //닭
        Tile = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_Tile), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);       //바닥
        on = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP18), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR); //수확한 양파(xxxxxxxx)
        for (int i = 0; i < 6; ++i) {
            HBITMAP bmp = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP2 + i), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR); //양파
            HBITMAP strawbeerybmp = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP10 + i), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR); //딸기

            Strawberrybitmaps.push_back(strawbeerybmp); //6장
            onionBitmaps.push_back(bmp); //6장
        }
     
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
            case IDM_didvk:     //양파
                ch = 1;
                break;
            case IDM_Ekfrl:     //딸기
                ch = 2;
                break;
            case IDM_rhoddl:    //괭이
                ch = 3;
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
          }
          break;
        case WM_TIMER: 
        {
            switch (wParam){ //플레이어 움직임
               
                case 999:
                {
                    if (GetKeyState(0x41) & 0x8000)  //왼쪽
                    {
                        p.playerX -= 5;
                        wasd = 3;
                    }
                    if (GetKeyState(0x44) & 0x8000)  //오른쪽
                    {
                        p.playerX += 5;
                        wasd = 2;
                    }
                    if (GetKeyState(0x57) & 0x8000)  //위
                    {
                        p.playerY -= 5;
                        wasd = 1;
                    }
                    if (GetKeyState(0x53) & 0x8000) //아래
                    {
                        p.playerY += 5;
                        wasd = 0;

                    }
                    //나중에 범위 설정

                    break;
                }             
                case 998: 
                {
                    //닭 움직임
                    chicken_x += (rand() % 10) - 5;
                    chicken_y += (rand() % 10) - 5;
                    break;
                    //나중에 범위 설정

                }
                case 1:  //작물 성장 타이머
                {
                    
                    for (auto& onion : iList)
                    {
                        onion.Ex += 10;

                        if (onion.Ex >= 100 && onion.image  < (int)onionBitmaps.size()) //경험치가 100이상이고 이미지가 마지막 단계가 아닐 경우  6단계
                        {
                            onion.Ex = 0;
                            onion.image++;  // 다음 단계로 성장
                        }
                    }

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
                Inventory = (Inventory == FALSE) ? TRUE : FALSE; //인벤토리 !Inventory;
                break;
            case '1':
                ch = 1;  //양파
                break;
            case '2':    //딸기
                ch = 2;
                break;
            case '3':    //괭이
                ch = 3;
                break;
            }
            InvalidateRect(hWnd, NULL, FALSE); // 화면 다시 그리기

        }
        break;

        case WM_LBUTTONDOWN:  //땅 교체
        {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);

            //타일 좌표
            int tileX = mouseX / TILE_SIZE; 
            int tileY = mouseY / TILE_SIZE;
            

            // 3x3 범위 체크
            int playerTileX = p.playerX / TILE_SIZE;
            int playerTileY = (p.playerY) / TILE_SIZE;

            // 3x3 범위 검사
            if (abs(tileX - playerTileX) <= 1 && abs(tileY - playerTileY) <= 1) {
                if (tileX >= 0 && tileX < map_x && tileY >= 0 && tileY < map_y)
                {
                    if (ch == 3)
                    {
                        if (map[tileY][tileX] == 0)// 클릭한 타일이 벽으로, 벽이면 흙으로
                        {

                            map[tileY][tileX] = 1;
                        }
                        else if (map[tileY][tileX] == 1)
                        {
                            map[tileY][tileX] = 0;
                            for (auto it = iList.begin(); it != iList.end(); ++it) //타일을 변경하면 그 위에 있는 작물 삭제
                            {
                                if (it->x == tileX * TILE_SIZE && it->y == (tileY * TILE_SIZE) - 5)
                                {
                                    iList.erase(it); //작물 삭제
                                    break;
                                }
                            }
                        }

                    }
                    //else //작물 수확 (xxxxxx)
                    //{
                    //    if (map[tileY][tileX] == 1)
                    //         for(auto& crop: iList)
                    //             if (crop.x == tileX * TILE_SIZE && crop.y == (tileY * TILE_SIZE) - 5)
                    //             {
                    //                 if (crop.image < (int)onionBitmaps.size())
                    //                 {
                    //                     crop.cn = 1;
                    //                 }
                    //             }


                    //   
                    //}
                    InvalidateRect(hWnd, NULL, FALSE);
                }
            }
                
        }
        break;
        case WM_RBUTTONDOWN: //씨앗
        {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);
            //타일 좌표
            int tileX = mouseX / TILE_SIZE;
            int tileY = mouseY / TILE_SIZE;

            //플레이어 기준 3x3만 클릭되게 설정
            int playerTileX = p.playerX / TILE_SIZE;
            int playerTileY = (p.playerY) / TILE_SIZE;

            // 3x3 범위 검사
            if (abs(tileX - playerTileX) <= 1 && abs(tileY - playerTileY) <= 1) {
                if (tileX >= 0 && tileX < map_x && tileY >= 0 && tileY < map_y)
                {
                    if (map[tileY][tileX] == 1)// 클릭한 타일이 흙이면 씨앗 심기
                    {
                        bool sw = true; //중복 작물

                        for (auto& onion : iList) 
                        {
                            if (onion.x == tileX * TILE_SIZE && onion.y == (tileY * TILE_SIZE) - 5) //같은 위치에 작물 설치 x
                            {
                                sw = false; // 작물 설치 x
                                break;
                            }
                                
                        }   
                        if (sw)  //작물 설치
                        {
                            crop p;     
                            p.x = tileX * TILE_SIZE;            //x 
                            p.y = (tileY * TILE_SIZE) - 5;      //y
                            switch (ch){                        
                            case 1:p.type = ONION; break;       //양파                      
                            case 2:p.type = STRAWBERRY; break;  //딸기
                            default:break;                              
                            }
                            iList.push_back(p);
                        }
                        
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
            HDC TileDC = CreateCompatibleDC(hdc);
            HBITMAP hOldTileBmp = (HBITMAP)SelectObject(TileDC, Tile);
            BITMAP Tile_bmp;
            GetObject(Tile, sizeof(BITMAP), &Tile_bmp);

            //작물
            HDC onionDC = CreateCompatibleDC(memDC); 


            for (int y = 0; y < map_y; ++y)
            {
                for (int x = 0; x < map_x; ++x)
                {
                    RECT tileRect = {  //타일 사이즈
                        x * TILE_SIZE,
                        y * TILE_SIZE,
                        (x + 1) * TILE_SIZE,
                        (y + 1) * TILE_SIZE
                    };
                    
                    if (map[y][x] == 0)
                    {                     
                        BOOL success_Tile = TransparentBlt(  
                            memDC,                   // 출력 DC
                            x * TILE_SIZE,          // 출력 위치 x
                            y * TILE_SIZE,          // 출력 위치 y
                            Tile_bmp.bmWidth+10,    // 출력 너비 + 10
                            Tile_bmp.bmHeight+10,   // 출력 높이 + 10
                            TileDC,                 // 원본 DC
                            0, 0,                   // 원본 비트맵 좌상단 좌표
                            Tile_bmp.bmWidth,
                            Tile_bmp.bmHeight,
                            RGB(255, 255, 255)     // 투명 처리할 색 
                        );                   
                    }
                    else
                    {
                        hBrush = CreateSolidBrush(RGB(139, 69, 19));
                        FillRect(memDC, &tileRect, hBrush);
                        DeleteObject(hBrush);
                    }             
                }
            }

            for (auto& onion : iList)
            {
                if (onion.image >= 1 && onion.image <= (int)onionBitmaps.size())
                {


                    HBITMAP currentBmp = NULL;
                    if (onion.type == ONION)   //심었을 때 씨앗 타입을 가져옴
                        currentBmp = onionBitmaps[onion.image - 1];  //vector 0부터 시작해서 -1
                    else if (onion.type == STRAWBERRY)
                        currentBmp = Strawberrybitmaps[onion.image - 1];
                    
                    if (currentBmp) //currentBmp이 null이 아니면 참
                    {
                        HBITMAP oldBmp = (HBITMAP)SelectObject(onionDC, currentBmp);

                        BITMAP bmp;
                        GetObject(currentBmp, sizeof(BITMAP), &bmp);

                        TransparentBlt(memDC,
                            onion.x, onion.y,
                            bmp.bmWidth * 2, bmp.bmHeight * 2,                         
                            onionDC,
                            0, 0,
                            bmp.bmWidth, bmp.bmHeight,
                            RGB(255, 255, 255));

                        SelectObject(onionDC, oldBmp); // 원상복구
                    }
                }
            }

            // 끝나고 DC 제거
            SelectObject(TileDC, hOldTileBmp);
            DeleteDC(TileDC);
            DeleteDC(onionDC);

            //임시로 만든 인벤(xxxxxxxxx)
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
            HBITMAP hOldPlayerBmp = NULL;
            BITMAP bmp;

            if (wasd >= 0 && wasd < hPlayerBitmaps.size())
            {
                hOldPlayerBmp = hPlayerBitmaps[wasd];
                HBITMAP hPrevBmp = (HBITMAP)SelectObject(hPlayerDC, hOldPlayerBmp);
                GetObject(hOldPlayerBmp, sizeof(BITMAP), &bmp);

                int drawWidth = bmp.bmWidth * 2;
                int drawHeight = bmp.bmHeight * 2;

                // 중심 기준
                int drawX = p.playerX - drawWidth / 2;
                int drawY = p.playerY - drawHeight / 2;

                // 실제 크기
                BOOL success = TransparentBlt(
                    memDC,          // 출력 DC
                    drawX,      // 출력 위치 X
                    drawY,     // 출력 위치 Y
                    drawWidth,    // 출력 너비 (21)
                    drawHeight,
                    hPlayerDC,      // 원본 DC
                    0, 0,          // 원본 비트맵 좌상단 좌표
                    bmp.bmWidth,
                    bmp.bmHeight,
                    RGB(255, 255, 255)  // 투명 처리할 색 (흰색)
                );
                SelectObject(hPlayerDC, hOldPlayerBmp);

            }
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
                c_bmp.bmWidth,    // 출력 너비
                c_bmp.bmHeight,   // 출력 높이
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
        KillTimer(hWnd, 999); //플레이어 이동 타이머 삭제
        KillTimer(hWnd, 998); //닭 이동 타이머 삭제
        KillTimer(hWnd, 1);  //작물 성장 타이머 삭제
        for (auto bmp : onionBitmaps) {    //양파 비트맵 삭제
            DeleteObject(bmp);
        }
        for (auto bmp : Strawberrybitmaps)  //딸기 비트맵 삭제
            DeleteObject(bmp);
        for (auto bmp : hPlayerBitmaps)     //플레이어 비트맵 삭제
            DeleteObject(bmp);
        DeleteObject(chicken); //닭
        DeleteObject(Tile);//타일
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
