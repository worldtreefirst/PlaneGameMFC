#pragma once
#include "MyGameObject.h"
class MyBomb :
    public MyGameObject
{
public:
    BOOL Drop();
    CRect GetRect();
    void GetWindowsHeight(int x);

public:
    static int BombLevel;
    MyBomb(int x, int y, int l, int mx, int my);
    ~MyBomb();
private:
    int damage;
    static const int BOMB_HEIGHT = 20;
};

