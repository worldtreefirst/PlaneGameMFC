#include "stdafx.h"
#include "MyExplosion.h"
#include "resource.h"

MyExplosion::MyExplosion(int x, int y) : MyGameObject(x, y)
{
    imagesWidth = 60;
    imagesHeight = 60;
    nStates = 0;
    m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_EXP);
}

MyExplosion::~MyExplosion()
{
}

BOOL MyExplosion::Drop()
{
    if (nStates == 7) return TRUE;
    return FALSE;
}

int MyExplosion::GetMove() const
{
    return nStates;
}

void MyExplosion::UpDateStates()
{
    nStates++;
}