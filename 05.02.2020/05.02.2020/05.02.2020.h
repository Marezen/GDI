
// 05.02.2020.h : main header file for the 05.02.2020 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy05022020App:
// See 05.02.2020.cpp for the implementation of this class
//

class CMy05022020App : public CWinApp
{
public:
	CMy05022020App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy05022020App theApp;
