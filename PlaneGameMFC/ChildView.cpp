
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "PlaneGameMFC.h"
#include "ChildView.h"

#include "MyGameObject.h"
#include "MyPlane.h"
#include "MyBomb.h"
#include "MyEnemy.h"
#include "MyHpStrip.h"
#include "MyEnemyBomb.h"
#include "MyExplosion.h"

#include "mmsystem.h"
#pragma comment(lib, "Winmm.lib")

#ifndef _TIMER__
#define _TIMER__
#define TIMER_PAINT 1
#define TIMER_CREATENEMY 2
#define TIMER_BEGINGAME 999
#endif

#ifndef _WINDOWS__
#define _WINDOWS__
#define WINDOWS_WIDTH m_client.Width()
#define WINDOWS_HEIGHT  m_client.Height()
#define PAGE_WIDTH m_bg.GetWidth()
#define PAGE_HEIGHT m_bg.GetHeight()
#endif

#ifndef _PLANE__
#define _PLANE__
#define PLANE_WIDTH 60
#define PLANE_HEIGHE 60
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CChildView::CChildView()
{
    large = false;
    bg_pos = 0;
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
        ::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

    //-------��Ϸ���ݳ�ʼ������--------

    //�������������
    srand((unsigned)time(NULL));

    //��ʼ������
    m_bg.LoadFromResource(AfxGetInstanceHandle(), IDB_BACKGROUND);

    //����Ӣ��
    m_hero = new MyPlane;
    m_herohp = new MyHpStrip;

    //����������Դ
    TCHAR tmpmp3[_MAX_PATH];
    ::GetTempPath(_MAX_PATH, tmpmp3);
    _tcscat_s(tmpmp3, _T("testapp_background.mp3"));
    ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_BGMUSIC));

    TCHAR mcicmd[300];
    _stprintf_s(mcicmd, _T("open \"%s\" alias mymusic"), tmpmp3);
    mciSendString(mcicmd, NULL, 0, NULL);
    mciSendString(_T("play mymusic"), NULL, 0, NULL);

    return TRUE;
}

void CChildView::OnPaint()
{
    //CPaintDC dc(this); // ���ڻ��Ƶ��豸������

    CDC *cDC = this->GetDC();
    GetClientRect(&m_client);
    m_cacheDC.CreateCompatibleDC(NULL);
    m_cacheBitmap.CreateCompatibleBitmap(cDC, WINDOWS_WIDTH, WINDOWS_HEIGHT);
    m_cacheDC.SelectObject(&m_cacheBitmap);


    //������
    Running();
    AI();

    //--------------���Գ���---------------

    /*tCString1.Format(_T("%d"), tExp.m_Images.GetHeight());
    tCString2.Format(_T("%d"), tExp.m_Images.GetWidth());
    tCString3.Format(_T("%d"), m_list[enExplosion].GetCount());
    TextOut(m_cacheDC, 0, 0, tCString1, tCString1.GetLength());
    TextOut(m_cacheDC, 0, 15, tCString2, tCString2.GetLength());
    TextOut(m_cacheDC, 0, 30, tCString3, tCString3.GetLength());*/

    //--------------���Խ���---------------

    cDC->BitBlt(0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, &m_cacheDC, 0, 0, SRCCOPY);

    ValidateRect(&m_client);
    m_cacheDC.DeleteDC();
    m_cacheBitmap.DeleteObject();
    ReleaseDC(cDC);

}



