#include "stdafx.h"
#include "MyPlane.h"
#include "resource.h"


MyPlane::MyPlane() : MyGameObject(250, 550, 10000000)
{
    SetMoveX(0);
    SetMoveY(0);
    SetBombLevel(4);
    imagesWidth = 60;
    imagesHeight = 60;
    nFire = 0;
    SetVerMotion(0);
    SetHorMotion(0);
    m_Images.LoadFromResource(AfxGetInstanceHandle(), IDB_PLANE);
}


MyPlane::~MyPlane() { }

int MyPlane::GetVerMotion() const { return m_nVerMotion; }

int MyPlane::GetHorMotion() const { return m_nHorMotion; }

void MyPlane::SetHorMotion(int nMotion) { m_nHorMotion = nMotion; }

void MyPlane::SetVerMotion(int nMotion) { m_nVerMotion = nMotion; }


void MyPlane::updatePoint()
{
    if (nFire) nFire++;
    if (nFire > 25) nFire = 0;
    m_ptPos.x += GetHorMotion() * 6;
    m_ptPos.y -= GetVerMotion() * 6;
}

void MyPlane::judgeEdge(int PAGE_WIDTH, int PAGE_HEIGHT, int WINDOWS_WIDTH, int WINDOWS_HEIGHT)
{
    if (m_ptPos.x < 0) m_ptPos.x = 0;
    if (m_ptPos.x + PLANE_WIDTH > min(PAGE_WIDTH, WINDOWS_WIDTH)) m_ptPos.x = min(PAGE_WIDTH, WINDOWS_WIDTH) - PLANE_WIDTH;
    if (m_ptPos.y < 0) m_ptPos.y = 0;
    if (m_ptPos.y + PLANE_HEIGHT > min(PAGE_HEIGHT, WINDOWS_HEIGHT)) m_ptPos.y = min(PAGE_HEIGHT, WINDOWS_HEIGHT) - PLANE_HEIGHT;
}


BOOL MyPlane::Fire()
{
    if (!nFire++)  return TRUE;
    return FALSE;
}

int MyPlane::GetFire() const { return nFire; }

int MyPlane::GetMoveX() const { return moveX; }

int MyPlane::GetMoveY() const { return moveY; }

BOOL MyPlane::Drop() { return TRUE; }