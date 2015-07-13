#pragma once
#include "MyGameObject.h"
class MyEnemyBomb :
    public MyGameObject
{
public:
    BOOL Drop();
    void GetWindowsHeight(int x);

public:
    MyEnemyBomb(int x, int y, int d);
    ~MyEnemyBomb();

private:
    int BombV;

};

