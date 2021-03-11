
// 23.11.2007.h : main header file for the 23.11.2007 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy23112007App:
// See 23.11.2007.cpp for the implementation of this class
//

class CMy23112007App : public CWinApp
{
public:
	CMy23112007App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy23112007App theApp;
