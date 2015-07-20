#pragma once
#include "MyGameObject.h"
#include "MyHpStrip.h"
class MyEnemy :
    public MyGameObject
{
public:
    int GetPlaneType() const;         //获取敌机类型
    BOOL Drop();                      //是否被摧毁
    BOOL Fire();                      //是否可以开火

public:
    MyEnemy(int t, int windowsHeight, int windowsWidth);
    ~MyEnemy();

public:
    MyHpStrip* enemyHp;               //血条

private:
    int lFire;
    int nFire;                        //是否可以开火
    int planeType;                    //敌机类型
};

