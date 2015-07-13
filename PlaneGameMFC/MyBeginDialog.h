#pragma once


// MyBeginDialog 对话框

class MyBeginDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MyBeginDialog)

public:
	MyBeginDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyBeginDialog();

// 对话框数据
	enum { IDD = IDD_BEGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedHehe();
    afx_msg void OnBnClickedHard1();
    afx_msg void OnBnClickedHard2();
    afx_msg void OnBnClickedHard3();
    afx_msg void OnBnClickedHard4();
};
