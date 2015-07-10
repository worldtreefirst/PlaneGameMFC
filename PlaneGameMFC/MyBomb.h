#pragma once
#include "MyGameObject.h"
class MyBomb :
    public MyGameObject
{
public:
    BOOL Drop();
    CRect GetRect();
    int  GetMoveX() const;
    int  GetMoveY() const;
    void GetWindowsHeight(int x);

public:
    MyBomb(int x, int y, int l);
    ~MyBomb();
private:
    int damage;
    static const int BOMB_HEIGHT = 20;
};

