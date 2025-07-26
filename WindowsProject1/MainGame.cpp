#include "MainGame.h"
#include "Gigagenie.h"
#include "BitmapManager.h"
#include "resource.h"
#include "Global.h"
#include "Map.h"
#include "Player.h"
#include "InputManager.h"
#include <Windows.h>
#include <optional>
MainGame::MainGame()
{
	genie = std::make_unique<Gigagenie>();
	OutputDebugString(L"객체 생성됨\n");
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	///////////////////나중에 비트맵매니저로 옮겨야할 코드/////////////////
	BitmapManager::Instance().Load("Grass", IDB_BITMAP22);
	BitmapManager::Instance().Load("Farm", IDB_BITMAP42);
	BitmapManager::Instance().Load("Water", IDB_BITMAP43);
	BitmapManager::Instance().Load("Box", IDB_BITMAP24);
	BitmapManager::Instance().Load("Strawberry", IDB_BITMAP10);
	BitmapManager::Instance().Load("Onion", IDB_BITMAP2);
	BitmapManager::Instance().Load("Player", IDB_BITMAP27);
	BitmapManager::Instance().Load("Tree", IDB_BITMAP49);
	////////////////////////////////////////////////////////////////

	//  ex)	addMap(맵 이름, 가로 세로)  << 나중에 맵 타일 타입설정도 넣어야 함(전체 타일)
	//	ex)	addObjectToCurrentMap(타일타입::타일이름,오브젝트타입::오브젝트이름, x , y, 작물타입::작물이름) 마지막은 오브젝트타입이 작물이면 사용


	//초기 맵 설정 Farm맵
	genie->addMap("Farm", 40, 19); //맵 생성
	genie->addObjectToCurrentMap(TileType::None, ObjectType::Player, 8, 8); //타일타입, 설치할 오브젝트 타입, 좌표(x,y)

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			genie->addObjectToCurrentMap(TileType::Farmland, ObjectType::Crop, 10 + i, 9 + j, CropType::Strawberry); 
			genie->addObjectToCurrentMap(TileType::Farmland, ObjectType::Crop, 14 + i, 9 + j, CropType::Onion); 
		}
	}
	genie->addObjectToCurrentMap(TileType::None, ObjectType::Box, 11, 8); 
	genie->addObjectToCurrentMap(TileType::None, ObjectType::Box, 15, 8);
	//genie->addObjectToCurrentMap(TileType::None, ObjectType::Tree, 2, 15);

	//genie->addMap("MyRoom",50, 30);
	OutputDebugStringA("디버겅용\n");

}

void MainGame::Render(HDC hdc)
{
	if (!genie || genie->maps.empty())
		return;

	genie->currentMap().Render(hdc);

}

void MainGame::Update()
{
}

void MainGame::Run()
{
	//HDC hdc = GetDC(hwnd);

	while (TRUE)
	{
		// Windows 메시지 큐에서 메시지가 있으면 가져온다 (없으면 루프 계속 돈다)
		//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//{
		//	// 메시지가 WM_QUIT이면 프로그램 종료
		//	if (msg.message == WM_QUIT)
		//		break;

		//	// 키보드 키가 눌렸을 때의 메시지 처리
		//	if (msg.message == WM_KEYDOWN) {
		//		Input(msg.wParam); // 눌린 키 정보를 Input 함수에 전달 (예: VK_LEFT 등)
		//	}

		//	// 키 입력 등 메시지를 텍스트로 번역 (예: WM_KEYDOWN → 문자)
		//	TranslateMessage(&msg);

		//	// 메시지를 윈도우 프로시저(WndProc)로 전달해서 기본 처리
		//	DispatchMessage(&msg);
		//}
		//Update();
	}
	
}

void MainGame::Input(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_LEFT:  genie->MovePlayer(Direction::LEFT);  break;
		case VK_RIGHT: genie->MovePlayer(Direction::RIGHT); break;
		case VK_UP:    genie->MovePlayer(Direction::UP);    break;
		case VK_DOWN:  genie->MovePlayer(Direction::DOWN);  break;
		}
	}
}
