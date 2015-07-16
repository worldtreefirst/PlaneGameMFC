#include "stdafx.h"
#include "MyEnemyBomb.h"
#include "resource.h"

MyEnemyBomb::MyEnemyBomb(int x, int y, int d, int mx, int my) : MyGameObject(x, y)
{
    m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_ENEMYBOMB);
    SetDamage(d);
    imagesWidth = 10;
    imagesHeight = 20;
    moveX = mx;
    moveY = my;
}


MyEnemyBomb::~MyEnemyBomb() { }

BOOL MyEnemyBomb::Drop()
{
    if (GetPoint().y > windowsHeight) return TRUE;
    return FALSE;
}