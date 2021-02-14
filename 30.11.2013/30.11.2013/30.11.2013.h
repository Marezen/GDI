
// 30.11.2013.h : main header file for the 30.11.2013 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy30112013App:
// See 30.11.2013.cpp for the implementation of this class
//

class CMy30112013App : public CWinApp
{
public:
	CMy30112013App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy30112013App theApp;
