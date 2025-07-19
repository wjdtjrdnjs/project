#pragma once
#include <vector>
#include "SingletonT.h"
class Player;
class Animal;
class Fence;
class Crop;
class GameObjectManager:public SingletonT<GameObjectManager>
{
public:
    void SetPlayer(Player* p) { player = p; }
    Player* GetPlayer() { return player; }

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


private:
	Player* player = nullptr;
	std::vector<Animal*> animals;
	std::vector<Fence*> fences;
	std::vector<Crop*> crops;
};

