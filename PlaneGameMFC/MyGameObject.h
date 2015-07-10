#pragma once
#include "afx.h"
class MyGameObject :
    public CObject
{
public:
    virtual ~MyGameObject();
    virtual BOOL Drop() = 0;
    virtual int GetMoveX() const = 0;
    virtual int GetMoveY() const = 0;

public:
    MyGameObject(int x = 0, int y = 0, int h = 1, int l = 1);
    int           GetHp() const;
    int        GetMaxHp() const;
    int       GetDamage() const;
    int    GetHardLevel() const;
    int    GetBombLevel() const;
    int  GetImagesWidth() const;
    int GetImagesHeight() const;
    void            SetHp(int x);
    void         SetMoveX(int x);
    void         SetMoveY(int y);
    void        SetDamage(int d);
    void     SetHardLevel(int l);
    void     SetBombLevel(int l);
    void  SetPoint(int x, int y);
    void SetWindowsHeight(int x);
    CPoint GetPoint();

public:
    CImage m_Images;
protected:
    int hp;
    int maxHp;
    int damage;
    int HardLevel;
    int BombLevel;
    int windowsHeight;
    int imagesWidth;
    int imagesHeight;
    int moveX;
    int moveY;
    CPoint  m_ptPos;
};


