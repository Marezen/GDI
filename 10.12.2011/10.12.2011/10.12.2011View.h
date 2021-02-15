
// 10.12.2011View.h : interface of the CMy10122011View class
//

#pragma once
#include "DImage.h"

class CMy10122011View : public CView
{
protected: // create from serialization only
	CMy10122011View() noexcept;
	DECLARE_DYNCREATE(CMy10122011View)

// Attributes
public:
	CMy10122011Doc* GetDocument() const;
	DImage* sky; // pozadina
	int move;    // pomeraj automobila i tockova
	HENHMETAFILE wheel, car; // metafajlovi
	//velicine
	int car_height;
	int car_width;
	int wheel_height;
	int wheel_width;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//Funkcije za zadatak:
	void Draw(CRect rect,CDC* pDC);
	//Transformacije
	void Translate(CDC* pDC, float x, float y, bool right);
	void Rotate(CDC* pDC,float angle,bool right);
	void TranslateRotate(CDC* pDC,float x,float y,float angle);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy10122011View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in 10.12.2011View.cpp
inline CMy10122011Doc* CMy10122011View::GetDocument() const
   { return reinterpret_cast<CMy10122011Doc*>(m_pDocument); }
#endif

