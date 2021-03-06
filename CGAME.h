#pragma once


// CGAME 对话框

class CGAME : public CDialogEx
{
	DECLARE_DYNAMIC(CGAME)
public:
	enum Game_Level		//游戏等级
	{
		GAME_LEVEL_LOW,
		GAME_LEVEL_NOR,
		GAME_LEVEL_HIGH
	};

	enum Game_Input		//控制方向
	{
		DIRECT_UP,
		DIRECT_DOWN,
		DIRECT_LEFT,
		DIRECT_RIGHT
	};

	CPoint		   m_point;		//当前果实坐标
	Game_Input	   m_nDirect;	//当前蛇的前进方向
	int			   m_nScore;	//当前游戏分数
	Game_Level	   m_nLevel;	//当前游戏等级
	int	           m_nHighScore;//当前游戏最高分
	Game_Input	   m_nOldDirect;//上一次蛇的前进方向

	CArray<CPoint, CPoint> m_Body;//蛇的身体向量
public:
	CGAME(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGAME();
public:
	void HeroWrite();					//弹出英雄榜，写入数据
	void ReDrawBody(CPoint Point);		//绘制一节蛇的身体
	void InitGame();					//初始化游戏
	BOOL GameStart();					//游戏开始函数
	void InitFoods();					//初始化果实函数
	void SetGameLevel(Game_Level level);	//设置游戏等级函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CGAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnPaint();
	 void OnTimer(int nIDEvent,HWND wnd);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};
