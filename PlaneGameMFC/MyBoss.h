#pragma once
#include "MyGameObject.h"
#include "MyHpStrip.h"
class MyBoss :
    public MyGameObject
{
public:
    BOOL Drop();     //是否被摧毁
    BOOL Fire();     //是否可以开火
public:
    MyHpStrip* myBossHp;  //加载Boss血条
    MyBoss(int w, int h);
    ~MyBoss();
private:
    int nFire; 
    int lFire;
    int change;       //速度改变时间
    BOOL fire;        
};