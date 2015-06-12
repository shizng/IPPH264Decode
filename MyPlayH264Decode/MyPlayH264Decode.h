// MyPlayH264Decode.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMyPlayH264DecodeApp:
// See MyPlayH264Decode.cpp for the implementation of this class
//

class CMyPlayH264DecodeApp : public CWinApp
{
public:
	CMyPlayH264DecodeApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMyPlayH264DecodeApp theApp;