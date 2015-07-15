#include "stdafx.h"
#include "MyGameObject.h"


MyGameObject::MyGameObject(int x, int y) : m_ptPos(x, y) {  }

MyGameObject::~MyGameObject() { }

CPoint MyGameObject::GetPoint() { return m_ptPos; }

int MyGameObject::          GetHp() const { return hp; }

int MyGameObject::       GetMaxHp() const { return maxHp; }

int MyGameObject::       GetMoveX() const { return moveX; }

int MyGameObject::       GetMoveY() const { return moveY; }

int MyGameObject::      GetDamage() const { return damage; }

int MyGameObject::   GetHardLevel() const { return HardLevel; }

int MyGameObject:: GetImagesWidth() const { return imagesWidth; }

int MyGameObject::GetImagesHeight() const { return imagesHeight; }

void MyGameObject::           SetHp(int x) { hp = x; }

void MyGameObject::        SetMaxHp(int x) { maxHp = x; }

void MyGameObject::        SetMoveX(int x) { moveX = x; }

void MyGameObject::        SetMoveY(int y) { moveY = y; }

void MyGameObject::       SetDamage(int d) { damage = d; }

void MyGameObject::    SetHardLevel(int l) { HardLevel = l; }

void MyGameObject:: SetPoint(int x, int y) { m_ptPos.x = x; m_ptPos.y = y; }

void MyGameObject:: SetWindowsWidth(int x)  { windowsWidth = x; }

void MyGameObject::SetWindowsHeight(int x) { windowsHeight = x; }

int MyGameObject::HardLevel = 1;

BOOL MyGameObject::iAmTheGod = FALSE;