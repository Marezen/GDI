
// 12.11.2011.h : main header file for the 12.11.2011 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy12112011App:
// See 12.11.2011.cpp for the implementation of this class
//

class CMy12112011App : public CWinApp
{
public:
	CMy12112011App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy12112011App theApp;
