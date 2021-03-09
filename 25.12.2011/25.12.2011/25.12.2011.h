
// 25.12.2011.h : main header file for the 25.12.2011 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy25122011App:
// See 25.12.2011.cpp for the implementation of this class
//

class CMy25122011App : public CWinApp
{
public:
	CMy25122011App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy25122011App theApp;
