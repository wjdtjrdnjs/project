#pragma once
#include "resource.h"
#include "Crop.h"
#include <windows.h>
#include <vector>
#include <algorithm>
enum Direction { //�÷��̾� ����
	DOWN = 0,
	UP = 1,
	RIGHT = 2,
	LEFT = 3
};
struct InventoryItem {  //�÷��̾� �κ��丮 (�Ʒ� 9ĭ)
	CropType type = CropType::None;  //������ Ÿ��
	int count = 0;		//������ ���� 
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

	static bool IsInPlayerRange(int tileX, int tileY, int playerX, int playerY);  //�÷��̾� ���� Ȯ�ο�
	void RenderInventory(HDC hdc, int screenWidth, int screenHeight);  //�÷��̾� �Ʒ� �κ�â(����) �Լ�
	void AddItem(CropType type); //�κ��丮 ������ �߰�
	
	void Render(HDC hdc); //�÷��̾� �׸�
	void PlayerUpdate(); //�÷��̾� �ൿ

	///PlayerUpdate()���� Ȯ�� ����
	void SetSelectedCrop(CropType type) { selectedCrop = type; }  //SetSelectedCrop ���õ� ������ Ÿ���� ������ 
	CropType GetSelectedCrop() const { return selectedCrop; } //GetSelectedCrop ���õ� ������ Ÿ�� ����
	void SetSelectedTool(int t) { selectedTool = t; } //SetSelectedTool ���õ� ��ȣ�� ������
	int GetSelectedTool()  { return selectedTool; }  //GetSelectedTool ���õ� ��ȣ�� ��������
	
	//�κ��丮 ���� ����
	InventoryItem* GetInventory() { return inventory; }

	void SetBoxOpen(bool open) { isBoxOpen = open; } //open�� true �Ǵ� false
	bool IsBoxOpen() const { return isBoxOpen; }
private:
	std::vector<HBITMAP>PLY; 
	bool isBoxOpen = false;
	
	CropType selectedCrop = CropType::Strawberry; //ó���� ���⸦ ����ִ´�
	Direction currentDir = DOWN;	  //ó�� ������ �Ʒ��̴�
	InventoryItem inventory[9];
	int selectedTool = 4; //
	int x = 100;
	int y = 100;
	int playersize = 35;
	HBITMAP hBmp = nullptr; // ��Ʈ�� �ڵ� �����
	HDC memDC = nullptr;
};

