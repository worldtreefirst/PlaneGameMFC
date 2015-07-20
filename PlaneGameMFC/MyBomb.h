#pragma once
#include "MyGameObject.h"
class MyBomb :
    public MyGameObject
{
public: 
    BOOL Drop();                     //是否被摧毁

public:
    static int BombLevel;            //导弹等级
    MyBomb(int x, int y, int t, int mx, int my, int d);
    ~MyBomb();
};

