#pragma once
#include <vector>
#include <windows.h>
#include <algorithm>
#include "resource.h"
#include "CropType.h"
#include "Crop.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "PlaceableObject.h"

enum Direction { //�÷��̾� ����
	DOWN = 0,
	UP = 1,
	RIGHT = 2,
	LEFT = 3
};

class Player
{
public:
	Player();
	~Player();
	//�÷��̾� ��ǥ
	int GetX()  { return x; }
	int GetY()  { return y; }
	void SetPosition(int newX, int newY) {
		x = newX;
		y = newY;
	}

	static bool IsInPlayerRange(int tileX, int tileY, int playerX, int playerY);  //�÷��̾� ���� 
	void RenderInventory(HDC hdc, int screenWidth, int screenHeight);  //�÷��̾� �Ʒ� �κ�â(����) ������
	void AddItem(CropType type);		//�κ��丮�� ������ �߰�
	
	void Render(HDC hdc);	//�÷��̾� ������
	void PlayerUpdate();	//�÷��̾� ������Ʈ(�̵� ó��, ���� ��ȣ ����, ��Ŭ�� or ��Ŭ��, ���� �̹��� ����)
	void Playermove();		//�÷��̾� �̵� ó��
	void HandleToolSelection();		// ���� ��ȣ ����
	void HandleLeftClickAction();	// ��Ŭ�� 
	void HandleRightClickAction();  // ��Ŭ�� 
	void UpdateBitmap();			//���� �̹��� ����

	///PlayerUpdate()���� Ȯ�� ����
	void SetSelectedCrop(CropType type) { selectedCrop = type; }  //SetSelectedCrop ���õ� ������ Ÿ���� ������ 
	CropType GetSelectedCrop() const { return selectedCrop; } //GetSelectedCrop ���õ� ������ Ÿ�� ����  //���� ���x
	void SetSelectedTool(int t) { selectedTool = t; } //SetSelectedTool ���õ� ��ȣ�� ������
	int GetSelectedTool()  { return selectedTool; }  //GetSelectedTool ���õ� ��ȣ�� ��������

	//void RenderFullInventory(HDC hdc) {  //�κ��丮 ��ü ������ Inventory.h�� ����
	//	fullInventory.Render(hdc, 360, 100);  // ���ϴ� ��ġ�� UI ���
	//}

	void SetInventoryOpen(bool open) { isInventoryOpen = open; }
	bool IsInventoryOpen() const { return isInventoryOpen; }

	//�κ��丮 ���� ����
	InventoryItem* GetInventory() { return inventory; }

	void SetBoxOpen(bool open) { isBoxOpen = open; } //open�� true �Ǵ� false
	bool IsBoxOpen() const { return isBoxOpen; }
private:
	std::vector<HBITMAP>PLY; 
	bool isBoxOpen = false;
	bool isInventoryOpen = false;
	CropType selectedCrop = CropType::None; //���
	Direction currentDir = DOWN;	  //ó�� ������ �Ʒ��̴�
	InventoryItem inventory[9];
	//Inventory fullInventory;
	int selectedTool = 4; //
	int x = 39;
	int y = 170;
	int playersize = 35;
	HBITMAP hBmp = nullptr; // ��Ʈ�� �ڵ� �����
	HDC memDC = nullptr;
};

