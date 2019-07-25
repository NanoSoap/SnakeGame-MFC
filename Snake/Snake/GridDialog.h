#pragma once


// GridDialog dialog

class GridDialog : public CDialogEx
{
	DECLARE_DYNAMIC(GridDialog)

public:
	GridDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~GridDialog();
	int scale;
	CSliderCtrl m_ctrlSlider;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL OnInitDialog();
};
