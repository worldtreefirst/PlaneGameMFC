#pragma once
#include "MyGameObject.h"
class MyBoss :
    public MyGameObject
{
public:
    BOOL Drop();
public:
    MyBoss();
    ~MyBoss();
};

