#include "stdafx.h"
#include "MyBuff.h"
#include "Resource.h"

#ifndef _HARD__LEVEL
#define _HARD__LEVEL
#define HARD_LEVEL MyGameObject::HardLevel
#endif

#ifndef _BUFF__TYPE
#define _BUFF__TYPE
#define BUFF_HP 1
#define BUFF_MY 2 
#define BUFF_BOMB 3
#define BUFF_DAMAGE 4 
#define BUFF_PROTECT 5
#endif

MyBuff::MyBuff(int x, int y) : MyGameObject(x, y)
{
    SetMoveX(0);
    SetMoveY(1);
    imagesHeight = 20;
    imagesWidth = 20;

    srand((unsigned)time(NULL));
    int P = rand() % 99 + 1;
    if (P <= 15)
    {
        SetType(BUFF_MY);
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_MY);
    } 
    else if (P <= 40)
    {
        SetType(BUFF_BOMB);
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_BOMB);
    }
    else if (P <= 55)
    {
        SetType(BUFF_DAMAGE);
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_DAMAGE);
    }
    else if (P <= 75)
    {
        SetType(BUFF_PROTECT);
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_PROTECT);
    }
    else
    {
        SetType(BUFF_HP);
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_HP);
    }
}


MyBuff::~MyBuff()
{
}

void MyBuff::SetType(int t) { type = t; }

int MyBuff::GetType() const { return type; }

BOOL MyBuff::Drop() { return FALSE; }