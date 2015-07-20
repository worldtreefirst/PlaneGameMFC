// MyBeginDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlaneGameMFC.h"
#include "MyBeginDialog.h"
#include "afxdialogex.h"

#include "MyGameObject.h"


// MyBeginDialog �Ի���

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


// MyBeginDialog ��Ϣ�������


void MyBeginDialog::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MyGameObject::beginGame = TRUE;
	MyGameObject::iAmTheGod = TRUE;
	MyGameObject::HardLevel = 100;
	CDialogEx::OnOK();
}


void MyBeginDialog::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MyGameObject::beginGame = TRUE;
	MyGameObject::iAmTheGod = FALSE;
	CDialogEx::OnCancel();
}
