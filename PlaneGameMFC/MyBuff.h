#pragma once
#include "MyGameObject.h"
class MyBuff :
    public MyGameObject
{
public:
    void SetType(int t);      //设置Buff类型
    int GetType() const;      //获取Buff类型
    BOOL Drop();              //是否被摧毁

public:
    MyBuff(int x, int y);
    ~MyBuff();
private:
    int type;                  //Buff类型
};

