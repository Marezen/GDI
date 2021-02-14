
// 11.03.2012.h : main header file for the 11.03.2012 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy11032012App:
// See 11.03.2012.cpp for the implementation of this class
//

class CMy11032012App : public CWinApp
{
public:
	CMy11032012App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy11032012App theApp;
