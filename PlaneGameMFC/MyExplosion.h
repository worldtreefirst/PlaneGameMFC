#pragma once
#include "MyGameObject.h"
class MyExplosion :
    public MyGameObject
{
public:
    BOOL Drop();                 //�Ƿ񱻴ݻ�
    void UpDateStates();         //����λ��
    int GetStates() const ;

public:
    MyExplosion(int x, int y, int width, int height);
    ~MyExplosion();

private:
    int nStates;                  //��ǰλ��
};
