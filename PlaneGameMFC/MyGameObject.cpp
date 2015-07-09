#include "stdafx.h"
#include "MyGameObject.h"


MyGameObject::MyGameObject(int x, int y, int h) : m_ptPos(x, y), hp(h)
{
    maxHp = hp;
}


MyGameObject::~MyGameObject()
{
}


CPoint MyGameObject::GetPoint()
{
    return m_ptPos;
}

int MyGameObject::GetHp() const
{
    return hp;
}

int MyGameObject::GetMaxHp() const
{
    return maxHp;
}

int MyGameObject::GetImagesWidth() const
{
    return imagesWidth;
}

int MyGameObject::GetImagesHeight() const
{
    return imagesHeight;
}

void MyGameObject::SetWindowsHeight(int x)
{
    windowsHeight = x;
}

void MyGameObject::SetPoint(int x, int y)
{
    m_ptPos.x = x;
    m_ptPos.y = y;
}

void MyGameObject::SetHp(int x)
{
    hp = x;
}