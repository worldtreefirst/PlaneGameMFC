#include "stdafx.h"
#include "MyBomb.h"
#include "resource.h"
#include "mmsystem.h"
#pragma comment(lib, "Winmm.lib")

MyBomb::MyBomb(int x, int y, int l) :MyGameObject(x, y)
{
    SetMoveX(0);
    SetDamage(l);
    SetMoveY(-10);
    SetBombLevel(l);
    switch (GetBombLevel())
    {
    case 1:
        imagesWidth = 20;
        imagesHeight = 30;
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_BOMB1);
        break;
    case 2:
        imagesWidth = 30;
        imagesHeight = 40;
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_BOMB2);
        break;
    }

    PlaySound((LPCWSTR)IDR_SHOOT, NULL, SND_ASYNC | SND_RESOURCE);
}

MyBomb::~MyBomb() { }

int MyBomb::GetMoveX() const { return moveX; }

int MyBomb::GetMoveY() const { return moveY; }

void MyBomb::GetWindowsHeight(int x) { windowsHeight = x; }

BOOL MyBomb::Drop()
{
    if (GetPoint().y + BOMB_HEIGHT < 0) return TRUE;
    return FALSE;
}
