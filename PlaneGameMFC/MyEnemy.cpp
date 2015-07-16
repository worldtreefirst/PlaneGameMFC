#include "stdafx.h"
#include "MyEnemy.h"
#include "resource.h"

#define HARD_LEVEL MyGameObject::HardLevel

MyEnemy::MyEnemy(int t, int windowsHeight, int windowsWidth) : planeType(t)
{
    srand((unsigned)time(NULL));
    m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_ENEMY1 + rand() % 9);
    imagesWidth = 40 + planeType * 20;
    imagesHeight = 40 + planeType * 20;
    if (rand() % 100 < 75)
    {
        moveX = 0;
        moveY = rand() % 2 + 8 - planeType * 2;
        SetPoint(rand() % (windowsWidth - imagesWidth), -imagesHeight);
    }
    else
    {
        if (rand() % 2)
        {
            moveY = rand() % 2 + 6 - planeType * 2;
            moveX = rand() % (moveY + 1) + 1;
            moveY = rand() % 2 + 6 - planeType * 2;
            SetPoint(-imagesWidth, rand() % (windowsHeight / 4) - imagesHeight);
        }
        else
        {
            moveX = rand() % (moveY + 1) + 1;
            moveX = rand() % moveY + 1;
            moveY = rand() % 2 + 6 - planeType * 2;
            SetPoint(windowsWidth, rand() % (windowsHeight / 4) - imagesHeight);
        }
    }
    SetHp(20 + 10 * HARD_LEVEL * planeType * planeType);
    SetMaxHp(20 + 10 * HARD_LEVEL * planeType * planeType);
    SetDamage(20 + rand() % (HARD_LEVEL * (4 - planeType)) + 2 * HARD_LEVEL * (4 - planeType));
    change = rand() % 100 + 100;
    lFire = rand() % 150 + 50;
    nFire = rand() % lFire + t * 10;
    //moveX = 0;
    //moveY = rand() % 5 + 3;
    enemyHp = new MyHpStrip;
}


MyEnemy::~MyEnemy() { delete enemyHp; }

BOOL MyEnemy::Drop() 
{
    if (planeType == 3 && GetPoint().y > rand() % (windowsHeight / 4) + imagesHeight + 30)
    {
        moveX = 0;
        moveY = 0;
    }
    if (nFire) nFire++;
    if (nFire > lFire) nFire = 0;
    if (GetPoint().y > windowsHeight) return TRUE;
    if (moveX <= 0 && GetPoint().x + imagesWidth < 0) return TRUE;
    if (moveX >0 && GetPoint().x > windowsWidth) return TRUE;
    return FALSE;
}

BOOL MyEnemy::Fire()
{
    SetDamage(20 + rand() % (HARD_LEVEL * (4 - planeType)) + HARD_LEVEL * (4 - planeType));
    if (!nFire)
    {
        nFire++;
        return TRUE;
    }
    return FALSE;
}

int MyEnemy::GetPlaneType() const { return planeType; }