#pragma once
#include "MyGameObject.h"
class MyExplosion :
    public MyGameObject
{
public:
    BOOL Drop();                 //是否被摧毁
    void UpDateStates();         //更新位标
    int GetStates() const ;

public:
    MyExplosion(int x, int y, int width, int height);
    ~MyExplosion();

private:
    int nStates;                  //当前位标
};
