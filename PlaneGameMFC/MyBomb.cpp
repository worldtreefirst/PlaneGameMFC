#include "stdafx.h"
#include "MyBomb.h"
#include "resource.h"
#include "mmsystem.h"
#pragma comment(lib, "Winmm.lib")

MyBomb::MyBomb(int x, int y) :MyGameObject(x, y)
{
    imagesWidth = 30;
    imagesHeight = 40;
    m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_BOMB1);
    PlaySound((LPCWSTR)IDR_SHOOT, NULL, SND_ASYNC | SND_RESOURCE);
}

MyBomb::~MyBomb()
{
}

int MyBomb::GetMove() const
{
    return -10;
}

BOOL MyBomb::Drop()
{
    if (GetPoint().y + BOMB_HEIGHT < 0) return TRUE;
    return FALSE;
}

void MyBomb::GetWindowsHeight(int x)
{
    windowsHeight = x;
}