#pragma once


// MyBeginDialog �Ի���

class MyBeginDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MyBeginDialog)

public:
	MyBeginDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MyBeginDialog();

// �Ի�������
	enum { IDD = IDD_BEGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedHehe();
    afx_msg void OnBnClickedHard1();
    afx_msg void OnBnClickedHard2();
    afx_msg void OnBnClickedHard3();
    afx_msg void OnBnClickedHard4();
};
