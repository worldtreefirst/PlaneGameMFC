
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "PlaneGameMFC.h"
#include "ChildView.h"

#include "MyGameObject.h"
#include "MyPlane.h"
#include "MyBoss.h"
#include "MyBomb.h"
#include "MyBuff.h"
#include "MyEnemy.h"
#include "MyHpStrip.h"
#include "MyEnemyBomb.h"
#include "MyExplosion.h"
#include "MyBeginDialog.h"

#include "mmsystem.h"
#pragma comment(lib, "Winmm.lib")

#ifndef _TIMER__
#define _TIMER__
#define TIMER_PAINT 1
#define TIMER_CREATENEMY1 2
#define TIMER_CREATENEMY2 3
#define TIMER_CREATENEMY3 4
#define TIMER_BEGINGAME 999
#endif

#ifndef _WINDOWS__
#define _WINDOWS__
#define WINDOWS_WIDTH m_client.Width()
#define WINDOWS_HEIGHT  m_client.Height()
#define PAGE_WIDTH m_bg.GetWidth()
#define PAGE_HEIGHT m_bg.GetHeight()
#define BEGINGAME MyGameObject::beginGame
#define I_AM_THE_GOD MyGameObject::iAmTheGod
#endif

#ifndef _BUFF__TYPE
#define _BUFF__TYPE
#define BUFF_HP 1
#define BUFF_MY 2 
#define BUFF_BOMB 3
#define BUFF_DAMAGE 4 
#define BUFF_PROTECT 5
#endif

#ifndef _PLANE__
#define _PLANE__
#define PLANE_WIDTH m_hero->GetImagesWidth()
#define PLANE_HERIGT m_hero->GetImagesHeight()
#define ENEMY_TYPE1 1
#define ENEMY_TYPE2 2
#define ENEMY_TYPE3 3 
#define HARD_LEVEL MyGameObject::HardLevel
#endif

#ifndef _PLANE_LEVEL__
#define _PLANE_LEVEL__
#define HERO_HP MyPlane::hp
#define HERO_MAX_HP MyPlane::maxHp
#define MY_LEVEL MyPlane::myLevel
#define BOMB_LEVEL MyPlane::bombLevel
#define PROTECT_LEVEL MyPlane::protectLevel
#define MIN_DAMAGE MyPlane::minDamage
#define MAX_DAMAGE MyPlane::maxDamage
#define SHOW_MIN_DAMAGE (MIN_DAMAGE + BOMB_LEVEL * HARD_LEVEL / 3)
#define SHOW_MAX_DAMAGE (MAX_DAMAGE + BOMB_LEVEL * HARD_LEVEL / 3)
#define MAX_LEVEL 100
#define BUFF_P (25 * HARD_LEVEL + 2475) / 100
#define HERO_DAMAGE (rand() % (MAX_DAMAGE + BOMB_LEVEL * HARD_LEVEL / 3) + MIN_DAMAGE + BOMB_LEVEL * HARD_LEVEL / 3)
#define PROTECT_DAMAGE (1000 - (PROTECT_LEVEL + MY_LEVEL))/ 1000
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CChildView::CChildView()
{
	large = false;
	bg_pos = 0;
	n_states = 0;
}

CChildView::~CChildView() { }

BEGIN_MESSAGE_MAP(CChildView, CWnd)
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL CChildView::ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
    // �����ļ�
    HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return false;

    // ������Դ�ļ��С�������Դ���ڴ桢�õ���Դ��С
    HRSRC    hRes = ::FindResource(NULL, strResName, strResType);
    HGLOBAL    hMem = ::LoadResource(NULL, hRes);
    DWORD    dwSize = ::SizeofResource(NULL, hRes);

    // д���ļ�
    DWORD dwWrite = 0; // ����д���ֽ�
    ::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
    ::CloseHandle(hFile);

    return true;

}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
        ::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

    //-------��Ϸ���ݳ�ʼ������--------

    //��ʼ������
    LoadBg();
    m_bg.LoadFromResource(AfxGetInstanceHandle(), IDB_BACKGROUND);

    //����Ӣ��
    m_hero = new MyPlane;
    m_herohp = new MyHpStrip;
    
    //����boss
    boss = FALSE;
    m_Boss = NULL;

    //��ʼ���÷�
    point = 0;

    //����������Դ
    TCHAR tmpmp3[_MAX_PATH];
    ::GetTempPath(_MAX_PATH, tmpmp3);
    _tcscat_s(tmpmp3, _T("testapp_background.mp3"));
    ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_BGMUSIC));

    TCHAR mcicmd[300];
    _stprintf_s(mcicmd, _T("open \"%s\" alias mymusic"), tmpmp3);
    mciSendString(mcicmd, NULL, 0, NULL);
    mciSendString(_T("setaudio mymusic volume to 1000"), NULL, 0, NULL);
    mciSendString(_T("play mymusic repeat"), NULL, 0, NULL);

    return TRUE;
}

