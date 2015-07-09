#pragma once
#include "MyGameObject.h"
class MyEnemy :
    public MyGameObject
{
public:
    int GetPointX();
    int GetPointY();
    int GetMove() const;
    void GetWindowsHeight(int x);
    BOOL Drop();
    BOOL Fire();

public:
    MyEnemy(int x, int y);
    ~MyEnemy();

private:
    int nFire;
    int planeV;
    int planeType;
};

