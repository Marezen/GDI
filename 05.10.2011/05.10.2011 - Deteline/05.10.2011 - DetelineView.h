#pragma once
#include "DImage.h"

class CMy05102011DetelineView : public CView
{
protected: // create from serialization only
	CMy05102011DetelineView() noexcept;
	DECLARE_DYNCREATE(CMy05102011DetelineView)

// Attributes
public:
	CMy05102011DetelineDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//Funkcije za zadatak:
	void DrawFigure(CDC* pDC,int size,COLORREF colFill,COLORREF colLine);
	void DrawComplexFigure(CDC* pDC, int size, COLORREF colFill[], COLORREF colLine, double ratio, CString str);
	void DrawPicture(CDC* pDC, int size, COLORREF colFill[], COLORREF colLine, double ratio, int row, int col);
	void SaveHMetaFile(CDC* pDC);

	//transformacije
	void Translate(CDC* pDC,float dx,float dy,bool right);
	void TranslateRotate(CDC* pDC,float angle,float dx,float dy);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy05102011DetelineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 05.10.2011 - DetelineView.cpp
inline CMy05102011DetelineDoc* CMy05102011DetelineView::GetDocument() const
   { return reinterpret_cast<CMy05102011DetelineDoc*>(m_pDocument); }
#endif

