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
    int           GetHp() const;
    int        GetMaxHp() const;
    int        GetMoveX() const;
    int        GetMoveY() const;
    int       GetDamage() const;
    int    GetHardLevel() const;
    int  GetImagesWidth() const;
    int GetImagesHeight() const;
    void            SetHp(int x);
    void         SetMaxHp(int x);
    void         SetMoveX(int x);
    void         SetMoveY(int y);
    void        SetDamage(int d);
    void     SetHardLevel(int l);
    void  SetPoint(int x, int y);
    void  SetWindowsWidth(int x);
    void SetWindowsHeight(int x);
    CPoint GetPoint();

public:
    CImage m_Images;
    static int HardLevel;
    static BOOL iAmTheGod;
protected:
    int hp;
    int maxHp;
    int damage;
    int windowsHeight;
    int windowsWidth;
    int imagesWidth;
    int imagesHeight;
    int moveX;
    int moveY;
    CPoint m_ptPos;
};


