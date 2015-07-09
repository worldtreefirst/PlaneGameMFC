#include "stdafx.h"
#include "MyEnemyBomb.h"
#include "resource.h"

MyEnemyBomb::MyEnemyBomb(int x, int y) : MyGameObject(x, y)
{
    imagesWidth = 10;
    imagesHeight = 20;
    m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_ENEMYBOMB);
    BombV = 10;
}


MyEnemyBomb::~MyEnemyBomb()
{
}

int MyEnemyBomb::GetMove() const
{
    return BombV;
}

BOOL MyEnemyBomb::Drop()
{
    if (GetPoint().y > windowsHeight) return TRUE;
    return FALSE;
}

void MyEnemyBomb::GetWindowsHeight(int x)
{
    windowsHeight = x;
}