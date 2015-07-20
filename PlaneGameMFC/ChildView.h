
// ChildView.h : 类的接口
//


#pragma once


// CChildView 窗口
class MyPlane;
class MyHpStrip;
class MyEnemy;
class MyBoss;
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
    void LoadBg();
    void Running();
    void BombLevel(int l);

private:
    int point;
    int bg_pos;
    int bg_type;
    bool large;
    CDC m_cacheDC;
    CRect m_client;
    BOOL boss;
    BOOL timer[5];
    MyBoss* m_Boss;
    MyPlane* m_hero;
    MyHpStrip* m_herohp;
    CObList m_list[50];
    CImage m_bg;
    CImage mBgList[10];
    CBitmap m_cacheBitmap;
    enum ObjType{ enEnemy, enBomb, enEnemyBomb, enBuff, enHpStrip, enExplosion };
public:
    void CreateBomb(MyEnemy* e);
private:
	int n_states;
};

