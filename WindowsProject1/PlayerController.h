#pragma once
#include <windows.h>
#include "InventoryComponent.h"

class Player;
class Box;
class CollisionManager;

class PlayerController
{
public:
	PlayerController(Player* p, InventoryComponent* inv) //플레이어컨트롤에 플레이어, 인벤토리 컴포넌트를 주입
		: player(p), inventory(inv), collisionMgr(nullptr), box(nullptr), playerstop(false), selectedTool(0) {
	}
	void SetCollisionManager(CollisionManager* colMgr) { // 충돌 매니저 설정
		collisionMgr = colMgr;

	}
	void UpdatePlayer();	// 플레이어 업데이트
	void Playermove();		//플레이어 이동 처리
	void HandleToolSelection();		// 툴바 번호 입력 처리
	void HandleLeftClickAction();	// 좌클릭 처리
	void HandleRightClickAction();  // 우클릭 처리
	InventoryComponent* GetInventory() { return inventory; } // 플레이어 인벤토리 반환

	//상자 오픈 시 플레이어 움직임 멈춤
	void SetStopped(bool ch) { playerstop = ch; }
	bool IsStopped() const { return playerstop; }

	void UpdatePlayerToolFromInventory(); //인벤토리에서 선택된 도구 정보를 플레이어한테 전달
private:
	Player* player;
	InventoryComponent* inventory;
	CollisionManager* collisionMgr;
	Box* box;
	bool playerstop = FALSE; //플레이어 이동/정지 상태

	int selectedTool = 0; //툴바 번호

};

