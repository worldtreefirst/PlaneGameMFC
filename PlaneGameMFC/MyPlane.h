#pragma once
#include "MyGameObject.h"
class MyPlane :
    public MyGameObject
{
public:
    void updatePoint();

    int  GetFire() const;
    int GetLevel() const;
    int GetHorMotion() const;
    int GetVerMotion() const;
    void SetHorMotion(int nMotion);
    void SetVerMotion(int nMotion);
    void judgeEdge(int PAGE_WIDTH, int PAGE_HEIGHT, int WINDOWS_WIDTH, int WINDOWS_HEIGHT);

    BOOL Drop();
    BOOL Fire();

public:
    MyPlane();
    ~MyPlane();

public:
    static const int PLANE_WIDTH = 60;
    static const int PLANE_HEIGHT = 60;

public:
    static int          hp;
    static int       maxHp;
    static int     myLevel;
    static int   bombLevel;
    static int   minDamage;
    static int   maxDamage;
    static int protectLevel;

private:
    int level;
    int nFire;
    int m_nHorMotion;//飞机水平运行方向0->静止，1->右 -1->左
    int m_nVerMotion;//飞机垂直运行方向0->静止，1->上 -1->下
};

