#pragma once


// MyBeginDialog �Ի���

class MyBeginDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MyBeginDialog)

public:
	MyBeginDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MyBeginDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
