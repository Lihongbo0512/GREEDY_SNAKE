// CGAME.cpp: 实现文件
//

#include "stdafx.h"
#include "Greedy_Snake.h"
#include "CGAME.h"
#include "afxdialogex.h"
#include "HeroDlg.h"
#include "CRule.h"
#define LOW_LEVEL_SLEEP 100
#define NOR_LEVEL_SLEEP 50
#define HIGH_LEVEL_SLEEP 20
// CGAME 对话框

IMPLEMENT_DYNAMIC(CGAME, CDialogEx)

CGAME::CGAME(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CGAME, pParent)
{
	m_nScore = 0;		//初始化分数
	m_point.x = 100;	//初始化果实x坐标
	m_point.y = 100;	//初始化果实y坐标
	m_nHighScore = 0;	//初始化最高分

}

CGAME::~CGAME()
{
}

void CGAME::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGAME, CDialogEx)
	ON_WM_PAINT()
	ON_WM_KEYUP()
END_MESSAGE_MAP()


// CGAME 消息处理程序


BOOL CGAME::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->SetBackgroundColor(RGB(0, 200, 100));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGAME::OnPaint()
{
	CPaintDC dc(this);
	CDC  memDC;
	memDC.CreateCompatibleDC(&dc);//创建内存兼容DC
	CPen pen;
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);
	memDC.SelectObject(&bitmap);
	pen.CreatePen(PS_SOLID, 5, RGB(0,0,100));//创建画笔
	memDC.SelectObject(&pen);		 //将画笔添加到memDC
	memDC.SetTextColor(RGB(100, 200,100));
	memDC.SetROP2(R2_NOTXORPEN);
	CString Str;					 //显示文本
	memDC.SetBkMode(TRANSPARENT);
	Str.Format("当前得分: %d", m_nScore);
	
	
	
	switch (m_nLevel)
	{
	case GAME_LEVEL_LOW:
		Str.Append("  当前等级:简单");
		break;
	case GAME_LEVEL_NOR:
		Str.Append("  当前等级:一般");
		break;
	case GAME_LEVEL_HIGH:
		Str.Append("  当前等级:困难");
		break;
	default:
		break;
	}
	memDC.TextOutA(5,5,Str);
	dc.BitBlt(0, 0, 700, 200, &memDC, 0, 0, SRCCOPY);

	CPen yspen;//绘制蛇的样式
	yspen.CreatePen(1,1,RGB(255,255,255));
	CBrush ysBrush;
	
	int k = m_Body.GetUpperBound() + 2;//蛇的身体长度

	if (k < 10)						   //如果蛇的长度小于10
	{
		ysBrush.CreateSolidBrush(RGB(0,255,0));
		dc.SelectObject(ysBrush);
		//绘制果实
		dc.Rectangle(CRect(m_point.x,
			m_point.y,
			m_point.x + 10,
			m_point.y + 10));
	}
	else if (k < 20)
	{
		ysBrush.CreateSolidBrush(RGB(0, 0, 255));
		dc.SelectObject(ysBrush);
		//绘制果实
		dc.Rectangle(CRect(m_point.x,
			m_point.y,
			m_point.x + 10,
			m_point.y + 10));
	}
	else if (k < 50)
	{
		ysBrush.CreateSolidBrush(RGB(0, 255, 255));
		dc.SelectObject(ysBrush);
		//绘制果实
		dc.Rectangle(CRect(m_point.x,
			m_point.y,
			m_point.x + 10,
			m_point.y + 10));
	}
	else
	{
		ysBrush.CreateSolidBrush(RGB(255,0, 0));
		dc.SelectObject(ysBrush);
		//绘制果实
		dc.Rectangle(CRect(m_point.x,
			m_point.y,
			m_point.x + 10,
			m_point.y + 10));
	}
	
	//绘制蛇的身体
	
	for (int i=0;i<=m_Body.GetUpperBound();i++)
	{
		CPoint BodyPoint = m_Body.GetAt(i);
		dc.Rectangle(CRect(BodyPoint.x,
			BodyPoint.y,
			BodyPoint.x + 10,
			BodyPoint.y + 10));
	}
}

