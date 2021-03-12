
// 28.08.2015.h : main header file for the 28.08.2015 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy28082015App:
// See 28.08.2015.cpp for the implementation of this class
//

class CMy28082015App : public CWinApp
{
public:
	CMy28082015App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy28082015App theApp;
