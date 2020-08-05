
// KTMT_3Dlg.h : header file
//

#pragma once


// CKTMT3Dlg dialog
class CKTMT3Dlg : public CDialogEx
{
// Construction
public:
	CKTMT3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KTMT_3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit EDI_1;
	CEdit EDI_2;
	CEdit EDI_RES;
	CButton BUT_CAL;
	CButton RAD_INT;
	CButton RAD_FLO;
	afx_msg void Calculate();

	int cur_RAD_INT = 0, cur_RAD_FLO = 0, cur_type = 0, cur_inp_type = 1;

	CButton RAD_INT_[23];
	CButton RAD_FLO_[5];
	CButton RAD_INP_BIN, RAD_INP_FLO, RAD_INP_HEX;

	afx_msg void Disable_EDI_2();//Tat khung nhap 2
	afx_msg void Enable_EDI_2();//Bat khung nhap 2
	afx_msg void get_type();//Tim trang thai hien tai la QInt hay QFloat
	afx_msg void get_RAD_INT();//Tim trang thai tinh toan hien tai cua QInt
	afx_msg void get_RAD_FLO();//Tim trang thai tinh toan hien tai cua QFloat
	afx_msg void inp_type_dec();// 3 ham cuoi co tac dung tim trang thai he so hien tai.
	afx_msg void inp_type_bin();
	afx_msg void inp_type_hex();
};
