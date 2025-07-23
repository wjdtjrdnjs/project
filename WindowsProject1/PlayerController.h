#pragma once
#include <windows.h>
#include "InventoryComponent.h"

class Player;
class Box;
class CollisionManager;

class PlayerController
{
public:
	PlayerController(Player* p, InventoryComponent* inv) //�÷��̾���Ʈ�ѿ� �÷��̾�, �κ��丮 ������Ʈ�� ����
		: player(p), inventory(inv), collisionMgr(nullptr), box(nullptr), playerstop(false), selectedTool(0) {
	}
	void SetCollisionManager(CollisionManager* colMgr) { // �浹 �Ŵ��� ����
		collisionMgr = colMgr;

	}
	void UpdatePlayer();	// �÷��̾� ������Ʈ
	void Playermove();		//�÷��̾� �̵� ó��
	void HandleToolSelection();		// ���� ��ȣ �Է� ó��
	void HandleLeftClickAction();	// ��Ŭ�� ó��
	void HandleRightClickAction();  // ��Ŭ�� ó��
	InventoryComponent* GetInventory() { return inventory; } // �÷��̾� �κ��丮 ��ȯ

	//���� ���� �� �÷��̾� ������ ����
	void SetStopped(bool ch) { playerstop = ch; }
	bool IsStopped() const { return playerstop; }

	void UpdatePlayerToolFromInventory(); //�κ��丮���� ���õ� ���� ������ �÷��̾����� ����
private:
	Player* player;
	InventoryComponent* inventory;
	CollisionManager* collisionMgr;
	Box* box;
	bool playerstop = FALSE; //�÷��̾� �̵�/���� ����

	int selectedTool = 0; //���� ��ȣ

};

