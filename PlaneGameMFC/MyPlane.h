#pragma once
#include "MyGameObject.h"
class MyPlane :
    public MyGameObject
{
public:
    void updatePoint();

    int GetPointX();
    int GetPointY();
    int GetMove() const;
    int GetFire() const;
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
private:
    int    nFire;
    int    m_nHorMotion;//�ɻ�ˮƽ���з���0->��ֹ��1->�� -1->��
    int    m_nVerMotion;//�ɻ���ֱ���з���0->��ֹ��1->�� -1->��
};