//设置定时器
void CGAME::OnTimer(int nIDEvent,HWND wnd)
{
	if (nIDEvent == 1)
	{
		CPoint ysPoint = m_Body.GetAt(0);		//获取蛇身的第一个点坐标
		BOOL bTag = FALSE;						//定义判断死亡的变量
		CRule rule;								//游戏判断类

		switch (m_nDirect)
		{
		case CGAME::DIRECT_UP:
			ysPoint.y -= 10;
			break;
		case CGAME::DIRECT_DOWN:
			ysPoint.y += 10;
			break;
		case CGAME::DIRECT_LEFT:
			ysPoint.x -= 10;
			break;
		case CGAME::DIRECT_RIGHT:
			ysPoint.x += 10;
			break;
		default:
			break;
		}

		if (rule.IsOver(ysPoint, m_Body))//游戏结束
		{
			::KillTimer(wnd,1);
			if (m_nScore > m_nHighScore)
			{
				HeroWrite();
			}
			else
			{
				AfxMessageBox("游戏结束！分数太低，没有进入英雄榜！");
			}
		}
		else
		{
			m_Body.InsertAt(0, ysPoint);//将新点添加到蛇的身体中
			ReDrawBody(ysPoint);		
			if (((ysPoint.x <= m_point.x+10&& ysPoint.x+10 >= m_point.x + 10)
				||(ysPoint.x +10>= m_point.x&&ysPoint.x <= m_point.x))&&
				((ysPoint.y <= m_point.y + 10 && ysPoint.y + 10 >= m_point.y + 10)
					|| (ysPoint.y + 10 >= m_point.y&&ysPoint.y <= m_point.y)))
			{
				int len = m_Body.GetUpperBound();
				int level = m_nLevel;
				m_nScore =(level+1) * (len - 3);//根据游戏等级算分数

				InitFoods();//初始化下一个果实

				Invalidate();//重绘窗口
			}
			else
			{
				CPoint point = m_Body.GetAt(m_Body.GetUpperBound());
				m_Body.RemoveAt(m_Body.GetUpperBound());
				ReDrawBody(point);
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

//处理按键消息
void CGAME::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case 0x53:
		if (m_nOldDirect != DIRECT_UP)
		{
			m_nDirect = DIRECT_DOWN;
			m_nOldDirect = DIRECT_DOWN;
		}
		break;
	case 0x57:
		if (m_nOldDirect != DIRECT_DOWN)
		{
			m_nDirect = DIRECT_UP;
			m_nOldDirect = DIRECT_UP;
		}
		break;
	case 0x41:
		if (m_nOldDirect != DIRECT_RIGHT)
		{
			m_nDirect = DIRECT_LEFT;
			m_nOldDirect = DIRECT_LEFT;
		}
		break;
	case 0x44:
		if (m_nOldDirect != DIRECT_LEFT)
		{
			m_nDirect = DIRECT_RIGHT;
			m_nOldDirect = DIRECT_RIGHT;
		}
		break;
	default:
		break;
	}

	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}

//初始化果实
void CGAME::InitFoods()
{
	int ysX, ysY;
	while (1)//给出合适的果实位置
	{
		ysX = rand() % 665;
		ysY = rand() % 240+30;
		for (int i = 0; i <= m_Body.GetUpperBound(); i++)
		{
			CPoint Point = m_Body.GetAt(i);
			if (Point.y - ysY >= 10 || Point.y - ysY >= 10 ||
				Point.y - ysY <= -10 || Point.y - ysY <= -10)
			{
				m_point = CPoint(ysX, ysY);
				return;
			}
		}
	}
}


//设置游戏等级
void CGAME::SetGameLevel(Game_Level level)
{
	m_nLevel = level;
}

//开始游戏函数
BOOL CGAME::GameStart()
{
	char pszTmp[128] = {0};
	GetPrivateProfileString("HERO","score",0,
		pszTmp,127,".\\hero.ini");//读取分数
	m_nHighScore = atoi(pszTmp);  

	//::SetTimer(this->m_hWnd,1,nSleep,NULL);//设置定时器

	InitGame();				  //初始化游戏
	return TRUE;
}

//初始化游戏
void CGAME::InitGame()
{
	m_Body.RemoveAll();

	m_Body.Add(CPoint(250, 100));
	m_Body.Add(CPoint(250, 110));
	m_Body.Add(CPoint(250, 120));
	m_Body.Add(CPoint(250, 130));

	srand((unsigned)time(NULL));//初始化随机数生成器

	m_nDirect = DIRECT_LEFT;//初始化蛇的方向
	m_nOldDirect = DIRECT_LEFT;
	m_nScore = 0;			//初始化分数

	InitFoods();			//初始化果实
	//Invalidate();			//重绘窗口
}


//重绘点
void CGAME::ReDrawBody(CPoint Point)
{
	InvalidateRect(CRect(Point.x,
		Point.y,
		Point.x + 10,
		Point.y + 10));
}

//英雄榜写入和显示
void CGAME::HeroWrite()
{
	CHeroDlg heroDlg;
	heroDlg.SetWriteFlg(TRUE);
	heroDlg.m_level = m_nLevel+1;
	heroDlg.m_score = m_nScore;
	heroDlg.DoModal();
}