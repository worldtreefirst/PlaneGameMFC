#pragma once
#include "MyGameObject.h"
#include "MyHpStrip.h"
class MyEnemy :
    public MyGameObject
{
public:
    int GetPointX();
    int GetPointY();
    void GetWindowsHeight(int x);
    BOOL Drop();
    BOOL Fire();

public:
    MyEnemy(int x, int y, int d = 1);
    ~MyEnemy();

public:
    MyHpStrip* enemyHp;

private:
    int lFire;
    int nFire;
    int planeType;
};

