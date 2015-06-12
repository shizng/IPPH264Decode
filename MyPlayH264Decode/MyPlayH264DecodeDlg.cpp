// MyPlayH264DecodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPlayH264Decode.h"
#include "MyPlayH264DecodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMyPlayH264DecodeDlg dialog




CMyPlayH264DecodeDlg::CMyPlayH264DecodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyPlayH264DecodeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyPlayH264DecodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyPlayH264DecodeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMyPlayH264DecodeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMyPlayH264DecodeDlg message handlers

BOOL CMyPlayH264DecodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyPlayH264DecodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyPlayH264DecodeDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyPlayH264DecodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMyPlayH264DecodeDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString filePath=m_F_sOpenAVIFile();
	m_oMyAVI.m_F_bReadAviFileBegin(filePath);
	m_oMyAVI.m_F_bStartVideoRetrieve();
	BITMAPINFOHEADER *mypBmp=new BITMAPINFOHEADER;
	mypBmp=NULL;
	//memset(mypBmp,0,sizeof(BITMAPINFOHEADER));
	m_oMyAVI.m_F_bGetVideoFrameAtTime(0,&mypBmp);
	m_oMyAVI.m_F_bEndVideoRetrieve();
	m_oMyAVI.m_F_bReadAviFileEnd();
	delete mypBmp;
	mypBmp=NULL;
	OnOK();
}
LPCTSTR CMyPlayH264DecodeDlg::m_F_sOpenAVIFile()
{
	
	OPENFILENAME ofn;
	TCHAR szName[MAX_PATH];
	//HWND hwnd;
	//HANDLE hf;
	::ZeroMemory(&ofn,sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.hwndOwner=this->m_hWnd;
	ofn.lpstrFile=szName;
	ofn.lpstrFile[0]='\0';
	ofn.nMaxFile=sizeof(szName);
	ofn.lpstrFilter=_T("avi file(.avi)\0*.avi\0");
	ofn.nFilterIndex=1;
	ofn.lpstrFileTitle=NULL;
	ofn.nMaxFileTitle=0;
	ofn.lpstrInitialDir=NULL;
	ofn.Flags=OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if(::GetOpenFileName(&ofn)==TRUE)
	{
		return ofn.lpstrFile;
	}
	return NULL;
}
