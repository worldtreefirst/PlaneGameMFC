#pragma once
#include "MyGameObject.h"
#include "MyHpStrip.h"
class MyEnemy :
    public MyGameObject
{
public:
    int GetPlaneType() const;
    BOOL Drop();
    BOOL Fire();

public:
    MyEnemy(int t, int windowsHeight, int windowsWidth);
    ~MyEnemy();

public:
    MyHpStrip* enemyHp;

private:
    int change;
    int lFire;
    int nFire;
    int planeType;
};

