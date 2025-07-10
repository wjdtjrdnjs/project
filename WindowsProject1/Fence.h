#pragma once
#include "resource.h"
#include <windows.h>
class Fence
{
public:
	Fence();
	~Fence();
	void Render(HDC hdc);

private:
	int x = 0;
	int y = 0;
};

