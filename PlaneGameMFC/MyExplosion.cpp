#include "stdafx.h"
#include "MyExplosion.h"
#include "resource.h"

MyExplosion::MyExplosion(int x, int y, int width, int height) : MyGameObject(x, y)
{
    imagesWidth = width;
    imagesHeight = height;
    nStates = 0;
    m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_EXP);
}

MyExplosion::~MyExplosion() { }

BOOL MyExplosion::Drop()
{
    if (nStates == 28) return TRUE;
    return FALSE;
}

void MyExplosion::UpDateStates() { nStates++; }

int MyExplosion::GetStates() const { return nStates / 4; }