#include "stdafx.h"
#include "MyGameObject.h"


MyGameObject::MyGameObject(int x, int y, int h, int l) : m_ptPos(x, y), hp(h), maxHp(h), HardLevel(l) {  }

MyGameObject::~MyGameObject() { }

CPoint MyGameObject::GetPoint() { return m_ptPos; }

int MyGameObject::          GetHp() const { return hp; }

int MyGameObject::       GetMaxHp() const { return maxHp; }

int MyGameObject::      GetDamage() const { return damage; }

int MyGameObject::   GetHardLevel() const { return HardLevel; }

int MyGameObject::   GetBombLevel() const { return BombLevel; }

int MyGameObject:: GetImagesWidth() const { return imagesWidth; }

int MyGameObject::GetImagesHeight() const { return imagesHeight; }

void MyGameObject::           SetHp(int x)   { hp = x; }

void MyGameObject::        SetMoveX(int x)   { moveX = x; }

void MyGameObject::        SetMoveY(int y)   { moveY = y; }

void MyGameObject::       SetDamage(int d)   { damage = d; }

void MyGameObject::    SetHardLevel(int l)   { HardLevel = l; }

void MyGameObject::    SetBombLevel(int l)   { BombLevel = l; }

void MyGameObject:: SetPoint(int x, int y)   { m_ptPos.x = x; m_ptPos.y = y; }

void MyGameObject::SetWindowsHeight(int x)   { windowsHeight = x; }


