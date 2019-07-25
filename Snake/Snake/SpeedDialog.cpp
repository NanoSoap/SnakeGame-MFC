// SpeedDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Snake.h"
#include "SpeedDialog.h"
#include "afxdialogex.h"


// SpeedDialog dialog

IMPLEMENT_DYNAMIC(SpeedDialog, CDialogEx)

SpeedDialog::SpeedDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

SpeedDialog::~SpeedDialog()
{
}

void SpeedDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1,m_ctrlSlider);
}


BEGIN_MESSAGE_MAP(SpeedDialog, CDialogEx)
	
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &SpeedDialog::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// SpeedDialog message handlers



BOOL SpeedDialog::OnInitDialog() {
	CDialogEx::OnInitDialog();

	m_ctrlSlider.SetPos(-(speed-150));
	return true;
}






void SpeedDialog::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int nPos = m_ctrlSlider.GetPos();
	CString str ;
	str.Format(_T("Value: %d"), nPos);
	SetDlgItemText(IDC_STATIC, str);
	speed = -nPos+150;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
