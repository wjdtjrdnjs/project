#pragma once
#include <windows.h>
#include "PlayerController.h"
#include "InventoryComponent.h"

class Player;
class Box;
class WorldMap;
class CollisionManager;

class PlayerController
{
public:
	PlayerController(Player* p, InventoryComponent* inv)
		: player(p), inventory(inv), collisionMgr(nullptr), box(nullptr), playerstop(false), selectedTool(0) {
	}
	void SetCollisionManager(CollisionManager* colMgr) {
		collisionMgr = colMgr;

	}
	void UpdatePlayer();	// �̵�, ���� ������Ʈ
	void Playermove();		//�÷��̾� �̵� ó��
	void HandleToolSelection();		// ���� ��ȣ ����
	void HandleLeftClickAction();	// ��Ŭ�� 
	void HandleRightClickAction();  // ��Ŭ�� 
	void HandleKeyDown(WPARAM wParam);
	InventoryComponent* GetInventory() { return inventory; }
	void SetStopped(bool ch) { playerstop = ch; }
	bool IsStopped() const { return playerstop; }

private:
	Player* player;
	InventoryComponent* inventory;
	CollisionManager* collisionMgr;
	Box* box;
	bool playerstop = FALSE;

	int selectedTool = 0;

};

