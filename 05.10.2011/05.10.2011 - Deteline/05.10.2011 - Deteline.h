
// 05.10.2011 - Deteline.h : main header file for the 05.10.2011 - Deteline application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy05102011DetelineApp:
// See 05.10.2011 - Deteline.cpp for the implementation of this class
//

class CMy05102011DetelineApp : public CWinApp
{
public:
	CMy05102011DetelineApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy05102011DetelineApp theApp;