void CChildView::OnPaint()
{
    //CPaintDC dc(this); // ���ڻ��Ƶ��豸������
    CPaintDC dc(this);
    CDC *cDC = this->GetDC();
    GetClientRect(&m_client);
    m_cacheDC.CreateCompatibleDC(NULL);
    m_cacheBitmap.CreateCompatibleBitmap(cDC, WINDOWS_WIDTH, WINDOWS_HEIGHT);
    m_cacheDC.SelectObject(&m_cacheBitmap);
    m_cacheDC.SetBkMode(TRANSPARENT);

    CFont font;
    CFont* pOldFont = &font;

    //������
    Running();
    AI();

    //״̬���
    font.CreateFont(25, 15, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("΢���ź�"));
    m_cacheDC.SelectObject(&font);
    m_cacheDC.SetTextColor(RGB(0, 255, 0));
    CString cCString[100];
    cCString[0].Format(_T("�÷֣�%d"), point);
    cCString[1].Format(_T("��ǰ����ֵ��%d"), HERO_HP);
    cCString[2].Format(_T("�������ֵ��%d"), HERO_MAX_HP);
    cCString[3].Format(_T("�Ѷȵȼ���%d"), HARD_LEVEL);
    cCString[4].Format(_T("ս���ȼ���%d"), MY_LEVEL);
    cCString[5].Format(_T("�����ȼ���%d"), BOMB_LEVEL);
    cCString[6].Format(_T("װ�׵ȼ���%d"), PROTECT_LEVEL);
    cCString[7].Format(_T("�˺���%d ~ %d "), SHOW_MIN_DAMAGE, SHOW_MAX_DAMAGE);

    for (int i = 0; i < 8; i++)
    {
        TextOut(m_cacheDC, 0, i * 25, cCString[i], cCString[i].GetLength());
    }
    m_cacheDC.SelectObject(pOldFont);

    cDC->BitBlt(0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, &m_cacheDC, 0, 0, SRCCOPY);

    ValidateRect(&m_client);
    m_cacheDC.DeleteDC();
    m_cacheBitmap.DeleteObject();
    ReleaseDC(cDC);
}

