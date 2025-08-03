#pragma once
#include "SingletonT.h"
#include "PlayerInventory.h"
#include "Box.h"

class UIManager : public SingletonT<UIManager>  // ✅ 싱글톤 상속
{
    friend class SingletonT<UIManager>;  // protected 생성자 접근 허용

public:
    void OpenBoxUI(Box* box, PlayerInventory* playerInv);
    void CloseBoxUI();
    void Update(float deltaTime);


    //렌더모임
    void Render(HDC hdc);
    void RenderInventory(HDC hdc);
    void RenderBoxUI(HDC hdc, Box* box);

    void HandleClick(int mouseX, int mouseY, bool isRightClick);
    bool IsBoxUIOpen() const { return isBoxUIOpen; }
    void SetPlayerInventory(PlayerInventory* inv);
   
    

private:
    UIManager() = default;          // SingletonT로 생성 제한
    ~UIManager() = default;

    PlayerInventory* playerInventory = nullptr;
    Box* openedBox = nullptr;

    bool isBoxUIOpen = false;
    int baseX = 100;
    int baseY = 100;


    void DrawInventoryGrid(HDC hdc, InventoryItem* items, int baseX, int baseY);
    void DrawToolbar(HDC hdc, InventoryItem* toolbar, int baseX, int baseY);
    void DrawHeldItem(HDC hdc);

};
