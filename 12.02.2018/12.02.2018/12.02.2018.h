
// 12.02.2018.h : main header file for the 12.02.2018 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy12022018App:
// See 12.02.2018.cpp for the implementation of this class
//

class CMy12022018App : public CWinApp
{
public:
	CMy12022018App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy12022018App theApp;
