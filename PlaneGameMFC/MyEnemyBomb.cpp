#include "stdafx.h"
#include "MyEnemyBomb.h"
#include "resource.h"

MyEnemyBomb::MyEnemyBomb(int x, int y, int d) : MyGameObject(x, y)
{
    SetDamage(d);
    imagesWidth = 10;
    imagesHeight = 20;
    m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_ENEMYBOMB);
    moveX = 0;
    moveY = 10;
}


MyEnemyBomb::~MyEnemyBomb() { }

BOOL MyEnemyBomb::Drop()
{
    if (GetPoint().y > windowsHeight) return TRUE;
    return FALSE;
}

void MyEnemyBomb::GetWindowsHeight(int x)
{
    windowsHeight = x;
}