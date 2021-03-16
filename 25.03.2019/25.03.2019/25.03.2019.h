
// 25.03.2019.h : main header file for the 25.03.2019 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy25032019App:
// See 25.03.2019.cpp for the implementation of this class
//

class CMy25032019App : public CWinApp
{
public:
	CMy25032019App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy25032019App theApp;
