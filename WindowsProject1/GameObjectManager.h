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
    void Init(HWND hWnd); // �ʱ�ȭ
    void Update(); //������Ʈ
    void Render(HDC hdc, HWND hWnd); //������

    // �÷��̾� ���� �� ��ȯ
    void SetPlayer(Player* p) { player = p; }
    Player* GetPlayer() { return player; }

    // ���� ���� �� ��ȯ
    void SetBox(Box* b) { box = b; }
    Box* GetBox() { return box; }
    // �÷��̾� ��Ʈ�ѷ� ���� �� ��ȯ
    void SetPlayerController(PlayerController* pc) { controller = pc; }
    PlayerController* GetPlayerController() { return controller; }

    // ����� ��ȯ
    WorldMap* GetWorldMap() const { return worldMap; }

    // ����, �۹�, ��Ÿ�� �߰�
    void AddAnimal(Animal* animal);
    void AddCrop(Crop* crop);
    void AddFence(Fence* fence);

    void UpdateAll(); // ��ü ��ü ������Ʈ

    // �۹�, ��Ÿ�� ����
    void RemoveCrop(Crop* crop);
    void RemoveFence(Fence* fence);

    // ���� ��ϵ� ����, �۹�, ��Ÿ�� ��� ��ȯ
    std::vector<Animal*>& GetAnimals() { return animals; }
    std::vector<Crop*>& GetCrops() { return crops; }
    std::vector<Fence*>& GetFences() { return fences; }

    // Ÿ�� ��ġ ���� �۹�, ��Ÿ�� Ž��
    Crop* GetCropAt(int tileX, int tileY);
    Fence* GetFenceAt(int tileX, int tileY);

    // �ڿ� ����
    void Release();

    // �Ϲ� ���� ������Ʈ ���
    void AddGameObject(GameObject* obj);

    // �÷��̾��� ��ġ ���� (�� ����/�ܺ�) ���� �� ��ȸ
    void SetPlayerInsideHouse(bool inside);
    bool IsPlayerInsideHouse() { return playerInsideHouse; }

    void RemoveGameObject(GameObject* obj);// �Ϲ� ���� ������Ʈ ����
    const std::vector<GameObject*>& GetAllObjects() const { return allObjects; } // ��ü ���� ������Ʈ ��� ��ȯ
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

