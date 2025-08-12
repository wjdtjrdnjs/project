#pragma once
#include <windows.h>
#include "Global.h" //�浹���� on/off
#include "WorldObject.h"
#include "InventoryItem.h"
class Player;
class NPC :public WorldObject
{
public:
	NPC();
	void SetTilePosition(int tileX, int tileY) override;
	void Render(HDC hdc, int tilesize) override;
	void RenderUI(HDC hdc);
	PlaceableType GetPlaceableType()const override;
	void SetPlayerToolbar(InventoryItem* toolbar);
	void OnInteract(Player* player);
	RECT GetCollisionRect();

	bool HandleClick(int mouseX, int mouseY, int num);//���콺 ��Ŭ�� ���� Ȯ��(�ڽ� ĭ or �÷��̾� ����)
	void HandleItemSlotLClick(InventoryItem* slot);//���콺 ��Ŭ������ ���԰� ���� ��� �ִ� ������ ó�� �Լ�
	void HandleItemSlotRClick(InventoryItem* slot);

private:
	int x, y;
	int Fencesize = 10;
	InventoryItem items[27];   // 3x9 �κ��丮 ����(�ӽ�)
	InventoryItem* playerToolbar;

	HBITMAP hBmp; // ��Ʈ�� �ڵ� �����
};