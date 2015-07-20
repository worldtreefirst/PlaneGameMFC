#pragma once
#include "MyGameObject.h"
class MyPlane :
    public MyGameObject
{
public:
    void updatePoint();

    int GetLevel() const;       //玩家等级
    int GetHorMotion() const;
    int GetVerMotion() const;
    void SetHorMotion(int nMotion);
    void SetVerMotion(int nMotion);
    void judgeEdge(int PAGE_WIDTH, int PAGE_HEIGHT, int WINDOWS_WIDTH, int WINDOWS_HEIGHT);  //判断边缘

    BOOL Drop();                
    BOOL Fire();                //是否可以开火

public:
    MyPlane();
    ~MyPlane();

public:
    static int hp;                  //玩家当前血量
    static int maxHp;               //玩家最大血量
    static int myLevel;             //玩家等级
    static int bombLevel;           //导弹等级
    static int minDamage;           //玩家最小伤害
    static int maxDamage;           //玩家最大伤害
    static int protectLevel;

private:
    int nFire;   //开火等待时间
    int m_nHorMotion;//飞机水平运行方向0->静止，1->右 -1->左
    int m_nVerMotion;//飞机垂直运行方向0->静止，1->上 -1->下
};

