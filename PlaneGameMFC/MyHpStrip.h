#pragma once
#include "MyGameObject.h"
class MyHpStrip :
    public MyGameObject
{
public:
    BOOL Drop();
    int GetMove() const;

public:
    MyHpStrip();
    ~MyHpStrip();
};

