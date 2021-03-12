#pragma once
#include "DImage.h"

class CMy28082015View : public CView
{
protected: // create from serialization only
	CMy28082015View() noexcept;
	DECLARE_DYNCREATE(CMy28082015View)
public:
	CMy28082015Doc* GetDocument() const;
public:

	DImage* img;
	//pomocne promenljive pomocu kojih crtamo House,Menu,Arrow i Magnifier
	int tabX, tabY;
	int space; // razmak izmedju ta 4 cuda

public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//funkcije za zadatak:
	void DrawHouse(CRect rect);
	void DrawMenu(CRect rect);
	void DrawArrow(CRect rect);
	void DrawMagnifier(CRect rect);
	void DrawDisplay(CString sPicture, CRect rcPicture);
	void DrawTablet(float dx, float dy, CString sName);
	//transformacija
	void Translate(CDC* pDC,float dx,float dy);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy28082015View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in 28.08.2015View.cpp
inline CMy28082015Doc* CMy28082015View::GetDocument() const
   { return reinterpret_cast<CMy28082015Doc*>(m_pDocument); }
#endif