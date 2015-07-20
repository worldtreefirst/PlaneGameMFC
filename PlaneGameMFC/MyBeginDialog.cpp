// MyBeginDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "PlaneGameMFC.h"
#include "MyBeginDialog.h"
#include "afxdialogex.h"

#include "MyGameObject.h"


// MyBeginDialog 对话框

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
	ON_BN_CLICKED(IDCANCEL, &MyBeginDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// MyBeginDialog 消息处理程序


void MyBeginDialog::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	MyGameObject::beginGame = TRUE;
	MyGameObject::iAmTheGod = TRUE;
	MyGameObject::HardLevel = 100;
	CDialogEx::OnOK();
}


void MyBeginDialog::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	MyGameObject::beginGame = TRUE;
	MyGameObject::iAmTheGod = FALSE;
	CDialogEx::OnCancel();
}
