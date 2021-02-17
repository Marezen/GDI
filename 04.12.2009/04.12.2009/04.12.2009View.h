
#pragma once
#include "DImage.h"
class CMy04122009View : public CView
{
protected: // create from serialization only
	CMy04122009View() noexcept;
	DECLARE_DYNCREATE(CMy04122009View)

// Attributes
public:
	CMy04122009Doc* GetDocument() const;
	DImage *im; // Slika na zidu
	DImage* sto;
	double angle;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//funkcije za zadatak:
	void Room(CDC* pDC,CRect rect);
	void Table(CDC* pDC, CRect rect);
	void Glass(CDC* pDC,CRect rect,CPoint bottle,double dAngle);
	void Bottle(CDC* pDC,CRect rect,CPoint bottle);
	//transformacije
	void Translate(CDC* pDC,float x,float y, bool right);
	void Rotate(CDC* pDC, float angle, bool right);
	void TranslateRotate(CDC* pDC,float x,float y,float angle,bool right);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy04122009View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 04.12.2009View.cpp
inline CMy04122009Doc* CMy04122009View::GetDocument() const
   { return reinterpret_cast<CMy04122009Doc*>(m_pDocument); }
#endif

