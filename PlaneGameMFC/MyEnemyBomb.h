#pragma once
#include "MyGameObject.h"
class MyEnemyBomb :
    public MyGameObject
{
public:
    BOOL Drop();
    int GetMove() const;
    void GetWindowsHeight(int x);

public:
    MyEnemyBomb(int x, int y);
    ~MyEnemyBomb();

private:
    int BombV;

};