void CChildView::Running()
{
    //������
    m_bg.Draw(m_cacheDC, 0, bg_pos, PAGE_WIDTH, PAGE_HEIGHT);
    m_bg.Draw(m_cacheDC, 0, bg_pos - PAGE_HEIGHT, PAGE_WIDTH, PAGE_HEIGHT);

    //��Ӣ��
    if (m_hero != NULL)
    {
        m_hero->m_Images.TransparentBlt(m_cacheDC, m_hero->GetPoint().x, m_hero->GetPoint().y, PLANE_WIDTH, PLANE_HEIGHE, 0, 0, m_hero->m_Images.GetWidth(), m_hero->m_Images.GetHeight(), RGB(255, 255, 255));
        m_herohp->m_Images.Draw(m_cacheDC, m_hero->GetPoint().x, m_hero->GetPoint().y - 20, PLANE_WIDTH * m_hero->GetHp() / m_hero->GetMaxHp(), 10, 0, 0, PLANE_WIDTH, PLANE_HEIGHE);

    }
    else
    {
        CString str = _T("Game Over!");
        TextOut(m_cacheDC, 0, 0, str, str.GetLength());
    }

    //������, �л��� �л��ӵ�
    for (int i = 0; i < 3; i++)
    {
        POSITION pos1, pos2;
        for (pos1 = m_list[i].GetHeadPosition(); (pos2 = pos1) != NULL;)
        {
            MyGameObject* pObj = (MyGameObject*)m_list[i].GetNext(pos1);
            pObj->SetWindowsHeight(WINDOWS_HEIGHT);
            if (!pObj->Drop())
            {
                pObj->m_Images.TransparentBlt(m_cacheDC, pObj->GetPoint().x, pObj->GetPoint().y, pObj->GetImagesWidth(), pObj->GetImagesHeight(), RGB(255, 255, 255));
                pObj->SetPoint(pObj->GetPoint().x, pObj->GetPoint().y + pObj->GetMove());
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
        pEnemy->enemyHp->m_Images.Draw(m_cacheDC, pEnemy->GetPoint().x, pEnemy->GetPoint().y - 20, PLANE_WIDTH * pEnemy->GetHp() / pEnemy->GetMaxHp(), 10, 0, 0, PLANE_WIDTH, PLANE_WIDTH);
    }

    //����ը
    POSITION pos1 = NULL, pos2 = NULL;
    for (pos1 = m_list[enExplosion].GetHeadPosition(); (pos2 = pos1) != NULL;)
    {
        MyExplosion* pExp = (MyExplosion*)m_list[enExplosion].GetNext(pos1);
        if (!pExp->Drop())
        {
            pExp->m_Images.TransparentBlt(m_cacheDC, pExp->GetPoint().x, pExp->GetPoint().y, 60, 60, 44 * pExp->GetMove(), 0, 43, 49, RGB(255, 255, 255));
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
            CPoint tPoint = m_hero->GetPoint();
            if (m_hero != NULL && m_hero->Fire())
            {
                m_list[enBomb].AddTail(new MyBomb(tPoint.x + 15, tPoint.y - 5));
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
            m_list[enEnemyBomb].AddTail(new MyEnemyBomb(pEnemy->GetPoint().x + 25, pEnemy->GetPoint().y + 60));
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
                pEnemy->SetHp(pEnemy->GetHp() - 1);
                if (pEnemy->GetHp() <= 0)
                {
                    m_list[enExplosion].AddTail(new MyExplosion(pEnemy->GetPoint().x, pEnemy->GetPoint().y));

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
            m_list[enEnemyBomb].RemoveAt(ePos2);
            delete pEnemyBomb;
            //��ҵ�Ѫ
            m_hero->SetHp(m_hero->GetHp() - 1);
            if (m_hero->GetHp() <= 0)
            {
                m_list[enExplosion].AddTail(new MyExplosion(m_hero->GetPoint().x, m_hero->GetPoint().y));

                m_hero = NULL;
                delete m_hero;

                PlaySound((LPCWSTR)IDR_EXOLOSIONPLAYER, NULL, SND_ASYNC | SND_RESOURCE);

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
            //�趨ΪѪ��ļ�Ѫ�ٵ�
            int tEnemy = pEnemy->GetHp(), tHero = m_hero->GetHp();
            
            //�л���Ѫ
            pEnemy->SetHp(pEnemy->GetHp() - tHero);
            if (pEnemy->GetHp() <= 0)
            {
                m_list[enExplosion].AddTail(new MyExplosion(pEnemy->GetPoint().x, pEnemy->GetPoint().y));
                m_list[enEnemy].RemoveAt(pos2);
                delete pEnemy;
                PlaySound((LPCWSTR)IDR_EXOLOSIONENEMY, NULL, SND_ASYNC | SND_RESOURCE);
            }

            m_hero->SetHp(m_hero->GetHp() - tEnemy);
            if (m_hero->GetHp() <= 0)
            {
                m_list[enExplosion].AddTail(new MyExplosion(m_hero->GetPoint().x, m_hero->GetPoint().y));
                m_hero = NULL;
                delete m_hero;

                PlaySound((LPCWSTR)IDR_EXOLOSIONPLAYER, NULL, SND_ASYNC | SND_RESOURCE);
            
                return;
            }

        }
    }

}

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

int CChildView::GetKey(int nVirtKey)
{
    return (GetKeyState(nVirtKey) & 0x8000) ? 1 : 0;
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    SetTimer(TIMER_PAINT, 1, NULL);
    SetTimer(TIMER_CREATENEMY, rand() % 800 + 400, NULL);

    return 0;
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    switch (nIDEvent)
    {
    case TIMER_PAINT:
        bg_pos++;
        if (bg_pos > PAGE_HEIGHT) bg_pos = 0;
        OnPaint();
        break;
    case TIMER_CREATENEMY:
        //�����л�
        m_list[enEnemy].AddTail(new MyEnemy(rand() % (min(PAGE_WIDTH, WINDOWS_WIDTH) - 60), -60, rand() % 5 + 1));
        break;
    default:
        break;
    }
}