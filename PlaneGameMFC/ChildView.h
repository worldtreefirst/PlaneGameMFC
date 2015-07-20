
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
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);        //程序初始化

protected:
    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()

protected:
    int GetKey(int nVirtKey);      //获得键的状态
    void AI();
    void LoadBg();
    void Running();
    void BombLevel(int l);

protected:
	CRect m_client;
	CDC *cDC;                     //内存DC
	CDC m_cacheDC;                //缓冲DC
	CBitmap m_cacheBitmap;        //缓冲位图

private:
    int point;
    int bg_pos;
	int bg_type;
	int n_states;
    BOOL timer[5];                 //定时器
    MyBoss* m_Boss;                //BOSS对象
    MyPlane* m_hero;               //玩家对象
    MyHpStrip* m_herohp;           //血条对象
    CObList m_list[10];            //链表管理游戏对象
    CImage mBgList[10];            //背景图片
    enum ObjType{ enEnemy, enBomb, enEnemyBomb, enBuff, enHpStrip, enExplosion };
public:
    void CreateBomb(MyEnemy* e);   //生成敌方子弹
};

