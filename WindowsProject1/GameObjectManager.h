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
    void Init(HWND hWnd);
    void Update();
    void Render(HDC hdc, HWND hWnd);

    void SetPlayer(Player* p) { player = p; }
    Player* GetPlayer() { return player; }

    void SetBox(Box* b) { box = b; }
    Box* GetBox() { return box; }

    void SetPlayerController(PlayerController* pc) { controller = pc; }
    PlayerController* GetPlayerController() { return controller; }
    WorldMap* GetWorldMap() const { return worldMap; }
    void AddAnimal(Animal* animal);
    void AddCrop(Crop* crop);
    void AddFence(Fence* fence);

    void UpdateAll();
    void RemoveCrop(Crop* crop);
    void RemoveFence(Fence* fence);

    std::vector<Animal*>& GetAnimals() { return animals; }
    std::vector<Crop*>& GetCrops() { return crops; }
    std::vector<Fence*>& GetFences() { return fences; }

    Crop* GetCropAt(int tileX, int tileY);
    Fence* GetFenceAt(int tileX, int tileY);
    void Release();

    /*void AddGameObject(GameObject* obj);
    void SetPlayerInsideHouse(bool inside);
    void RemoveGameObject(GameObject* obj);
    const std::vector<GameObject*>& GetAllObjects() const { return allObjects; }*/
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