void CChildView::Running()
{
    //�������������
    srand((unsigned)time(NULL));

    //������
    mBgList[bg_type].Draw(m_cacheDC, 0, bg_pos, PAGE_WIDTH, PAGE_HEIGHT);
    mBgList[bg_type].Draw(m_cacheDC, 0, bg_pos - PAGE_HEIGHT, PAGE_WIDTH, PAGE_HEIGHT);

    //���ö�ʱ��
    if (BEGINGAME && m_Boss == NULL)
    {
        //SetTimer(TIMER_CREATENEMY1, rand() % 20, NULL);
        if (!timer[TIMER_CREATENEMY1] && rand() % 2) { timer[TIMER_CREATENEMY1] = TRUE; SetTimer(TIMER_CREATENEMY1, rand() % 2000 + 1000 - HARD_LEVEL * 10, NULL); }
        if (!timer[TIMER_CREATENEMY2] && rand() % 2) { timer[TIMER_CREATENEMY2] = TRUE; SetTimer(TIMER_CREATENEMY2, rand() % 3000 + 2000 - HARD_LEVEL * 20, NULL); }
        if (!timer[TIMER_CREATENEMY3] && rand() % 2) { timer[TIMER_CREATENEMY3] = TRUE; SetTimer(TIMER_CREATENEMY3, rand() % 6000 + 4000 - HARD_LEVEL * 30, NULL); }
    }

    //�Ѷ�����
    if (BEGINGAME && m_Boss == NULL && !(HARD_LEVEL % 5))
    {
        m_Boss = new MyBoss(min(WINDOWS_WIDTH, PAGE_WIDTH), min(WINDOWS_HEIGHT, PAGE_HEIGHT));
    }
    if (HARD_LEVEL != MAX_LEVEL && point >= HARD_LEVEL * (HARD_LEVEL + 1) * 100 / 2)
    {
        HARD_LEVEL = min(MAX_LEVEL, HARD_LEVEL + 1);
        if (!(HARD_LEVEL % 5)) 
        {
            bg_type = rand() % 5; 
        }
        if (!(HARD_LEVEL % 3) && MY_LEVEL != MAX_LEVEL)
        {
            ++MY_LEVEL;
            HERO_HP = HERO_MAX_HP = HERO_MAX_HP + 50;
            int t1 = rand() % 5 + 1, t2 = rand() % 5 + 1;
            MIN_DAMAGE = MIN_DAMAGE + min(t1, t2);
            MAX_DAMAGE = MAX_DAMAGE + max(t1, t2);
        }
    }

    //��Ӣ��
    if (m_hero != NULL)
    {
		m_hero->m_Images.TransparentBlt(m_cacheDC, m_hero->GetPoint().x, m_hero->GetPoint().y, PLANE_HERIGT, PLANE_HERIGT, 210 * (n_states / 8), 0, 210, 300, RGB(255, 255, 255));
        if (HERO_MAX_HP / HERO_HP < 60)
            m_herohp->m_Images.Draw(m_cacheDC, m_hero->GetPoint().x, m_hero->GetPoint().y - 20, PLANE_WIDTH * HERO_HP / HERO_MAX_HP, 30, 0, 0, PLANE_WIDTH, PLANE_HERIGT);
    }
    else
    { 
        CFont font;
        CString str = _T("Game Over!");
        font.CreateFont(25, 25, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("΢���ź�"));
        m_cacheDC.SetTextColor(RGB(255, 0, 0));
        m_cacheDC.SelectObject(font);
        TextOut(m_cacheDC, m_client.Width() / 2 - 125, m_client.Height() / 2 - 100, str, str.GetLength());
    }

    //��BOSS
    if (m_Boss != NULL)
    {
        m_Boss->m_Images.TransparentBlt(m_cacheDC, m_Boss->GetPoint().x, m_Boss->GetPoint().y, m_Boss->GetImagesWidth(), m_Boss->GetImagesHeight(), 0, 0, m_Boss->m_Images.GetWidth(), m_Boss->m_Images.GetHeight(), RGB(255, 255, 255));
        m_Boss->SetPoint(m_Boss->GetPoint().x + m_Boss->GetMoveX(), m_Boss->GetPoint().y + m_Boss->GetMoveY());
        if (m_Boss->GetMaxHp() / m_Boss->GetHp() < 60)
            m_Boss->myBossHp->m_Images.Draw(m_cacheDC, m_Boss->GetPoint().x, m_Boss->GetPoint().y - 30, m_Boss->GetImagesWidth() * m_Boss->GetHp() / m_Boss->GetMaxHp(), 100, 0, 0, m_Boss->GetImagesWidth(), m_Boss->GetImagesHeight());
    }

    //������, �л��� �л��ӵ�, BUFF
    for (int i = 0; i < 4; i++)
    {
        POSITION pos1, pos2;
        for (pos1 = m_list[i].GetHeadPosition(); (pos2 = pos1) != NULL;)
        {
            MyGameObject* pObj = (MyGameObject*)m_list[i].GetNext(pos1);
            pObj->SetWindowsHeight(min(WINDOWS_HEIGHT, PAGE_HEIGHT));
            pObj->SetWindowsWidth(min(WINDOWS_WIDTH, PAGE_WIDTH));
            if (!pObj->Drop())
            {
                pObj->m_Images.TransparentBlt(m_cacheDC, pObj->GetPoint().x, pObj->GetPoint().y, pObj->GetImagesWidth(), pObj->GetImagesHeight(), RGB(255, 255, 255));
                pObj->SetPoint(pObj->GetPoint().x + pObj->GetMoveX(), pObj->GetPoint().y + pObj->GetMoveY());
            }
            else
            {
                m_list[i].RemoveAt(pos2);
                delete pObj;
            }
        }

    }

    //���л�Ѫ��
    for (POSITION pos = m_list[enEnemy].GetHeadPosition(); pos != NULL;)
    {
        MyEnemy* pEnemy = (MyEnemy*)m_list[enEnemy].GetNext(pos);
        if ((pEnemy->GetMaxHp() / pEnemy->GetHp()) < 60)
            pEnemy->enemyHp->m_Images.Draw(m_cacheDC, pEnemy->GetPoint().x, pEnemy->GetPoint().y - 20, pEnemy->GetImagesWidth() * pEnemy->GetHp() / pEnemy->GetMaxHp(), 30, 0, 0, PLANE_WIDTH, PLANE_WIDTH);
    }

    //����ը
    POSITION pos1 = NULL, pos2 = NULL;
    for (pos1 = m_list[enExplosion].GetHeadPosition(); (pos2 = pos1) != NULL;)
    {
        MyExplosion* pExp = (MyExplosion*)m_list[enExplosion].GetNext(pos1);
        if (!pExp->Drop())
        {
            pExp->m_Images.TransparentBlt(m_cacheDC, pExp->GetPoint().x, pExp->GetPoint().y, pExp->GetImagesWidth(), pExp->GetImagesHeight(), 44 * pExp->GetStates(), 0, 43, 49, RGB(255, 255, 255));
            pExp->UpDateStates();
        }
        else
        {
            m_list[enExplosion].RemoveAt(pos2);
            delete pExp;
        }
    }
}

