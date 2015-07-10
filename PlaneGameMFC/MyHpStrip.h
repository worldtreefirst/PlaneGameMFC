#pragma once
#include "MyGameObject.h"
class MyHpStrip :
    public MyGameObject
{
public:
    BOOL Drop();
    int GetMoveX() const;
    int GetMoveY() const;

public:
    MyHpStrip();
    ~MyHpStrip();
};

