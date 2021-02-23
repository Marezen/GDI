
// 08.12.2012.h : main header file for the 08.12.2012 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy08122012App:
// See 08.12.2012.cpp for the implementation of this class
//

class CMy08122012App : public CWinApp
{
public:
	CMy08122012App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy08122012App theApp;
