
// Greedy_SnakeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Greedy_Snake.h"
#include "Greedy_SnakeDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>		//含有音乐播放API
#include "HelpDlg.h"
#include "HeroDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()

	
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CGreedySnakeDlg 对话框



CGreedySnakeDlg::CGreedySnakeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GREEDY_SNAKE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	game = NULL;
	m_Sleep = 100;
}

void CGreedySnakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_Game, m_Frame);
}

BEGIN_MESSAGE_MAP(CGreedySnakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_UPDATE_COMMAND_UI(ID_EXIT_GAME, &CGreedySnakeDlg::OnUpdateExitGame)
	ON_UPDATE_COMMAND_UI(ID_START_GAME, &CGreedySnakeDlg::OnUpdateStartGame)
	ON_UPDATE_COMMAND_UI(ID_Game_Help, &CGreedySnakeDlg::OnUpdateHelp)
	ON_UPDATE_COMMAND_UI(ID_Hero_List, &CGreedySnakeDlg::OnUpdateHeroList)
	ON_UPDATE_COMMAND_UI(ID_High, &CGreedySnakeDlg::OnUpdateHigh)
	ON_UPDATE_COMMAND_UI(ID_Low, &CGreedySnakeDlg::OnUpdateLow)
	ON_UPDATE_COMMAND_UI(ID_Nor, &CGreedySnakeDlg::OnUpdateNor)
	ON_UPDATE_COMMAND_UI(ID_Game_Music, &CGreedySnakeDlg::OnUpdateGameMusic)
	ON_UPDATE_COMMAND_UI(ID_About, &CGreedySnakeDlg::OnUpdateAbout)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGreedySnakeDlg 消息处理程序

BOOL CGreedySnakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	this->SetBackgroundColor(RGB(100, 100, 100));
	this->MoveWindow(CRect(300, 200, 1000, 600));
	m_Menu.LoadMenu(IDR_MAIN_MENU);
	InitMenu();	  //初始化菜单
	SetMenu(&m_Menu);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGreedySnakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGreedySnakeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGreedySnakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//菜单退出游戏的按钮响应
void CGreedySnakeDlg::OnUpdateExitGame(CCmdUI *pCmdUI)
{
	CDialog::OnCancel();//调用对话框的退出函数
}

//菜单开始游戏的按钮响应
void CGreedySnakeDlg::OnUpdateStartGame(CCmdUI *pCmdUI)
{
	StartGame();	   //调用开始游戏的功能函数
}

//菜单帮助的按钮响应
void CGreedySnakeDlg::OnUpdateHelp(CCmdUI *pCmdUI)
{
	Help();			  //调用帮助的功能函数
}


//菜单英雄榜的按钮响应
void CGreedySnakeDlg::OnUpdateHeroList(CCmdUI *pCmdUI)
{
	HeroList();		 //调用英雄榜的功能函数
}


//菜单-困难的按钮响应
void CGreedySnakeDlg::OnUpdateHigh(CCmdUI *pCmdUI)
{
	//判断当前按钮状态
	BOOL bCheck = (BOOL)m_Menu.GetMenuState(ID_High, MF_CHECKED);
	if (!bCheck)
	{
		m_Menu.CheckMenuItem(ID_Low, MF_BYCOMMAND | MF_UNCHECKED);
		m_Menu.CheckMenuItem(ID_High, MF_BYCOMMAND | MF_CHECKED);
		m_Menu.CheckMenuItem(ID_Nor, MF_BYCOMMAND | MF_UNCHECKED);
		m_level = CGAME::GAME_LEVEL_HIGH;
		m_Sleep = 30;
	}

}

//菜单-简单的按钮响应
void CGreedySnakeDlg::OnUpdateLow(CCmdUI *pCmdUI)
{
	//判断当前按钮状态
	BOOL bCheck = (BOOL)m_Menu.GetMenuState(ID_Low, MF_CHECKED);
	if (!bCheck)
	{
		m_Menu.CheckMenuItem(ID_Low, MF_BYCOMMAND | MF_CHECKED);
		m_Menu.CheckMenuItem(ID_High, MF_BYCOMMAND | MF_UNCHECKED);
		m_Menu.CheckMenuItem(ID_Nor, MF_BYCOMMAND | MF_UNCHECKED);
		m_level = CGAME::GAME_LEVEL_LOW;
		m_Sleep = 100;
	}
}

//菜单-一般的按钮响应
void CGreedySnakeDlg::OnUpdateNor(CCmdUI *pCmdUI)
{
	//判断当前按钮状态
	BOOL bCheck = (BOOL)m_Menu.GetMenuState(ID_Nor, MF_CHECKED);
	if (!bCheck)
	{
		m_Menu.CheckMenuItem(ID_Low, MF_BYCOMMAND | MF_UNCHECKED);
		m_Menu.CheckMenuItem(ID_High, MF_BYCOMMAND | MF_UNCHECKED);
		m_Menu.CheckMenuItem(ID_Nor, MF_BYCOMMAND | MF_CHECKED);
		m_level = CGAME::GAME_LEVEL_NOR;
		m_Sleep = 50;
	}
}

//菜单游戏音乐的按钮响应函数
void CGreedySnakeDlg::OnUpdateGameMusic(CCmdUI *pCmdUI)
{
	//判断当前按钮状态
	BOOL bCheck = (BOOL)m_Menu.GetMenuState(ID_Game_Music, MF_CHECKED);
	if (!bCheck)
	{
		m_Menu.CheckMenuItem(ID_Game_Music, MF_BYCOMMAND | MF_CHECKED);
	}
	else
	{
		m_Menu.CheckMenuItem(ID_Game_Music, MF_BYCOMMAND | MF_UNCHECKED);
	}
	PlayBackMusic(!bCheck);//调用背景音乐播放函数
}

//菜单关于的按钮响应函数
void CGreedySnakeDlg::OnUpdateAbout(CCmdUI *pCmdUI)
{
	CAboutDlg DlgAbout;
	DlgAbout.DoModal();		//弹出关于对话框
}


//帮助功能函数
void CGreedySnakeDlg::Help()
{
	CHelpDlg helpDlg;
	helpDlg.DoModal();//显示帮助对话框
}

//开始游戏功能函数
void CGreedySnakeDlg::StartGame()
{
	if (game)
	{
		delete game;
	}
	game = new CGAME;
	SetTimer(1, m_Sleep, NULL);
	game->SetGameLevel(m_level);
	game->GameStart();
	CRect rect;
	m_Frame.GetClientRect(&rect);
	m_Frame.MapWindowPoints(this, rect);
	game->Create(IDD_CGAME,this);
	game->MoveWindow(rect);
	game->ShowWindow(SW_SHOW);
}

//英雄榜功能函数
void CGreedySnakeDlg::HeroList()
{
	CHeroDlg herodlg;
	herodlg.DoModal();
}



//播放背景音乐功能函数
void CGreedySnakeDlg::PlayBackMusic(BOOL flg)
{
	//指定音乐播放文件
	if (flg)
	{
		sndPlaySound("ll.wav",SND_ASYNC|SND_LOOP);//开始播放
		
	}
	else 
	{
		sndPlaySound(NULL, SND_PURGE);		//停止播放
	}
}


//初始化菜单的功能实现函数
void CGreedySnakeDlg::InitMenu()
{
	//难度初始化为简单
	m_Menu.CheckMenuItem(ID_Low,MF_BYCOMMAND|MF_CHECKED);
	m_Menu.CheckMenuItem(ID_High,MF_BYCOMMAND|MF_UNCHECKED);
	m_Menu.CheckMenuItem(ID_Nor, MF_BYCOMMAND | MF_UNCHECKED);
	//初始化无背景音乐
	m_Menu.CheckMenuItem(ID_Game_Music, MF_BYCOMMAND | MF_UNCHECKED);
}

void CGreedySnakeDlg::OnTimer(UINT_PTR nIDEvent)
{
	game->OnTimer(1,this->m_hWnd);

	CDialogEx::OnTimer(nIDEvent);
}
