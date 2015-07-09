
// ChildView.h : CChildView 类的接口
//


#pragma once


// CChildView 窗口
class MyPlane;
class CChildView : public CWnd
{
public:
    BOOL ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);

public:
    CChildView();
    virtual ~CChildView();

protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()

protected:
    int GetKey(int nVirtKey);
    void AI();
    void Running();

private:
    int bg_pos;
    bool large;
    CDC m_cacheDC;
    CRect m_client;
    MyPlane* m_hero;
    CObList m_list[5];
    CImage m_bg;
    CImage testHero;
    CBitmap m_BitmapBg1;
    CBitmap m_BitmapBg2;
    CBitmap m_cacheBitmap;
    enum ObjType{ enEnemy, enBomb, enEnemyBomb, enExplosion };

};

