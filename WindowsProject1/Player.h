#pragma once
#include <vector>
#include <map>
#include <windows.h>
#include <algorithm>
#include "resource.h"
#include "CropType.h"
#include "Crop.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "CollisionManager.h"
#include "PlaceableObject.h"

enum Direction { //�÷��̾� ����
	DOWN = 0,
	UP = 1,
	RIGHT = 2,
	LEFT = 3
};

class Player:public CollisionManager
{
public:
	Player();
	~Player();
	//�÷��̾� ��ǥ
	int GetX()  { return x; }
	int GetY()  { return y; }
	int GetWidth() { return x; }
	int GeGetHeighttX() { return x; }
	RECT GetBoundingBox()const;
	void RenderInventory(HDC hdc, int screenWidth, int screenHeight);  //�÷��̾� �Ʒ� �κ�â(����) ������
	void AddItem(CropType type);		//�κ��丮�� ������ �߰�

	std::vector<RECT>GetCollisionRects()const override;;

	void Render(HDC hdc);	//�÷��̾� ������
	void UpdatePlayer();	//�÷��̾� ������Ʈ(�̵� ó��, ���� ��ȣ ����, ��Ŭ�� or ��Ŭ��, ���� �̹��� ����)
	void Playermove();		//�÷��̾� �̵� ó��
	void HandleToolSelection();		// ���� ��ȣ ����
	void HandleLeftClickAction();	// ��Ŭ�� 
	void HandleRightClickAction();  // ��Ŭ�� 

	void SetSelectedCrop(CropType type) { selectedCrop = type; }  //SetSelectedCrop ���õ� ������ Ÿ���� ������ 
	CropType GetSelectedCrop() const { return selectedCrop; } //GetSelectedCrop ���õ� ������ Ÿ�� ����  //���� ���x
	void SetSelectedTool(int t) { selectedTool = t; } //SetSelectedTool ���õ� ��ȣ�� ������
	int GetSelectedTool()  { return selectedTool; }  //GetSelectedTool ���õ� ��ȣ�� ��������

	void RenderFullInventory(HDC hdc) {  //�κ��丮 ��ü ������ Inventory.h�� ����
		fullInventory.Render(hdc, 360, 100);  // ���ϴ� ��ġ�� UI ���
	}

	void SetInventoryOpen(bool open) { isInventoryOpen = open; }
	bool IsInventoryOpen() const { return isInventoryOpen; }

	//�κ��丮 ���� ����
	InventoryItem* GetInventory() { return inventory; }

	void SetBoxOpen(bool open) { isBoxOpen = open; } //open�� true �Ǵ� false
	bool IsBoxOpen() const { return isBoxOpen; }
private:
	std::map<Direction, std::vector<HBITMAP>> ply; // �÷��̾� ���� �̹���

	bool isBoxOpen = false;
	bool isInventoryOpen = false;
	CropType selectedCrop = CropType::None; //���
	Direction currentDir = DOWN;	  //ó�� ������ �Ʒ��̴�
	InventoryItem inventory[9];
	Inventory fullInventory;
	int selectedTool = 0; //
	int x = 39;
	int y = 170;
	int playersize = 35;
	HBITMAP hBmp = nullptr; // ��Ʈ�� �ڵ� �����
	HDC memDC = nullptr;
};

