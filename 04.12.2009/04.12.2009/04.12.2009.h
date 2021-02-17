
// 04.12.2009.h : main header file for the 04.12.2009 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy04122009App:
// See 04.12.2009.cpp for the implementation of this class
//

class CMy04122009App : public CWinApp
{
public:
	CMy04122009App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy04122009App theApp;
