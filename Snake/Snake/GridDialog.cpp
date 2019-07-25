// GridDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Snake.h"
#include "GridDialog.h"
#include "afxdialogex.h"


// GridDialog dialog

IMPLEMENT_DYNAMIC(GridDialog, CDialogEx)

GridDialog::GridDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

GridDialog::~GridDialog()
{
}

void GridDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_ctrlSlider);
}


BEGIN_MESSAGE_MAP(GridDialog, CDialogEx)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &GridDialog::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// GridDialog message handlers




void GridDialog::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int nPos = m_ctrlSlider.GetPos();
	CString str;
	str.Format(_T("Value: %d"), nPos);
	SetDlgItemText(IDC_STATIC3, str);
	scale = nPos;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

BOOL GridDialog::OnInitDialog() {
	CDialogEx::OnInitDialog();
	m_ctrlSlider.SetPos(scale);
	m_ctrlSlider.SetRange(1, 10);
	m_ctrlSlider.SetTicFreq(1);
	return true;
}