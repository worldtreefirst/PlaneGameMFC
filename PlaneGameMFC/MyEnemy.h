#pragma once
#include "MyGameObject.h"
#include "MyHpStrip.h"
class MyEnemy :
    public MyGameObject
{
public:
    int GetPointX();
    int GetPointY();
    int GetMoveX() const;
    int GetMoveY() const;
    void GetWindowsHeight(int x);
    BOOL Drop();
    BOOL Fire();

public:
    MyEnemy(int x, int y, int h);
    ~MyEnemy();

public:
    MyHpStrip* enemyHp;

private:
    int lFire;
    int nFire;
    int planeType;
};

