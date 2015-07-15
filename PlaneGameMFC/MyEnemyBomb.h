#pragma once
#include "MyGameObject.h"
class MyEnemyBomb :
    public MyGameObject
{
public:
    BOOL Drop();

public:
    MyEnemyBomb(int x, int y, int d, int mx, int my);
    ~MyEnemyBomb();

private:
    int BombV;

};

