#include "stdafx.h"
#include "MyBoss.h"
#include "Resource.h"
#include "MyGameObject.h"
#include "MyHpStrip.h"

#define HARD_LEVEL MyGameObject::HardLevel

MyBoss::MyBoss(int w, int h) : MyGameObject(rand() % (w - 200), -150)
{
    srand((unsigned)time(NULL));
    m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_BOSS1 + rand() % 6);
    windowsWidth = w;
    windowsHeight = h;
    imagesWidth = 200;
    imagesHeight = 150;
    moveX =  0;
    moveY = 10;
    //SetPoint(0, 0);
    SetDamage(rand() % HARD_LEVEL + HARD_LEVEL);
    SetHp(HARD_LEVEL * 500);
    SetMaxHp(HARD_LEVEL * 500);
    myBossHp = new MyHpStrip;
    change = rand() % 250 + 100;
    nFire = rand() % 10 + 121 - HARD_LEVEL;
    lFire = rand() % nFire;
}

MyBoss::~MyBoss()
{
}

BOOL MyBoss::Drop()
{
    return FALSE;
}

BOOL MyBoss::Fire()
{
    SetDamage(rand() % HARD_LEVEL + HARD_LEVEL);
    if (GetPoint().y > rand()%(windowsHeight / 8) + 100)
    {
        moveY = 0;
    }
    if (moveY == 0) {
        if (moveX > 0 && GetPoint().x + imagesWidth >= windowsWidth)
            moveX = -moveX;
        if (moveX < 0 && GetPoint().x <= 0)
            moveX = -moveX;
        change--;
    }
    if (change <= 0)
    {
        change = rand() % 150 + 100 - HARD_LEVEL;
        if (!moveX)
            moveX = rand() % 10 + 1;
        else
            moveX = 0;
        if (rand() % 2) { moveX = -moveX; }
    }
    lFire++;
    if (lFire > nFire) 
    {
        lFire = 0;
        return TRUE;
    }
    return FALSE;
}