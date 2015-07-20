#pragma once
#include "afx.h"
class MyGameObject :
    public CObject
{
public:
    virtual ~MyGameObject();
    virtual BOOL Drop() = 0;

public:
    MyGameObject(int x = 0, int y = 0);
    int GetHp() const;                       //��ȡ��λ��ǰѪ��
    int GetMaxHp() const;                    //��ȡ��λ���Ѫ��
    int GetMoveX() const;                    //��ȡX���ƶ��ٶ�
    int GetMoveY() const;                    //��ȡY���ƶ��ٶ�
    int GetDamage() const;                   //��ȡ��λ�˺�
    int GetHardLevel() const;                //��ȡ�Ѷȵȼ�
    int GetImagesWidth() const;              //��ȡ��ͼ���
    int GetImagesHeight() const;             //��ȡ��ͼ�߶�
    void SetHp(int x);                       //���õ�λ��ǰѪ��
    void SetMaxHp(int x);                    //���õ�λ���Ѫ��
    void SetMoveX(int x);                    //����X���ƶ��ٶ�
    void SetMoveY(int y);                    //����Y���ƶ��ٶ�
    void SetDamage(int d);                   //���õ�λ�˺�
    void SetPoint(int x, int y);             //���õ÷�
    void SetWindowsWidth(int x);             //���õ�ǰ���ڿ��
    void SetWindowsHeight(int x);            //���õ�ǰ���ڸ߶�
    CPoint GetPoint();                       //��ȡ��λ����

public: 
    CImage m_Images;                         //��λ��ͼ
    static int HardLevel;                    //�Ѷȵȼ�
    static BOOL beginGame;                   //��Ϸ��ʼ���
    static BOOL iAmTheGod;                   //�޵�ģʽ���
protected:
    int hp;                                  //��λ��ǰѪ��
    int maxHp;                               //��λ���Ѫ��
    int damage;                              //��λ�˺�
    int windowsHeight;                       //��ǰ���ڸ߶�
    int windowsWidth;                        //��ǰ���ڿ��
    int imagesWidth;                         //��ǰ��ͼ���
    int imagesHeight;                        //��ǰ��ͼ�߶�
    int moveX;                               //��λX���ƶ��ٶ�
    int moveY;                               //��λY���ƶ��ٶ�
    CPoint m_ptPos;                          //��λ����
};


