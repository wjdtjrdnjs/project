#pragma once
#include <vector>
#include "SingletonT.h"
#include "PlayerController.h"
class Player;
class GameObject;
class Box;
class Fence;
class WorldMap;
class Crop;
class PlayerController;
class InventoryComponent;
class House;
class Animal;
class GameObjectManager:public SingletonT<GameObjectManager>
{
public:

    static GameObjectManager& Instance();
    void Init(HWND hWnd); // 초기화
    void Update(); //업데이트
    void Render(HDC hdc, HWND hWnd); //렌더링

    // 플레이어 설정 및 반환
    void SetPlayer(Player* p) { player = p; }
    Player* GetPlayer() { return player; }

    // 상자 설정 및 반환
    void SetBox(Box* b) { box = b; }
    Box* GetBox() { return box; }
    // 플레이어 컨트롤러 설정 및 반환
    void SetPlayerController(PlayerController* pc) { controller = pc; }
    PlayerController* GetPlayerController() { return controller; }

    // 월드맵 반환
    WorldMap* GetWorldMap() const { return worldMap; }

    // 동물, 작물, 울타리 추가
    void AddAnimal(Animal* animal);
    void AddCrop(Crop* crop);
    void AddFence(Fence* fence);

    void UpdateAll(); // 전체 객체 업데이트

    // 작물, 울타리 제거
    void RemoveCrop(Crop* crop);
    void RemoveFence(Fence* fence);

    // 현재 등록된 동물, 작물, 울타리 목록 반환
    std::vector<Animal*>& GetAnimals() { return animals; }
    std::vector<Crop*>& GetCrops() { return crops; }
    std::vector<Fence*>& GetFences() { return fences; }

    // 타일 위치 기준 작물, 울타리 탐색
    Crop* GetCropAt(int tileX, int tileY);
    Fence* GetFenceAt(int tileX, int tileY);

    // 자원 해제
    void Release();

    // 일반 게임 오브젝트 등록
    void AddGameObject(GameObject* obj);

    // 플레이어의 위치 상태 (집 내부/외부) 설정 및 조회
    void SetPlayerInsideHouse(bool inside);
    bool IsPlayerInsideHouse() { return playerInsideHouse; }

    void RemoveGameObject(GameObject* obj);// 일반 게임 오브젝트 제거
    const std::vector<GameObject*>& GetAllObjects() const { return allObjects; } // 전체 게임 오브젝트 목록 반환
private:
	Player* player = nullptr;
	std::vector<Animal*> animals;
	std::vector<Fence*> fences;
	std::vector<Crop*> crops;
    InventoryUIController* uiController = nullptr;
    PlayerController* controller = nullptr;
    InventoryComponent* inventory = nullptr;
    Box* box = nullptr;
    WorldMap* worldMap = nullptr;
    House* house = nullptr;
    Animal* animal = nullptr;
    bool playerInsideHouse = false;
    std::vector<GameObject*> allObjects;
    HWND hWnd = nullptr;
};

