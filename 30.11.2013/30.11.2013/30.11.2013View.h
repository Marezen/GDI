#pragma once
#include "DImage.h"
class CMy30112013View : public CView
{
protected: // create from serialization only
	CMy30112013View() noexcept;
	DECLARE_DYNCREATE(CMy30112013View)

// Attributes
public:
	CMy30112013Doc* GetDocument() const;
	DImage *sky;
	DImage *bark;
	//POtrebni su nam dodatni atributi:
	float rotAngle; // ugao rotacije surikena
	float centerX, centerY; // centar koord sistema.
	float move; // za koliko se pomera ka drvetu
	int size; // velicina. Moze a i ne mora

	bool stop; // indikator kada udari u drvo , da prestane da se krece.
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//Funkcije za zadatak
	void DrawBlade(CDC* pDC,int size);
	void DrawStar(CDC* pDC,int size);

	//Transformacije
	void Translate(CDC* pDC, float x, float y);
	void Rotate(CDC* pDC, float angle);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy30112013View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in 30.11.2013View.cpp
inline CMy30112013Doc* CMy30112013View::GetDocument() const
   { return reinterpret_cast<CMy30112013Doc*>(m_pDocument); }
#endif

