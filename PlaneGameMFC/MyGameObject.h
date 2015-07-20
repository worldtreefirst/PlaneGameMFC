#pragma once
#include "afx.h"
class MyGameObject :
    public CObject
{
public:
    virtual ~MyGameObject();
    virtual BOOL Drop() = 0;

public:
    MyGameObject(int x = 0, int y = 0);
    int GetHp() const;                       //获取单位当前血量
    int GetMaxHp() const;                    //获取单位最大血量
    int GetMoveX() const;                    //获取X向移动速度
    int GetMoveY() const;                    //获取Y向移动速度
    int GetDamage() const;                   //获取单位伤害
    int GetHardLevel() const;                //获取难度等级
    int GetImagesWidth() const;              //获取贴图宽度
    int GetImagesHeight() const;             //获取贴图高度
    void SetHp(int x);                       //设置单位当前血量
    void SetMaxHp(int x);                    //设置单位最大血量
    void SetMoveX(int x);                    //设置X向移动速度
    void SetMoveY(int y);                    //设置Y向移动速度
    void SetDamage(int d);                   //设置单位伤害
    void SetPoint(int x, int y);             //设置得分
    void SetWindowsWidth(int x);             //设置当前窗口宽度
    void SetWindowsHeight(int x);            //设置当前窗口高度
    CPoint GetPoint();                       //获取单位坐标

public: 
    CImage m_Images;                         //单位贴图
    static int HardLevel;                    //难度等级
    static BOOL beginGame;                   //游戏开始标记
    static BOOL iAmTheGod;                   //无敌模式标记
protected:
    int hp;                                  //单位当前血量
    int maxHp;                               //单位最大血量
    int damage;                              //单位伤害
    int windowsHeight;                       //当前窗口高度
    int windowsWidth;                        //当前窗口宽度
    int imagesWidth;                         //当前贴图宽度
    int imagesHeight;                        //当前贴图高度
    int moveX;                               //单位X向移动速度
    int moveY;                               //单位Y向移动速度
    CPoint m_ptPos;                          //单位坐标
};


