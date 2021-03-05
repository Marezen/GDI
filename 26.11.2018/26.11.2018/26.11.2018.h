
// 26.11.2018.h : main header file for the 26.11.2018 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy26112018App:
// See 26.11.2018.cpp for the implementation of this class
//

class CMy26112018App : public CWinApp
{
public:
	CMy26112018App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy26112018App theApp;
