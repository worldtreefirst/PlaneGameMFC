#pragma once
#include "MyGameObject.h"
#include "MyHpStrip.h"
class MyBoss :
    public MyGameObject
{
public:
    BOOL Drop();     //�Ƿ񱻴ݻ�
    BOOL Fire();     //�Ƿ���Կ���
public:
    MyHpStrip* myBossHp;  //����BossѪ��
    MyBoss(int w, int h);
    ~MyBoss();
private:
    int nFire; 
    int lFire;
    int change;       //�ٶȸı�ʱ��
    BOOL fire;        
};