#pragma once
#include "afx.h"
class MyGameObject :
    public CObject
{
public:
    virtual ~MyGameObject();
    virtual BOOL Drop() = 0;
    virtual int GetMove() const = 0;

public:
    MyGameObject(int x = 0, int y = 0, int h = 1);
    int GetHp()const;
    int GetMaxHp() const;
    int GetImagesWidth() const;
    int GetImagesHeight() const;
    void SetPoint(int x, int y);
    void SetWindowsHeight(int x);
    void SetHp(int x);
    CPoint GetPoint();

public:
    CImage m_Images;
protected:
    int hp;
    int maxHp;
    int windowsHeight;
    int imagesWidth;
    int imagesHeight;
    CPoint  m_ptPos;
};


