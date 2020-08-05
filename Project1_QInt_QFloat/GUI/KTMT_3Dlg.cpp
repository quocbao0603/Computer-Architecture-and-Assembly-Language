
// KTMT_3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "KTMT_3.h"
#include "KTMT_3Dlg.h"
#include "afxdialogex.h"
#include "process.h"
#include <string>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKTMT3Dlg dialog



CKTMT3Dlg::CKTMT3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KTMT_3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKTMT3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDI_1, EDI_1);
	DDX_Control(pDX, IDC_EDI_2, EDI_2);
	DDX_Control(pDX, IDC_EDI_RES, EDI_RES);
	DDX_Control(pDX, IDC_BUT_CAL, BUT_CAL);
	DDX_Control(pDX, IDC_RAD_INT, RAD_INT);
	DDX_Control(pDX, IDC_RAD_FLO, RAD_FLO);


	//Create relation between QInt Radio and RAD_INT_ array.
	//See the ID to know each ID of Radio corresponding to each element of array.
	DDX_Control(pDX, IDC_RAD_INT_DTB, RAD_INT_[0]);
	DDX_Control(pDX, IDC_RAD_INT_BTD, RAD_INT_[1]);
	DDX_Control(pDX, IDC_RAD_INT_BTH, RAD_INT_[2]);
	DDX_Control(pDX, IDC_RAD_INT_DTH, RAD_INT_[3]);

	DDX_Control(pDX, IDC_RAD_INT_ADD, RAD_INT_[4]);
	DDX_Control(pDX, IDC_RAD_INT_MIN, RAD_INT_[5]);
	DDX_Control(pDX, IDC_RAD_INT_MUL, RAD_INT_[6]);
	DDX_Control(pDX, IDC_RAD_INT_DIV, RAD_INT_[7]);

	DDX_Control(pDX, IDC_RAD_INT_LES, RAD_INT_[8]);
	DDX_Control(pDX, IDC_RAD_INT_LOE, RAD_INT_[9]);
	DDX_Control(pDX, IDC_RAD_INT_BIG, RAD_INT_[10]);
	DDX_Control(pDX, IDC_RAD_INT_BOE, RAD_INT_[11]);

	DDX_Control(pDX, IDC_RAD_INT_EQU, RAD_INT_[12]);
	DDX_Control(pDX, IDC_RAD_INT_RIG, RAD_INT_[13]);
	DDX_Control(pDX, IDC_RAD_INT_LEF, RAD_INT_[14]);

	DDX_Control(pDX, IDC_RAD_INT_AND, RAD_INT_[15]);
	DDX_Control(pDX, IDC_RAD_INT_OR, RAD_INT_[16]);
	DDX_Control(pDX, IDC_RAD_INT_XOR, RAD_INT_[17]);
	DDX_Control(pDX, IDC_RAD_INT_NOT, RAD_INT_[18]);

	DDX_Control(pDX, IDC_RAD_INT_rol, RAD_INT_[19]);
	DDX_Control(pDX, IDC_RAD_INT_ROR, RAD_INT_[20]);

	DDX_Control(pDX, IDC_RAD_INT_HTB, RAD_INT_[21]);
	DDX_Control(pDX, IDC_RAD_INT_HTD, RAD_INT_[22]);
	///
	///

	//Create relation between QFloat Radio and RAD_FLO_ array.
	//See the ID to know each ID of Radio corresponding to each element of array.
	DDX_Control(pDX, IDC_RAD_FLO_DTB, RAD_FLO_[0]);
	DDX_Control(pDX, IDC_RAD_FLO_BTD, RAD_FLO_[1]);
	DDX_Control(pDX, IDC_RAD_FLO_ADD, RAD_FLO_[2]);
	DDX_Control(pDX, IDC_RAD_FLO_MIN, RAD_FLO_[3]);
	DDX_Control(pDX, IDC_RAD_FLO_MUL, RAD_FLO_[4]);
	DDX_Control(pDX, IDC_RAD_FLO_DIV, RAD_FLO_[5]);

	DDX_Control(pDX, IDC_RAD_INP_BIN, RAD_INP_BIN);
	DDX_Control(pDX, IDC_RAD_INP_DEC, RAD_INP_FLO);	
	DDX_Control(pDX, IDC_RAD_INP_HEX, RAD_INP_HEX);
}

BEGIN_MESSAGE_MAP(CKTMT3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_CAL, &CKTMT3Dlg::Calculate)
	//
	// Disable EDI_2 edit control when checking leftshift, rightshift, rol, ror radio button.
	//
	ON_BN_CLICKED(IDC_RAD_INT_RIG, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_LEF, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_rol, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_ROR, &CKTMT3Dlg::Enable_EDI_2)
	//
	// Disable EDI_2 edit control when checking leftshift, rightshift, rol, ror radio button.
	//
	ON_BN_CLICKED(IDC_RAD_INT_DTB, &CKTMT3Dlg::Disable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_BTD, &CKTMT3Dlg::Disable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_BTH, &CKTMT3Dlg::Disable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_DTH, &CKTMT3Dlg::Disable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_ADD, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_MIN, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_MUL, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_DIV, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_LES, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_LOE, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_BIG, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_BOE, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_EQU, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_AND, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_OR, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_XOR, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_NOT, &CKTMT3Dlg::Disable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_HTB, &CKTMT3Dlg::Disable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT_HTD, &CKTMT3Dlg::Disable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_FLO_DTB, &CKTMT3Dlg::Disable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_FLO_BTD, &CKTMT3Dlg::Disable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_FLO_ADD, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_FLO_MIN, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_FLO_MUL, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_FLO_DIV, &CKTMT3Dlg::Enable_EDI_2)
	ON_BN_CLICKED(IDC_RAD_INT, &CKTMT3Dlg::get_type)
	ON_BN_CLICKED(IDC_RAD_FLO, &CKTMT3Dlg::get_type)
	ON_BN_CLICKED(IDC_RAD_INP_BIN, &CKTMT3Dlg::inp_type_bin)
	ON_BN_CLICKED(IDC_RAD_INP_DEC, &CKTMT3Dlg::inp_type_dec)
	ON_BN_CLICKED(IDC_RAD_INP_HEX, &CKTMT3Dlg::inp_type_hex)
