
// 06.12.2014.h : main header file for the 06.12.2014 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy06122014App:
// See 06.12.2014.cpp for the implementation of this class
//

class CMy06122014App : public CWinApp
{
public:
	CMy06122014App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy06122014App theApp;
