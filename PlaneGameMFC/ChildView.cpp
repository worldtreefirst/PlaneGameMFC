
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "PlaneGameMFC.h"
#include "ChildView.h"

#include "MyGameObject.h"
#include "MyPlane.h"
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
#define PLANE_WIDTH 60
#define PLANE_HEIGHE 60
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
#define SHOW_MIN_DAMAGE (MIN_DAMAGE + BOMB_LEVEL * HARD_LEVEL)
#define SHOW_MAX_DAMAGE (MAX_DAMAGE + BOMB_LEVEL * HARD_LEVEL)
#define MAX_LEVEL 100
#define BUFF_P (25 * HARD_LEVEL + 2475) / 100
#define HERO_DAMAGE (rand() % (MAX_DAMAGE + BOMB_LEVEL * HARD_LEVEL) + MIN_DAMAGE + BOMB_LEVEL * HARD_LEVEL)
#define PROTECT_DAMAGE (1000 - (PROTECT_LEVEL + MY_LEVEL))/ 1000
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CChildView::CChildView()
{
    large = false;
    bg_pos = 0;
}

CChildView::~CChildView() { }

BEGIN_MESSAGE_MAP(CChildView, CWnd)
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL CChildView::ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
    // 创建文件
    HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return false;

    // 查找资源文件中、加载资源到内存、得到资源大小
    HRSRC    hRes = ::FindResource(NULL, strResName, strResType);
    HGLOBAL    hMem = ::LoadResource(NULL, hRes);
    DWORD    dwSize = ::SizeofResource(NULL, hRes);

    // 写入文件
    DWORD dwWrite = 0; // 返回写入字节
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

    //-------游戏数据初始化部分--------

    //初始化背景
    LoadBg();
    m_bg.LoadFromResource(AfxGetInstanceHandle(), IDB_BACKGROUND);

    //加载英雄
    m_hero = new MyPlane;
    m_herohp = new MyHpStrip;

    //初始化得分
    point = 0;

    //加载音乐资源
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
    //CPaintDC dc(this); // 用于绘制的设备上下文
    CPaintDC dc(this);
    CDC *cDC = this->GetDC();
    GetClientRect(&m_client);
    m_cacheDC.CreateCompatibleDC(NULL);
    m_cacheBitmap.CreateCompatibleBitmap(cDC, WINDOWS_WIDTH, WINDOWS_HEIGHT);
    m_cacheDC.SelectObject(&m_cacheBitmap);
    m_cacheDC.SetBkMode(TRANSPARENT);

    CFont font;
    CFont* pOldFont = &font;

    //贴背景
    Running();
    AI();

    //状态面板
    font.CreateFont(25, 15, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
    m_cacheDC.SelectObject(&font);
    m_cacheDC.SetTextColor(RGB(0, 255, 0)); 
    CString cCString[100];
    cCString[0].Format(_T("得分：%d"), point);
    cCString[1].Format(_T("当前生命值：%d"), HERO_HP);
    cCString[2].Format(_T("最大生命值：%d"), HERO_MAX_HP);
    cCString[3].Format(_T("难度等级：%d"), HARD_LEVEL);
    cCString[4].Format(_T("战机等级：%d"), MY_LEVEL);
    cCString[5].Format(_T("导弹等级：%d"), BOMB_LEVEL);
    cCString[6].Format(_T("装甲等级：%d"), PROTECT_LEVEL);
    cCString[7].Format(_T("伤害：%d ~ %d "), SHOW_MIN_DAMAGE, SHOW_MAX_DAMAGE);

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
    //产生随机数种子
    srand((unsigned)time(NULL));

    //贴背景
    mBgList[bg_type].Draw(m_cacheDC, 0, bg_pos, PAGE_WIDTH, PAGE_HEIGHT);
    mBgList[bg_type].Draw(m_cacheDC, 0, bg_pos - PAGE_HEIGHT, PAGE_WIDTH, PAGE_HEIGHT);
    //m_bg.Draw(m_cacheDC, 0, bg_pos, PAGE_WIDTH, PAGE_HEIGHT);
    //m_bg.Draw(m_cacheDC, 0, bg_pos - PAGE_HEIGHT, PAGE_WIDTH, PAGE_HEIGHT);

    //难度升级
    if (HARD_LEVEL != MAX_LEVEL && point >= HARD_LEVEL * (HARD_LEVEL + 1) * 100 / 2)
    {
        HARD_LEVEL = min(MAX_LEVEL, HARD_LEVEL + 1);
        if (!(HARD_LEVEL % 5)) { bg_type = rand() % 5; }
        if (!(HARD_LEVEL % 3) && MY_LEVEL != MAX_LEVEL)
        {
            ++MY_LEVEL;
            HERO_HP = HERO_MAX_HP = HERO_MAX_HP + 50;
            int t1 = rand() % 5 + 1, t2 = rand() % 5 + 1;
            MIN_DAMAGE = MIN_DAMAGE + min(t1, t2);
            MAX_DAMAGE = MAX_DAMAGE + max(t1, t2);
        }
    }

    //贴英雄
    if (m_hero != NULL)
    {
        m_hero->m_Images.TransparentBlt(m_cacheDC, m_hero->GetPoint().x, m_hero->GetPoint().y, PLANE_WIDTH, PLANE_HEIGHE, 0, 0, m_hero->m_Images.GetWidth(), m_hero->m_Images.GetHeight(), RGB(255, 255, 255));
        if (HERO_MAX_HP / HERO_HP < 60)
            m_herohp->m_Images.Draw(m_cacheDC, m_hero->GetPoint().x, m_hero->GetPoint().y - 20, PLANE_WIDTH * HERO_HP / HERO_MAX_HP, 10, 0, 0, PLANE_WIDTH, PLANE_HEIGHE);
    }
    else
    { 
        CFont font;
        CString str = _T("Game Over!");
        font.CreateFont(25, 25, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
        m_cacheDC.SetTextColor(RGB(255, 0, 0));
        m_cacheDC.SelectObject(font);
        TextOut(m_cacheDC, m_client.Width() / 2 - 125, m_client.Height() / 2 - 100, str, str.GetLength());
    }

    //画导弹, 敌机， 敌机子弹, BUFF
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

    //画敌机血条
    for (POSITION pos = m_list[enEnemy].GetHeadPosition(); pos != NULL;)
    {
        MyEnemy* pEnemy = (MyEnemy*)m_list[enEnemy].GetNext(pos);
        if ((pEnemy->GetMaxHp() / pEnemy->GetHp()) < 60)
            pEnemy->enemyHp->m_Images.Draw(m_cacheDC, pEnemy->GetPoint().x, pEnemy->GetPoint().y - 20, pEnemy->GetImagesWidth() * pEnemy->GetHp() / pEnemy->GetMaxHp(), 10, 0, 0, PLANE_WIDTH, PLANE_WIDTH);
    }

    //画爆炸
    POSITION pos1 = NULL, pos2 = NULL;
    for (pos1 = m_list[enExplosion].GetHeadPosition(); (pos2 = pos1) != NULL;)
    {
        MyExplosion* pExp = (MyExplosion*)m_list[enExplosion].GetNext(pos1);
        if (!pExp->Drop())
        {
            pExp->m_Images.TransparentBlt(m_cacheDC, pExp->GetPoint().x, pExp->GetPoint().y, 60, 60, 44 * pExp->GetStates(), 0, 43, 49, RGB(255, 255, 255));
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

    //飞机控制
    if (AfxGetMainWnd() == GetActiveWindow())
    {
        //飞机移动
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


        //产生导弹
        if (GetKey(VK_SPACE))
        {
            if (m_hero != NULL && m_hero->Fire()) { BombLevel(BOMB_LEVEL); }

        }
    }

    //敌机发射子弹
    for (POSITION ePos = m_list[enEnemy].GetHeadPosition(); ePos != NULL;)
    {
        MyEnemy* pEnemy = (MyEnemy*)m_list[enEnemy].GetNext(ePos);
        BOOL FIRE = rand() % 2;
        if (FIRE && pEnemy->Fire())
        {
            CreateBomb(pEnemy);
        }
    }

    //导弹击中敌机
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
                
                //敌机掉血
                pEnemy->SetHp(pEnemy->GetHp() - pBomb->GetDamage());

                if (pEnemy->GetHp() <= 0)
                {
                    //随机生成BUFF
                    if (rand() % 100 + 1 <= BUFF_P)
                    {
                        m_list[enBuff].AddTail(new MyBuff(pEnemy->GetPoint().x, pEnemy->GetPoint().y));
                    }

                    //玩家得分
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

    //玩家被敌机子弹击中
    POSITION ePos1 = NULL, ePos2 = NULL;
    for (ePos1 = m_list[enEnemyBomb].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
    {
        MyEnemyBomb* pEnemyBomb = (MyEnemyBomb*)m_list[enBomb].GetNext(ePos1);
        if (pEnemyBomb->GetPoint().x + pEnemyBomb->GetImagesWidth() > m_hero->GetPoint().x   &&
            pEnemyBomb->GetPoint().x < m_hero->GetPoint().x + m_hero->GetImagesWidth() &&
            pEnemyBomb->GetPoint().y < m_hero->GetPoint().y + m_hero->GetImagesHeight() &&
            pEnemyBomb->GetPoint().y + pEnemyBomb->GetImagesHeight() > m_hero->GetPoint().y)
        {
            
            //玩家掉血
            HERO_HP -= pEnemyBomb->GetDamage() * PROTECT_DAMAGE;
            //玩家武器降级
            if (!I_AM_THE_GOD)
                BOMB_LEVEL = max(1, BOMB_LEVEL - 1);
           
            m_list[enEnemyBomb].RemoveAt(ePos2);
            delete pEnemyBomb;
             
            if (HERO_HP <= 0)
            {
                HERO_HP = 0;
                if (I_AM_THE_GOD)
                {
                    HERO_HP = HERO_MAX_HP;
                    break;
                }
                m_list[enExplosion].AddTail(new MyExplosion(m_hero->GetPoint().x, m_hero->GetPoint().y, m_hero->GetImagesWidth(), m_hero->GetImagesHeight()));

                m_hero = NULL;
                delete m_hero;

                PlaySound((LPCWSTR)IDR_EXOLOSIONPLAYER, NULL, SND_ASYNC | SND_RESOURCE);

                return;
            }
            
        }
    }

    //玩家被敌机撞上
    POSITION pos1 = NULL, pos2 = NULL;
    for (pos1 = m_list[enEnemy].GetHeadPosition(); (pos2 = pos1) != NULL;)
    {
        MyEnemy* pEnemy = (MyEnemy*)m_list[enBomb].GetNext(pos1);
        if (pEnemy->GetPoint().x + pEnemy->GetImagesWidth() > m_hero->GetPoint().x   &&
            pEnemy->GetPoint().x < m_hero->GetPoint().x + m_hero->GetImagesWidth() &&
            pEnemy->GetPoint().y < m_hero->GetPoint().y + m_hero->GetImagesHeight() &&
            pEnemy->GetPoint().y + pEnemy->GetImagesHeight() > m_hero->GetPoint().y)
        {

            //设定为敌机摧毁，玩家掉血
            int tEnemy = pEnemy->GetDamage();
            
            //随机生成BUFF
            if (rand() % 100 + 1 <= BUFF_P)
            {
                m_list[enBuff].AddTail(new MyBuff(pEnemy->GetPoint().x, pEnemy->GetPoint().y));
            }

            //敌机摧毁
           m_list[enExplosion].AddTail(new MyExplosion(pEnemy->GetPoint().x, pEnemy->GetPoint().y, pEnemy->GetImagesWidth(), pEnemy->GetImagesHeight()));
           m_list[enEnemy].RemoveAt(pos2);
           delete pEnemy;
           PlaySound((LPCWSTR)IDR_EXOLOSIONENEMY, NULL, SND_ASYNC | SND_RESOURCE);

            //玩家掉血
            HERO_HP -= tEnemy * PROTECT_DAMAGE;
            //玩家子弹降级
            if (!I_AM_THE_GOD)
                BOMB_LEVEL = max(1, BOMB_LEVEL - 1);

            if (HERO_HP <= 0)
            {
                HERO_HP = 0;
                if (I_AM_THE_GOD)
                {
                    HERO_HP = HERO_MAX_HP;
                    break;
                }
                m_list[enExplosion].AddTail(new MyExplosion(m_hero->GetPoint().x, m_hero->GetPoint().y, m_hero->GetImagesWidth(), m_hero->GetImagesHeight()));

                m_hero = NULL;
                delete m_hero;

                PlaySound((LPCWSTR)IDR_EXOLOSIONPLAYER, NULL, SND_ASYNC | SND_RESOURCE);

                return;
            }

            //玩家得分
            point += tEnemy + HARD_LEVEL * 5;
        }
    }

    //玩家吃到BUFF
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
                HERO_HP = min(HERO_HP + HARD_LEVEL * 20, HERO_MAX_HP);
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

    SetTimer(TIMER_PAINT, 1, NULL);
    SetTimer(TIMER_CREATENEMY1, rand() % 2000 + 1000 - HARD_LEVEL * 10, NULL);
    SetTimer(TIMER_CREATENEMY2, rand() % 3000 + 2000 - HARD_LEVEL * 20, NULL);
    SetTimer(TIMER_CREATENEMY3, rand() % 6000 + 4000 - HARD_LEVEL * 30, NULL);

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
    case TIMER_CREATENEMY1:
        //创建第一类敌机
        m_list[enEnemy].AddTail(new MyEnemy(ENEMY_TYPE1, min(WINDOWS_HEIGHT, PAGE_HEIGHT), min(WINDOWS_WIDTH, PAGE_WIDTH)));
        break;
    case TIMER_CREATENEMY2:
        //创建第二类敌机
        m_list[enEnemy].AddTail(new MyEnemy(ENEMY_TYPE2, min(WINDOWS_HEIGHT, PAGE_HEIGHT), min(WINDOWS_WIDTH, PAGE_WIDTH)));
        break;
    case TIMER_CREATENEMY3:
        //创建第三类敌机
        m_list[enEnemy].AddTail(new MyEnemy(ENEMY_TYPE3, min(WINDOWS_HEIGHT, PAGE_HEIGHT), min(WINDOWS_WIDTH, PAGE_WIDTH)));
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
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 20, tPoint.y - 5, 1, 0, -10, HERO_DAMAGE));
        break;
    case 2:
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 15, tPoint.y - 5, 2, 0, -10, HERO_DAMAGE));
        break;
    case 3:
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 15, tPoint.y - 5, 2,  0, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x - 5,      tPoint.y, 1, -3, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 45,     tPoint.y, 1,  3, -10, HERO_DAMAGE));
        break;
    case 4:
    //default:
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 15, tPoint.y - 5, 2,  0, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x - 15,     tPoint.y, 2, -3, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 45,     tPoint.y, 2,  3, -10, HERO_DAMAGE));
        break;
    default:
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 15,  tPoint.y - 5, 2,  0, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x - 15,      tPoint.y, 2, -3, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 45,      tPoint.y, 2,  3, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x - 45, tPoint.y + 10, 3, -5, -10, HERO_DAMAGE));
        m_list[enBomb].AddTail(new MyBomb(tPoint.x + 80, tPoint.y + 10, 4,  5, -10, HERO_DAMAGE));
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
