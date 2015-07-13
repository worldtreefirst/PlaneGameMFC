#pragma once
#include "MyGameObject.h"
class MyExplosion :
    public MyGameObject
{
public:
    BOOL Drop();
    void UpDateStates();
    int GetStates() const ;

public:
    MyExplosion(int x, int y);
    ~MyExplosion();

private:
    int nStates;

};