END_MESSAGE_MAP()


// CKTMT3Dlg message handlers

BOOL CKTMT3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	

	//Check default radio when init dialogbox.
	RAD_INT.SetCheck(1);
	RAD_INT_[0].SetCheck(1);
	RAD_FLO_[0].SetCheck(1);
	RAD_INP_FLO.SetCheck(1);
	Disable_EDI_2();
	UpdateData(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKTMT3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKTMT3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKTMT3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKTMT3Dlg::Calculate()
{
	//Update data
	UpdateData(1);
	CString c_input_1 = _T("");
	CString c_input_2 = _T("");

	//Get value of input_1, input_2 textboxs. 
	EDI_1.GetWindowTextW(c_input_1);
	EDI_2.GetWindowTextW(c_input_2);

	//Covert CString variable  (c_input_1, c_input_2) to std::string
	std::wstring str = (LPCTSTR)c_input_1;
	std::wstring str2 = (LPCTSTR)c_input_2;
	string input_1(str.begin(), str.end());
	string input_2(str2.begin(), str2.end());

	//Result variable
	string result;

	if (cur_type == 0) {
		//Xu ly Qint
		int radio = stoi(to_string(cur_RAD_INT));
		switch (radio) {
		//Truong hop toan tu 1 ngoi
		case 0:
		case 1:
		case 2:
		case 3:
		case 18:
		case 21:
		case 22:
			{
			result = process_IntUnaryOp(input_1, radio, cur_inp_type);
			break;
		}
		//Toan tu 2 ngoi
		default: {
			result = process_IntBinaryOp(input_1, input_2, radio, cur_inp_type);
			break;
		}
		}
	}
	//Xu ly Float
	else {
		int radio = stoi(to_string(cur_RAD_FLO));
		int cur_flo_inp_type = cur_inp_type == 0 ? 0 : 1;
		switch (radio) {
			//Truong hop toan tu 1 ngoi
		case 0:
		case 1:
		{
			result = process_FloUnaryOp(input_1, radio, cur_flo_inp_type);
			break;
		}
				 //Toan tu 2 ngoi
		default: {
			result = process_FloBinaryOp(input_1, input_2, radio, cur_flo_inp_type);
			break;
		}
		}
	}
	
	//Set result.
	CString c_result((result).c_str());
	EDI_RES.SetWindowTextW(c_result);
	UpdateData(0);

}






void CKTMT3Dlg::Disable_EDI_2()
{
	UpdateData(1);
	if (cur_type == 0) {
		get_RAD_INT();
		if ((cur_RAD_INT >= 0 && cur_RAD_INT <= 3) ||cur_RAD_INT == 18 || cur_RAD_INT == 21 || cur_RAD_INT <= 22) {
			EDI_2.EnableWindow(0);
			UpdateData(0);
		}
	}
	else {
		get_RAD_FLO();
		if (cur_RAD_FLO == 0 || cur_RAD_FLO == 1) {
			EDI_2.EnableWindow(0);
			UpdateData(0);
			
		}
	}
}


void CKTMT3Dlg::Enable_EDI_2()
{
	UpdateData(1);
	if (cur_type == 0) {
		get_RAD_INT();
		if ((cur_RAD_INT >= 4 && cur_RAD_INT <= 20) && cur_RAD_INT != 18) {
			EDI_2.EnableWindow(1);
			UpdateData(0);
		}
	}
	else {
		get_RAD_FLO();
		if (cur_RAD_FLO >= 2) {
			EDI_2.EnableWindow(1);
			UpdateData(0);
		}
	}
}

void CKTMT3Dlg::get_type(){
	UpdateData(1);
	if (RAD_INT.GetCheck()) cur_type = 0;
	else cur_type = 1;
	Disable_EDI_2();
	Enable_EDI_2();
}

void CKTMT3Dlg::get_RAD_INT(){
	UpdateData(1);
	for (int i = 0; i < 23; i++) {
		if (RAD_INT_[i].GetCheck()) {
			cur_RAD_INT = i;
			break;
		}
	}
}


void CKTMT3Dlg::get_RAD_FLO(){
	UpdateData(1);
	for (int i = 0; i < 6; i++) {
		if (RAD_FLO_[i].GetCheck()) {
			cur_RAD_FLO = i;
			break;
		}
	}
}

void CKTMT3Dlg::inp_type_dec(){
	UpdateData(1);
	cur_inp_type = 1;
}

void CKTMT3Dlg::inp_type_bin(){
	UpdateData(1);
	cur_inp_type = 0;
}

void CKTMT3Dlg::inp_type_hex() {
	UpdateData(1);
	cur_inp_type = 2;
}

