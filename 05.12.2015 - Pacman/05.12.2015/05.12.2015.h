
// 05.12.2015.h : main header file for the 05.12.2015 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy05122015App:
// See 05.12.2015.cpp for the implementation of this class
//

class CMy05122015App : public CWinApp
{
public:
	CMy05122015App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy05122015App theApp;
