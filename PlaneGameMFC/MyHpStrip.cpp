#include "stdafx.h"
#include "MyHpStrip.h"
#include "Resource.h"

MyHpStrip::MyHpStrip()
{
    moveX = 0;
    moveY = 0;
    imagesWidth = 60;
    imagesHeight = 10;
    m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_MYHEROHP);
}


MyHpStrip::~MyHpStrip() { }

int MyHpStrip::GetMoveX() const { return moveX; }

int MyHpStrip::GetMoveY() const { return moveY; }

BOOL MyHpStrip::Drop()
{
    return TRUE;
}