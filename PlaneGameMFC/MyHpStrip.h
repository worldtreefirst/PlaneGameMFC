#pragma once
#include "MyGameObject.h"
class MyHpStrip :
    public MyGameObject
{
public:
    BOOL Drop();

public:
    MyHpStrip();
    ~MyHpStrip();
};

