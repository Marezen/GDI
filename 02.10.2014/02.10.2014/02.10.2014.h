
// 02.10.2014.h : main header file for the 02.10.2014 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy02102014App:
// See 02.10.2014.cpp for the implementation of this class
//

class CMy02102014App : public CWinApp
{
public:
	CMy02102014App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy02102014App theApp;
