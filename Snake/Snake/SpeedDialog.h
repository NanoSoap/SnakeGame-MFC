#pragma once


// SpeedDialog dialog

class SpeedDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SpeedDialog)

public:
	int speed;
	SpeedDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~SpeedDialog();
	CSliderCtrl m_ctrlSlider;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	DECLARE_MESSAGE_MAP()
public:
	
	// BOOL OnInitDialog();
	afx_msg
		BOOL OnInitDialog();
	void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
};
