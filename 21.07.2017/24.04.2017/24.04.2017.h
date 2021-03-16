
// 24.04.2017.h : main header file for the 24.04.2017 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy24042017App:
// See 24.04.2017.cpp for the implementation of this class
//

class CMy24042017App : public CWinApp
{
public:
	CMy24042017App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy24042017App theApp;
