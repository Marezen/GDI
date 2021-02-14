
#pragma once
#include "DImage.h"
class CMy03062015View : public CView
{
protected: // create from serialization only
	CMy03062015View() noexcept;
	DECLARE_DYNCREATE(CMy03062015View)

// Attributes
public:
	CMy03062015Doc* GetDocument() const;
	DImage *background; // pozadina novcica
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//funkcije zadatka:
	void DrawBackground(CDC* pDC,CPoint ptCenter,int radius,CString strPicture);
	void DrawCoin(CDC* pDC,CPoint ptCenter,int radius,CString strText,int fsizeText,CString strCoin,int fsizeCoin,COLORREF clrTExt);
	void SaveBMP(CString name,CDC* pDC,CPoint ptCEnter,int radius);

	//Transformacije
	void Rotate(CDC* pDC,float angle,bool right);
	void TranslateRotate(CDC* pDC,float x,float y,float angle,float distance);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy03062015View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 03.06.2015View.cpp
inline CMy03062015Doc* CMy03062015View::GetDocument() const
   { return reinterpret_cast<CMy03062015Doc*>(m_pDocument); }
#endif