void CChildView::AI()
{
    if (m_hero == NULL) return;

    //�ɻ�����
    if (AfxGetMainWnd() == GetActiveWindow())
    {
        //�ɻ��ƶ�
        for (int i = 0; i < 4; i++)
        {
            int nMeMotion = 0;
            m_hero->SetVerMotion(0);
            m_hero->SetHorMotion(0);

            nMeMotion = GetKey(VK_UP);
            if (nMeMotion == 1)
                m_hero->SetVerMotion(1);

            nMeMotion = GetKey(VK_DOWN);
            if (nMeMotion == 1)
                m_hero->SetVerMotion(-1);

            nMeMotion = GetKey(VK_RIGHT);
            if (nMeMotion == 1)
                m_hero->SetHorMotion(1);

            nMeMotion = GetKey(VK_LEFT);
            if (nMeMotion == 1)
                m_hero->SetHorMotion(-1);
        }

        m_hero->updatePoint();
        m_hero->judgeEdge(PAGE_WIDTH, PAGE_HEIGHT, WINDOWS_WIDTH, WINDOWS_HEIGHT);

        //��������
        if (GetKey(VK_SPACE))
        {
            if (m_hero != NULL && m_hero->Fire()) { BombLevel(BOMB_LEVEL); }

        }
    }

    //BOSS����
    if (m_Boss != NULL)
    {
        //BOSS�����ӵ�
        if (m_Boss->Fire())
        {
            m_list[enEnemyBomb].AddTail(new MyEnemyBomb(m_Boss->GetPoint().x + m_Boss->GetImagesWidth() / 2, m_Boss->GetPoint().y + m_Boss->GetImagesHeight() / 2, m_Boss->GetDamage(), 7, 0));
            m_list[enEnemyBomb].AddTail(new MyEnemyBomb(m_Boss->GetPoint().x + m_Boss->GetImagesWidth() / 2, m_Boss->GetPoint().y + m_Boss->GetImagesHeight() / 2, m_Boss->GetDamage(), -7, 0));
            m_list[enEnemyBomb].AddTail(new MyEnemyBomb(m_Boss->GetPoint().x + m_Boss->GetImagesWidth() / 2, m_Boss->GetPoint().y + m_Boss->GetImagesHeight() / 2, m_Boss->GetDamage(), 0, 7));
            m_list[enEnemyBomb].AddTail(new MyEnemyBomb(m_Boss->GetPoint().x + m_Boss->GetImagesWidth() / 2, m_Boss->GetPoint().y + m_Boss->GetImagesHeight() / 2, m_Boss->GetDamage(), 0, -7));
            int dx[] = { -1, -1,  1, 1 };
            int dy[] = { 1, -1, -1, 1 };
            for (int i = 0; i < 4; i++)
            {
                m_list[enEnemyBomb].AddTail(new MyEnemyBomb(m_Boss->GetPoint().x + m_Boss->GetImagesWidth() / 2, m_Boss->GetPoint().y + m_Boss->GetImagesHeight() / 2, m_Boss->GetDamage(), 3 * dx[i], 6 * dy[i]));
                m_list[enEnemyBomb].AddTail(new MyEnemyBomb(m_Boss->GetPoint().x + m_Boss->GetImagesWidth() / 2, m_Boss->GetPoint().y + m_Boss->GetImagesHeight() / 2, m_Boss->GetDamage(), 6 * dx[i], 3 * dy[i]));
                m_list[enEnemyBomb].AddTail(new MyEnemyBomb(m_Boss->GetPoint().x + m_Boss->GetImagesWidth() / 2, m_Boss->GetPoint().y + m_Boss->GetImagesHeight() / 2, m_Boss->GetDamage(), 5 * dx[i], 5 * dy[i]));
            }
        }

        //��������BOSS
        POSITION mPos1 = NULL, mPos2 = NULL;
        for (mPos1 = m_list[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
        {
            MyBomb* pBomb = (MyBomb*)m_list[enBomb].GetNext(mPos1);
            if (pBomb->GetPoint().x + pBomb->GetImagesWidth() > m_Boss->GetPoint().x   &&
                pBomb->GetPoint().x < m_Boss->GetPoint().x + m_Boss->GetImagesWidth()  &&
                pBomb->GetPoint().y < m_Boss->GetPoint().y + m_Boss->GetImagesHeight() &&
                pBomb->GetPoint().y + pBomb->GetImagesHeight() > m_Boss->GetPoint().y)
            {
                for (int i = 0; i < 5; i++) srand((unsigned)time(NULL));

                //BOSS��Ѫ
                m_Boss->SetHp(m_Boss->GetHp() - pBomb->GetDamage());

                m_list[enExplosion].AddTail(new MyExplosion(m_Boss->GetPoint().x + rand() % m_Boss->GetImagesWidth(), m_Boss->GetPoint().y + rand() % m_Boss->GetImagesHeight(), 60, 60));

                m_list[enBomb].RemoveAt(mPos2);
                delete pBomb;

                if (m_Boss->GetHp() < 0)
                {
                    MY_LEVEL = min(MY_LEVEL + 1, MAX_LEVEL);
                    HARD_LEVEL = min(HARD_LEVEL + 1, MAX_LEVEL);

                    m_list[enExplosion].AddTail(new MyExplosion(m_Boss->GetPoint().x, m_Boss->GetPoint().y, m_Boss->GetImagesWidth(), m_Boss->GetImagesHeight()));
                    PlaySound((LPCWSTR)IDR_EXOLOSIONENEMY, NULL, SND_ASYNC | SND_RESOURCE);
                    delete m_Boss;
                    m_Boss = NULL;
                }

                return;
            }
        }

        //���ײ��BOSS
        if (m_Boss->GetPoint().x + m_Boss->GetImagesWidth() > m_hero->GetPoint().x   &&
            m_Boss->GetPoint().x < m_hero->GetPoint().x + m_hero->GetImagesWidth() &&
            m_Boss->GetPoint().y < m_hero->GetPoint().y + m_hero->GetImagesHeight() &&
            m_Boss->GetPoint().y + m_Boss->GetImagesHeight() > m_hero->GetPoint().y)
        {
            int tBoss = m_Boss->GetHp(), tHero = HERO_HP;

            m_Boss->SetHp(m_Boss->GetHp() - tHero);
            if (m_Boss->GetHp() <= 0)
            {
                MY_LEVEL = min(MY_LEVEL + 1, MAX_LEVEL);
                HARD_LEVEL = min(HARD_LEVEL + 1, MAX_LEVEL);

                m_list[enExplosion].AddTail(new MyExplosion(m_Boss->GetPoint().x, m_Boss->GetPoint().y, m_Boss->GetImagesWidth(), m_Boss->GetImagesHeight()));
                PlaySound((LPCWSTR)IDR_EXOLOSIONENEMY, NULL, SND_ASYNC | SND_RESOURCE);
                delete m_Boss;
                m_Boss = NULL;
            }

            HERO_HP -= tHero;
            if (m_hero->GetHp() <= 0)
            {
                m_list[enExplosion].AddTail(new MyExplosion(m_hero->GetPoint().x, m_hero->GetPoint().y, m_hero->GetImagesWidth(), m_hero->GetImagesHeight()));
                PlaySound((LPCWSTR)IDR_EXOLOSIONPLAYER, NULL, SND_ASYNC | SND_RESOURCE);

                if (I_AM_THE_GOD)
                {
                    HERO_HP = HERO_MAX_HP;
                    m_hero->SetPoint(250, 500);
                    return;
                }
                
                m_hero = NULL;
                delete m_hero;
                
                return;
            }
        }
    }

    //�л������ӵ�
    for (POSITION ePos = m_list[enEnemy].GetHeadPosition(); ePos != NULL;)
    {
        MyEnemy* pEnemy = (MyEnemy*)m_list[enEnemy].GetNext(ePos);
        BOOL FIRE = rand() % 2;
        if (FIRE && pEnemy->Fire())
        {
            CreateBomb(pEnemy);
        }
    }

    //�������ел�
    POSITION mPos1 = NULL, mPos2 = NULL;
    for (mPos1 = m_list[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
    {
        MyBomb* pBomb = (MyBomb*)m_list[enBomb].GetNext(mPos1);
        POSITION ePos1 = NULL, ePos2 = NULL;
        for (ePos1 = m_list[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
        {
            MyEnemy* pEnemy = (MyEnemy*)m_list[enEnemy].GetNext(ePos1);
            if (pBomb->GetPoint().x + pBomb->GetImagesWidth() > pEnemy->GetPoint().x   &&
                pBomb->GetPoint().x < pEnemy->GetPoint().x + pEnemy->GetImagesWidth() &&
                pBomb->GetPoint().y < pEnemy->GetPoint().y + pEnemy->GetImagesHeight() &&
                pBomb->GetPoint().y + pBomb->GetImagesHeight() > pEnemy->GetPoint().y)
            {
                
                //�л���Ѫ
                pEnemy->SetHp(pEnemy->GetHp() - pBomb->GetDamage());

                if (pEnemy->GetHp() <= 0)
                {
                    //�������BUFF
                    if (rand() % 100 + 1 <= BUFF_P)
                    {
                        m_list[enBuff].AddTail(new MyBuff(pEnemy->GetPoint().x, pEnemy->GetPoint().y));
                    }

                    //��ҵ÷�
                    point += pEnemy->GetDamage() + HARD_LEVEL * 5;

                    m_list[enExplosion].AddTail(new MyExplosion(pEnemy->GetPoint().x, pEnemy->GetPoint().y, pEnemy->GetImagesWidth(), pEnemy->GetImagesHeight()));

                    PlaySound((LPCWSTR)IDR_EXOLOSIONENEMY, NULL, SND_ASYNC | SND_RESOURCE);

                    m_list[enEnemy].RemoveAt(ePos2);
                    delete pEnemy;
                }
                m_list[enBomb].RemoveAt(mPos2);
                delete pBomb;

                break;
            }
        }
    }

    //��ұ��л��ӵ�����
    POSITION ePos1 = NULL, ePos2 = NULL;
    for (ePos1 = m_list[enEnemyBomb].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
    {
        MyEnemyBomb* pEnemyBomb = (MyEnemyBomb*)m_list[enBomb].GetNext(ePos1);
        if (pEnemyBomb->GetPoint().x + pEnemyBomb->GetImagesWidth() > m_hero->GetPoint().x   &&
            pEnemyBomb->GetPoint().x < m_hero->GetPoint().x + m_hero->GetImagesWidth() &&
            pEnemyBomb->GetPoint().y < m_hero->GetPoint().y + m_hero->GetImagesHeight() &&
            pEnemyBomb->GetPoint().y + pEnemyBomb->GetImagesHeight() > m_hero->GetPoint().y)
        {
            
            //��ҵ�Ѫ
            HERO_HP -= pEnemyBomb->GetDamage() * PROTECT_DAMAGE;
            //�����������
            if (!I_AM_THE_GOD)
                BOMB_LEVEL = max(1, BOMB_LEVEL - 1);
           
            m_list[enEnemyBomb].RemoveAt(ePos2);
            delete pEnemyBomb;
             
            if (HERO_HP <= 0)
            {
                m_list[enExplosion].AddTail(new MyExplosion(m_hero->GetPoint().x, m_hero->GetPoint().y, m_hero->GetImagesWidth(), m_hero->GetImagesHeight()));
                PlaySound((LPCWSTR)IDR_EXOLOSIONPLAYER, NULL, SND_ASYNC | SND_RESOURCE);

                HERO_HP = 0;
                if (I_AM_THE_GOD)
                {
                    HERO_HP = HERO_MAX_HP;
                    break;
                }

                m_hero = NULL;
                delete m_hero;

                return;
            }
        }
    }

    //��ұ��л�ײ��
    POSITION pos1 = NULL, pos2 = NULL;
    for (pos1 = m_list[enEnemy].GetHeadPosition(); (pos2 = pos1) != NULL;)
    {
        MyEnemy* pEnemy = (MyEnemy*)m_list[enBomb].GetNext(pos1);
        if (pEnemy->GetPoint().x + pEnemy->GetImagesWidth() > m_hero->GetPoint().x   &&
            pEnemy->GetPoint().x < m_hero->GetPoint().x + m_hero->GetImagesWidth() &&
            pEnemy->GetPoint().y < m_hero->GetPoint().y + m_hero->GetImagesHeight() &&
            pEnemy->GetPoint().y + pEnemy->GetImagesHeight() > m_hero->GetPoint().y)
        {

            //�趨Ϊ�л��ݻ٣���ҵ�Ѫ
            int tEnemy = pEnemy->GetHp();
          
               //�������BUFF
            if (rand() % 100 + 1 <= BUFF_P)
            {
                m_list[enBuff].AddTail(new MyBuff(pEnemy->GetPoint().x, pEnemy->GetPoint().y));
            }

            //�л��ݻ�
            m_list[enExplosion].AddTail(new MyExplosion(pEnemy->GetPoint().x, pEnemy->GetPoint().y, pEnemy->GetImagesWidth(), pEnemy->GetImagesHeight()));
            m_list[enEnemy].RemoveAt(pos2);
            delete pEnemy;
            PlaySound((LPCWSTR)IDR_EXOLOSIONENEMY, NULL, SND_ASYNC | SND_RESOURCE);
           
            //��ҵ�Ѫ
            HERO_HP -= tEnemy * PROTECT_DAMAGE;

            //����ӵ�����
            if (!I_AM_THE_GOD)
                BOMB_LEVEL = max(1, BOMB_LEVEL - 1);

            if (HERO_HP <= 0)
            {
                m_list[enExplosion].AddTail(new MyExplosion(m_hero->GetPoint().x, m_hero->GetPoint().y, m_hero->GetImagesWidth(), m_hero->GetImagesHeight()));
                PlaySound((LPCWSTR)IDR_EXOLOSIONPLAYER, NULL, SND_ASYNC | SND_RESOURCE);

                HERO_HP = 0;
                if (I_AM_THE_GOD)
                {
                    HERO_HP = HERO_MAX_HP;
                    break;
                }

                m_hero = NULL;
                delete m_hero;

                return;
            }

            //��ҵ÷�
            point += tEnemy + HARD_LEVEL * 5;
        }
    }

    //��ҳԵ�BUFF
   POSITION bPos1 = NULL, bPos2 = NULL;
    for (bPos1 = m_list[enBuff].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
    {
        MyBuff* pMyBuff = (MyBuff*)m_list[enBuff].GetNext(bPos1);

        if (pMyBuff->GetPoint().x + pMyBuff->GetImagesWidth() > m_hero->GetPoint().x   &&
            pMyBuff->GetPoint().x < m_hero->GetPoint().x + m_hero->GetImagesWidth() &&
            pMyBuff->GetPoint().y < m_hero->GetPoint().y + m_hero->GetImagesHeight() &&
            pMyBuff->GetPoint().y + pMyBuff->GetImagesHeight() > m_hero->GetPoint().y)
        {
            int t1 = rand() % 5 + 1, t2 = rand() % 5 + 1;
            switch (pMyBuff->GetType())
            {
            case BUFF_HP:
                HERO_HP = min(HERO_HP + (rand() % HARD_LEVEL / 3 * 10) + HARD_LEVEL / 3 * 10 + 40, HERO_MAX_HP);
                break;
            case BUFF_BOMB:
                BOMB_LEVEL = min(BOMB_LEVEL + 1, 5);
                break;
            case BUFF_DAMAGE:
                MAX_DAMAGE += max(t1, t2);
                MIN_DAMAGE += min(t1, t2);
                break;
            case BUFF_PROTECT:
                PROTECT_LEVEL = min(PROTECT_LEVEL + 1, MAX_LEVEL);
                break;
            case BUFF_MY:
                if (MY_LEVEL != MAX_LEVEL)
                {
                    ++MY_LEVEL;
                    MIN_DAMAGE = MIN_DAMAGE + min(t1, t2);
                    MAX_DAMAGE = MAX_DAMAGE + max(t1, t2);
                    HERO_HP = HERO_MAX_HP = HERO_MAX_HP + 50;
                    PROTECT_LEVEL = min(PROTECT_LEVEL + 1, MAX_LEVEL);
                }
                break;
            }
            m_list[enBuff].RemoveAt(bPos2);
            delete pMyBuff;
            break;
        }
    }
}

int CChildView::GetKey(int nVirtKey)
{
    return (GetKeyState(nVirtKey) & 0x8000) ? 1 : 0;
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    for (int i = 0; i < 5; i++) timer[i] = FALSE;

    SetTimer(TIMER_PAINT, 1, NULL);

    return 0;
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    switch (nIDEvent)
    {
    case TIMER_PAINT:
        bg_pos++;
		n_states++;
		if (n_states > 64) n_states = 0;
        if (bg_pos > PAGE_HEIGHT) bg_pos = 0;
        OnPaint();
        break;
    case TIMER_CREATENEMY1:
        //������һ��л�
        m_list[enEnemy].AddTail(new MyEnemy(ENEMY_TYPE1, min(WINDOWS_HEIGHT, PAGE_HEIGHT), min(WINDOWS_WIDTH, PAGE_WIDTH)));
        //�ݻټ�ʱ��
        KillTimer(TIMER_CREATENEMY1);
        timer[TIMER_CREATENEMY1] = FALSE;
        break;
    case TIMER_CREATENEMY2:
        //�����ڶ���л�
        m_list[enEnemy].AddTail(new MyEnemy(ENEMY_TYPE2, min(WINDOWS_HEIGHT, PAGE_HEIGHT), min(WINDOWS_WIDTH, PAGE_WIDTH)));
        //�ݻټ�ʱ��
        KillTimer(TIMER_CREATENEMY2);
        timer[TIMER_CREATENEMY2] = FALSE;
        break;
    case TIMER_CREATENEMY3:
        //����������л�
        m_list[enEnemy].AddTail(new MyEnemy(ENEMY_TYPE3, min(WINDOWS_HEIGHT, PAGE_HEIGHT), min(WINDOWS_WIDTH, PAGE_WIDTH)));
        //�ݻټ�ʱ��
        KillTimer(TIMER_CREATENEMY3);
        timer[TIMER_CREATENEMY3] = FALSE;
        break;
    default:
        break;
    }
}

void CChildView::LoadBg()
{
    bg_type = rand() % 5;
    mBgList[0].LoadFromResource(AfxGetInstanceHandle(), IDB_BACKGROUND1);
    mBgList[1].LoadFromResource(AfxGetInstanceHandle(), IDB_BACKGROUND2);
    mBgList[2].LoadFromResource(AfxGetInstanceHandle(), IDB_BACKGROUND3);
    mBgList[3].LoadFromResource(AfxGetInstanceHandle(), IDB_BACKGROUND4);
    mBgList[4].LoadFromResource(AfxGetInstanceHandle(), IDB_BACKGROUND5);
}

void CChildView::BombLevel(int l)
{
    CPoint tPoint = m_hero->GetPoint();
    switch (l)
    {
    case 1:
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 35, tPoint.y - 5, 1, 0, -10, HERO_DAMAGE));
        break;
    case 2:
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 30, tPoint.y - 5, 2, 0, -10, HERO_DAMAGE));
        break;
    case 3:
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 30, tPoint.y - 5, 2,  0, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 10,     tPoint.y, 1, -3, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 60,     tPoint.y, 1,  3, -10, HERO_DAMAGE));
        break;
    case 4:
    //default:
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 30, tPoint.y - 5, 2,  0, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(     tPoint.x,     tPoint.y, 2, -3, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 60,     tPoint.y, 2,  3, -10, HERO_DAMAGE));
        break;
    default:
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 30,  tPoint.y - 5, 2,  0, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(     tPoint.x,      tPoint.y, 2, -3, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 60,      tPoint.y, 2,  3, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x - 30, tPoint.y + 10, 3, -5, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 95, tPoint.y + 10, 4,  5, -10, HERO_DAMAGE));
        break;
    }
}

