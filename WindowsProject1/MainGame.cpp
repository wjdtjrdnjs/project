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
	OutputDebugString(L"��ü ������\n");
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	genie->init();
	//  ex)	addMap(�� �̸�, ���� ����, ��ü Ÿ��Ÿ��)  
	//	ex)	addObjectToCurrentMap(Ÿ��Ÿ��::Ÿ���̸�,������ƮŸ��::������Ʈ�̸�, x , y, �۹�Ÿ��::�۹��̸�) �������� ������ƮŸ���� �۹��̸� ���
	

	//300, 100, 500, 180
	OutputDebugStringA("����Ͽ�\n");

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

