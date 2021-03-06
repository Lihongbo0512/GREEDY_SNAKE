
// Greedy_SnakeDlg.h: 头文件
//

#pragma once
#include "CGAME.h"
class CGAME;

// CGreedySnakeDlg 对话框
class CGreedySnakeDlg : public CDialogEx
{
// 构造
public:
	CGreedySnakeDlg(CWnd* pParent = nullptr);	// 标准构造函数
//功能函数
public:
	void Help();			//帮助         功能函数
	void HeroList();		//英雄榜       功能函数
	void StartGame();		//开始游戏     功能函数
	void PlayBackMusic(BOOL flg);	//播放背景音乐 功能函数
	void InitMenu();        //初始化菜单
public:



// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GREEDY_SNAKE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CMenu m_Menu;
	CGAME::Game_Level m_level;
	int		m_Sleep;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnUpdateExitGame(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStartGame(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHelp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHeroList(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHigh(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGameMusic(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAbout(CCmdUI *pCmdUI);
	// 游戏框架
	CStatic m_Frame;
	CGAME *game;//主游戏对话框
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
