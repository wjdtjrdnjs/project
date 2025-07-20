#pragma once
#include <vector>
#include <Windows.h>
class CollisionManager
{
public:
	bool playerCollided( );  //플레이어 충돌 검사
	virtual std::vector<RECT> GetCollisionRects() const = 0;
	virtual ~CollisionManager() = default;
};

