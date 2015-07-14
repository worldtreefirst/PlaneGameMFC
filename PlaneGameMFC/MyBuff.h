#pragma once
#include "MyGameObject.h"
class MyBuff :
    public MyGameObject
{
public:
    void SetType(int t);
    int GetType() const;
    BOOL Drop();

public:
    MyBuff(int x, int y);
    ~MyBuff();
private:
    int type;
};

