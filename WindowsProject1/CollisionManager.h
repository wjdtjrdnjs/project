#pragma once
#include <vector>
#include <Windows.h>
class CollisionManager
{
public:
	bool playerCollided( );  //�÷��̾� �浹 �˻�
	virtual std::vector<RECT> GetCollisionRects() const = 0;
	virtual ~CollisionManager() = default;
};

