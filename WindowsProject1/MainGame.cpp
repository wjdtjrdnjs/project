#include "MainGame.h"
#include "Gigagenie.h"
#include "BitmapManager.h"
#include "InputManager.h"
#include "GameObjectManager.h"
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
	genie->init();
	//  ex)	addMap(맵 이름, 가로 세로, 전체 타일타입)  
	//	ex)	addObjectToCurrentMap(타일타입::타일이름,오브젝트타입::오브젝트이름, x , y, 작물타입::작물이름) 마지막은 오브젝트타입이 작물이면 사용
	

	//300, 100, 500, 180
	OutputDebugStringA("디버겅용\n");

}

void MainGame::Render(HDC hdc)
{
	if (!genie)return;
	GameObjectManager::Instance().Render(hdc);

}

void MainGame::Update(float deltaTime)
{
	if (!genie)return;
	GameObjectManager::Instance().Update(deltaTime);
}



void MainGame::Run()
{
}

void MainGame::Input(UINT message, WPARAM wParam, LPARAM lParam)
{

	InputManager::Instance().ProcessMessage(message, wParam, lParam);
}

