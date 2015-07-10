#include "stdafx.h"
#include "MyEnemyBomb.h"
#include "resource.h"

MyEnemyBomb::MyEnemyBomb(int x, int y) : MyGameObject(x, y)
{
    SetDamage(1);
    imagesWidth = 10;
    imagesHeight = 20;
    m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_ENEMYBOMB);
    moveX = 0;
    moveY = 10;
}


MyEnemyBomb::~MyEnemyBomb() { }

int MyEnemyBomb::GetMoveX() const { return moveX; }

int MyEnemyBomb::GetMoveY() const { return moveY; }

BOOL MyEnemyBomb::Drop()
{
    if (GetPoint().y > windowsHeight) return TRUE;
    return FALSE;
}

void MyEnemyBomb::GetWindowsHeight(int x)
{
    windowsHeight = x;
}