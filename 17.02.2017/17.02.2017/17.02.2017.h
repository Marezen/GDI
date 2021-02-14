
// 17.02.2017.h : main header file for the 17.02.2017 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy17022017App:
// See 17.02.2017.cpp for the implementation of this class
//

class CMy17022017App : public CWinApp
{
public:
	CMy17022017App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy17022017App theApp;