void CChildView::CreateBomb(MyEnemy* e)
{
    switch (e->GetPlaneType())
    {
    case 1:
        m_list[enEnemyBomb].AddTail(new MyEnemyBomb(e->GetPoint().x + 25, e->GetPoint().y + 60, e->GetDamage(), 0, 10));
        break;
    case 2:
        m_list[enEnemyBomb].AddTail(new MyEnemyBomb(e->GetPoint().x + 10, e->GetPoint().y + 60, e->GetDamage(), 0, 10));
        m_list[enEnemyBomb].AddTail(new MyEnemyBomb(e->GetPoint().x + 60, e->GetPoint().y + 60, e->GetDamage(), 0, 10));
        break;
    case 3:
        m_list[enEnemyBomb].AddTail(new MyEnemyBomb(e->GetPoint().x + 15, e->GetPoint().y + 60, e->GetDamage(), -5, 10));
        m_list[enEnemyBomb].AddTail(new MyEnemyBomb(e->GetPoint().x + 40, e->GetPoint().y + 60, e->GetDamage(),  0, 10));
        m_list[enEnemyBomb].AddTail(new MyEnemyBomb(e->GetPoint().x + 65, e->GetPoint().y + 60, e->GetDamage(),  5, 10));
    default:
        break;

    }
}
