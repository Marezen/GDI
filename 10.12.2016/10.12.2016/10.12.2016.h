
// 10.12.2016.h : main header file for the 10.12.2016 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy10122016App:
// See 10.12.2016.cpp for the implementation of this class
//

class CMy10122016App : public CWinApp
{
public:
	CMy10122016App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy10122016App theApp;
