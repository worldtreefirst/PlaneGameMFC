#pragma once
#include "MyGameObject.h"
class MyBuff :
    public MyGameObject
{
public:
    void SetType(int t);      //����Buff����
    int GetType() const;      //��ȡBuff����
    BOOL Drop();              //�Ƿ񱻴ݻ�

public:
    MyBuff(int x, int y);
    ~MyBuff();
private:
    int type;                  //Buff����
};

