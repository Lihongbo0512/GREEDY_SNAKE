#pragma once


// CHeroDlg 对话框

class CHeroDlg : public CDialog
{
	DECLARE_DYNAMIC(CHeroDlg)

public:
	void SetWriteFlg(BOOL Flag);
	CHeroDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHeroDlg();
public:
	int m_level;    //保存等级变量
	int m_score;	//保存分数变量
	CString m_name;	//保存名称变量
	BOOL bWriteFlg;	//记录标志变量
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHeroDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	

	DECLARE_MESSAGE_MAP()
public:
	virtual INT_PTR DoModal();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};
