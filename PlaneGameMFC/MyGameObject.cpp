#include "stdafx.h"
#include "MyGameObject.h"


MyGameObject::MyGameObject(int x, int y) : m_ptPos(x, y)
{
}


MyGameObject::~MyGameObject()
{
}


CPoint MyGameObject::GetPoint()
{
    return m_ptPos;
}

void MyGameObject::SetPoint(int x, int y)
{
    m_ptPos.x = x;
    m_ptPos.y = y;
}

int MyGameObject::GetImagesWidth() const
{
    return imagesWidth;
}

int MyGameObject::GetImagesHeight() const
{
    return imagesHeight;
}

void MyGameObject::GetWindowsHeight(int x)
{
    windowsHeight = x;
}
