
// ChildView.h : ��Ľӿ�
//

#pragma once

// CChildView ����
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
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);        //�����ʼ��

protected:
    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()

protected:
    int GetKey(int nVirtKey);      //��ü���״̬
    void AI();
    void LoadBg();
    void Running();
    void BombLevel(int l);

protected:
	CRect m_client;
	CDC *cDC;                     //�ڴ�DC
	CDC m_cacheDC;                //����DC
	CBitmap m_cacheBitmap;        //����λͼ

private:
    int point;
    int bg_pos;
	int bg_type;
	int n_states;
    BOOL timer[5];                 //��ʱ��
    MyBoss* m_Boss;                //BOSS����
    MyPlane* m_hero;               //��Ҷ���
    MyHpStrip* m_herohp;           //Ѫ������
    CObList m_list[10];            //���������Ϸ����
    CImage mBgList[10];            //����ͼƬ
    enum ObjType{ enEnemy, enBomb, enEnemyBomb, enBuff, enHpStrip, enExplosion };
public:
    void CreateBomb(MyEnemy* e);   //���ɵз��ӵ�
};

