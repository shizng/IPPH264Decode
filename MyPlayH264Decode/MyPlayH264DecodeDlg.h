// MyPlayH264DecodeDlg.h : header file
//

#pragma once
#include "AVIFile.h"

// CMyPlayH264DecodeDlg dialog
class CMyPlayH264DecodeDlg : public CDialog
{
// Construction
public:
	CMyPlayH264DecodeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYPLAYH264DECODE_DIALOG };

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
private:
	CAVIFile m_oMyAVI;
public:
	afx_msg void OnBnClickedOk();
	LPCTSTR m_F_sOpenAVIFile();
};
