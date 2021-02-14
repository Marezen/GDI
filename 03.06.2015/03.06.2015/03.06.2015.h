
// 03.06.2015.h : main header file for the 03.06.2015 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy03062015App:
// See 03.06.2015.cpp for the implementation of this class
//

class CMy03062015App : public CWinApp
{
public:
	CMy03062015App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy03062015App theApp;
