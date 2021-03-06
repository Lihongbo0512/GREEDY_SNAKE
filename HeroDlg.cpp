// HeroDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Greedy_Snake.h"
#include "HeroDlg.h"
#include "afxdialogex.h"


// CHeroDlg 对话框

IMPLEMENT_DYNAMIC(CHeroDlg, CDialog)

CHeroDlg::CHeroDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CHeroDlg, pParent)
{
	bWriteFlg = FALSE;		//初始化写标识为假
}

CHeroDlg::~CHeroDlg()
{
}

void CHeroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Name, m_name);
	DDX_Text(pDX, IDC_Level, m_level);
	DDX_Text(pDX, IDC_Score, m_score);
	DDV_MinMaxInt(pDX, IDC_Score,0,10000);//设置可输入的分数范围
}


BEGIN_MESSAGE_MAP(CHeroDlg, CDialog)
	
END_MESSAGE_MAP()


// CHeroDlg 消息处理程序


INT_PTR CHeroDlg::DoModal()
{
	char psztmp[128] = { 0 };
	//读取配置文件
	GetPrivateProfileString("HERO","name","0",psztmp,127,".\\hero.ini");//读取姓名
	m_name = CString(psztmp);
	if (!bWriteFlg)
	{
		GetPrivateProfileString("HERO", "score", "0", psztmp, 127, ".\\hero.ini");
		m_score = atoi(psztmp);
		GetPrivateProfileString("HERO", "level", "0", psztmp, 127, ".\\hero.ini");
		m_level = atoi(psztmp);
	}
	return CDialog::DoModal();
}

//按钮响应
void CHeroDlg::OnOK()
{
	UpdateData(TRUE);//更新显示数值到变量
	if (bWriteFlg)
	{
		CString tmp;
		tmp.Format("%d", m_score);
		WritePrivateProfileString("HERO", "score", tmp, ".\\hero.ini");
		tmp.Format("%d", m_level);
		WritePrivateProfileString("HERO", "level", tmp, ".\\hero.ini");
	}
	bWriteFlg = FALSE;//设置可读状态
	CDialog::OnOK();
}


BOOL CHeroDlg::OnInitDialog()
{
	CDialog::OnInitDialog(); 
	if (bWriteFlg)
	{
		SetDlgItemText(IDOK, "记录");//写入时更改按钮名称

	}
	return TRUE;  
}


//设置写入模式
void CHeroDlg::SetWriteFlg(BOOL Flag)
{
	bWriteFlg = Flag;
}