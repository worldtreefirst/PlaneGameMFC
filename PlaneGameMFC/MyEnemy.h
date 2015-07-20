#pragma once
#include "MyGameObject.h"
#include "MyHpStrip.h"
class MyEnemy :
    public MyGameObject
{
public:
    int GetPlaneType() const;         //��ȡ�л�����
    BOOL Drop();                      //�Ƿ񱻴ݻ�
    BOOL Fire();                      //�Ƿ���Կ���

public:
    MyEnemy(int t, int windowsHeight, int windowsWidth);
    ~MyEnemy();

public:
    MyHpStrip* enemyHp;               //Ѫ��

private:
    int lFire;
    int nFire;                        //�Ƿ���Կ���
    int planeType;                    //�л�����
};

