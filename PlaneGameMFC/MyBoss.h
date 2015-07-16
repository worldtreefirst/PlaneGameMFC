#pragma once
#include "MyGameObject.h"
#include "MyHpStrip.h"
class MyBoss :
    public MyGameObject
{
public:
    BOOL Drop();
    BOOL Fire();
public:
    MyHpStrip* myBossHp;
    MyBoss(int w, int h);
    ~MyBoss();
private:
    int nFire;
    int lFire;
    int change;
    BOOL fire;
};

