#pragma once
#include "MyGameObject.h"
class MyBomb :
    public MyGameObject
{
public:
    BOOL Drop();
    CRect GetRect();
    int GetMove() const;
    void GetWindowsHeight(int x);

public:
    MyBomb(int x, int y);
    ~MyBomb();
private:
    static const int BOMB_HEIGHT = 20;
};

