// ShutDownDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "COC.h"
#include "ShutDownDlg.h"
#include "afxdialogex.h"
#include "COCDlg.h"


// CShutDownDlg 对话框

IMPLEMENT_DYNAMIC(CShutDownDlg, CDialogEx)

CShutDownDlg::CShutDownDlg(CCOCDlg* pParent /*=NULL*/)
	: CDialogEx(CShutDownDlg::IDD, pParent)
	, m_shutDownTime(0)
{
	m_pParent = pParent;
}

CShutDownDlg::~CShutDownDlg()
{
}

void CShutDownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX); 
	DDX_Text(pDX, IDC_EDIT1, m_shutDownTime);
	DDV_MinMaxInt(pDX, m_shutDownTime, 0, 86400);
}


BEGIN_MESSAGE_MAP(CShutDownDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CShutDownDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CShutDownDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CShutDownDlg 消息处理程序


void CShutDownDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CShutDownDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_pParent->setShutDownTime(m_shutDownTime);
	CDialogEx::OnOK();
}


void CShutDownDlg::setTime(int time)
{
	m_shutDownTime = time; 
}
