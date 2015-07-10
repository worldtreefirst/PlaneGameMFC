#pragma once
#include "MyGameObject.h"
class MyExplosion :
    public MyGameObject
{
public:
    BOOL Drop();
    int GetMoveX() const;
    int GetMoveY() const;
    void UpDateStates();

public:
    MyExplosion(int x, int y);
    ~MyExplosion();

private:
    int nStates;

};
