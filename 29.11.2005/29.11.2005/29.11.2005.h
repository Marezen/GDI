
// 29.11.2005.h : main header file for the 29.11.2005 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy29112005App:
// See 29.11.2005.cpp for the implementation of this class
//

class CMy29112005App : public CWinApp
{
public:
	CMy29112005App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy29112005App theApp;
