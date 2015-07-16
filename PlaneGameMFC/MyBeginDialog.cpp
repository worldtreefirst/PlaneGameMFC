// MyBeginDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "PlaneGameMFC.h"
#include "MyBeginDialog.h"
#include "afxdialogex.h"

#include "MyPlane.h"
#include "MyBomb.h"
#include "MyGameObject.h"

// MyBeginDialog 对话框

#ifndef _PLANE__
#define _PLANE__
#define BEGINGAME MyGameObject::beginGame
#define HERO_HP MyPlane::hp
#define HERO_MAX_HP MyPlane::maxHp
#define BOMB_LEVEL MyPlane::bombLevel
#define HARD_LEVEL MyGameObject::HardLevel
#endif

IMPLEMENT_DYNAMIC(MyBeginDialog, CDialogEx)

MyBeginDialog::MyBeginDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyBeginDialog::IDD, pParent)
{

}

MyBeginDialog::~MyBeginDialog()
{
}

void MyBeginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyBeginDialog, CDialogEx)
    ON_BN_CLICKED(IDOK, &MyBeginDialog::OnBnClickedOk)
    ON_BN_CLICKED(IDC_HEHE, &MyBeginDialog::OnBnClickedHehe)
    ON_BN_CLICKED(IDC_HARD1, &MyBeginDialog::OnBnClickedHard1)
    ON_BN_CLICKED(IDC_HARD2, &MyBeginDialog::OnBnClickedHard2)
    ON_BN_CLICKED(IDC_HARD3, &MyBeginDialog::OnBnClickedHard3)
    ON_BN_CLICKED(IDC_HARD4, &MyBeginDialog::OnBnClickedHard4)
END_MESSAGE_MAP()


// MyBeginDialog 消息处理程序

void MyBeginDialog::OnBnClickedOk()
{


}

void MyBeginDialog::OnBnClickedHehe()
{
    // TODO:  在此添加控件通知处理程序代码
    BEGINGAME = TRUE;
    HERO_HP = 1000;
    HERO_MAX_HP = 1000;
    HARD_LEVEL = 100;
    BOMB_LEVEL = 1;
    MyGameObject::iAmTheGod = TRUE;
    CDialogEx::OnOK();
}


void MyBeginDialog::OnBnClickedHard1()
{
    // TODO:  在此添加控件通知处理程序代码
    BEGINGAME = TRUE;
    HERO_HP = 100;
    HERO_MAX_HP = 100;
    HARD_LEVEL = 1;
    BOMB_LEVEL = 1;
    CDialogEx::OnOK();
}


void MyBeginDialog::OnBnClickedHard2()
{
    // TODO:  在此添加控件通知处理程序代码
    BEGINGAME = TRUE;
    HERO_HP = 100;
    HERO_MAX_HP = 100;
    HARD_LEVEL = 5;
    BOMB_LEVEL = 1; 
    CDialogEx::OnOK();
}


void MyBeginDialog::OnBnClickedHard3()
{
    // TODO:  在此添加控件通知处理程序代码
    BEGINGAME = TRUE;
    HERO_HP = 100;
    HERO_MAX_HP = 100;
    HARD_LEVEL = 20;
    BOMB_LEVEL = 1;
    CDialogEx::OnOK();
}


void MyBeginDialog::OnBnClickedHard4()
{
    // TODO:  在此添加控件通知处理程序代码
    BEGINGAME = TRUE;
    HERO_HP = 100;
    HERO_MAX_HP = 100;
    HARD_LEVEL = 100;
    BOMB_LEVEL = 1;
    CDialogEx::OnOK();
}
