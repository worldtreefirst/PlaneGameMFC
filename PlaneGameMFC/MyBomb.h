#pragma once
#include "MyGameObject.h"
class MyBomb :
    public MyGameObject
{
public: 
    BOOL Drop();                     //�Ƿ񱻴ݻ�

public:
    static int BombLevel;            //�����ȼ�
    MyBomb(int x, int y, int t, int mx, int my, int d);
    ~MyBomb();
};

