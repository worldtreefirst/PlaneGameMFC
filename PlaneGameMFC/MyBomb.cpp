#include "stdafx.h"
#include "MyBomb.h"
#include "resource.h"
#include "mmsystem.h"
#pragma comment(lib, "Winmm.lib")

MyBomb::MyBomb(int x, int y, int t, int mx, int my, int d) :MyGameObject(x, y)
{
    SetDamage(d);
    SetMoveX(mx);
    SetMoveY(my);
    switch (t)
    {
    case 1:
        imagesWidth = 20;
        imagesHeight = 30;
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_BOMB1);
        break;
    case 2:
        imagesWidth = 30;
        imagesHeight = 40;
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_BOMB2);
        break;
    case 3:
        imagesWidth = 40;
        imagesHeight = 50;
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_BOMB3);
        break;
    default:
        imagesWidth = 40;
        imagesHeight = 50;
        m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_BOMB3);
        break;
    }

    PlaySound((LPCWSTR)IDR_SHOOT, NULL, SND_ASYNC | SND_RESOURCE);
}

MyBomb::~MyBomb() { }

BOOL MyBomb::Drop()
{
    if (GetPoint().y + BOMB_HEIGHT < 0) return TRUE;
    return FALSE;
}

int MyBomb::BombLevel = 1;