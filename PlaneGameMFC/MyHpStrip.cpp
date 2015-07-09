#include "stdafx.h"
#include "MyHpStrip.h"
#include "Resource.h"

MyHpStrip::MyHpStrip()
{
    imagesWidth = 60;
    imagesHeight = 10;
    m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_MYHEROHP);
}


MyHpStrip::~MyHpStrip()
{
}

int MyHpStrip::GetMove() const
{
    return 0;
}

BOOL MyHpStrip::Drop()
{
    return TRUE;
}