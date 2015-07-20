#pragma once
#include "MyGameObject.h"
class MyEnemyBomb :
    public MyGameObject
{
public:
    BOOL Drop();             //是否被摧毁

public:
    MyEnemyBomb(int x, int y, int d, int mx, int my);
    ~MyEnemyBomb();

private:
    int BombV;               //子弹速度
};

