#include "stdafx.h"
#include "MyEnemy.h"
#include "resource.h"

MyEnemy::MyEnemy(int x, int y, int h) : MyGameObject(x, y, h)
{
    imagesWidth = 60;
    imagesHeight = 60;
    windowsHeight = 0;
    srand((unsigned)time(NULL));
    for (int i = 0; i < rand() % 5; i++) srand((unsigned)time(NULL));;
    planeType = rand() % 3 + 1;
    switch (planeType)
    {
    case 1:
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_ENEMY1);
        break;
    case 2:
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_ENEMY2);
        break;
    case 3:
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_ENEMY3);
        break;
    }
    lFire = rand() % 50 + 50;
    nFire = rand() % lFire + 1;
    planeV = rand() % 5 + 3;
    enemyHp = new MyHpStrip;
}


MyEnemy::~MyEnemy()
{
    delete enemyHp;
}

int MyEnemy::GetMove() const
{
    return planeV;
}

void MyEnemy::GetWindowsHeight(int x)
{
    windowsHeight = x;
}

BOOL MyEnemy::Drop()
{
    if (nFire) nFire++;
    if (nFire > lFire) nFire = 0;
    if (GetPoint().y > windowsHeight) return TRUE;
    return FALSE;
}

BOOL MyEnemy::Fire()
{
    if (!nFire)
    {
        nFire++;
        return TRUE;
    }
    return FALSE;
}
