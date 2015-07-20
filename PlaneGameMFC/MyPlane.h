#pragma once
#include "MyGameObject.h"
class MyPlane :
    public MyGameObject
{
public:
    void updatePoint();

    int GetLevel() const;       //��ҵȼ�
    int GetHorMotion() const;
    int GetVerMotion() const;
    void SetHorMotion(int nMotion);
    void SetVerMotion(int nMotion);
    void judgeEdge(int PAGE_WIDTH, int PAGE_HEIGHT, int WINDOWS_WIDTH, int WINDOWS_HEIGHT);  //�жϱ�Ե

    BOOL Drop();                
    BOOL Fire();                //�Ƿ���Կ���

public:
    MyPlane();
    ~MyPlane();

public:
    static int hp;                  //��ҵ�ǰѪ��
    static int maxHp;               //������Ѫ��
    static int myLevel;             //��ҵȼ�
    static int bombLevel;           //�����ȼ�
    static int minDamage;           //�����С�˺�
    static int maxDamage;           //�������˺�
    static int protectLevel;

private:
    int nFire;   //����ȴ�ʱ��
    int m_nHorMotion;//�ɻ�ˮƽ���з���0->��ֹ��1->�� -1->��
    int m_nVerMotion;//�ɻ���ֱ���з���0->��ֹ��1->�� -1->��
};

