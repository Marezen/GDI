#pragma once
#include "DImage.h"
class CMy25032019View : public CView
{
protected: // create from serialization only
	CMy25032019View() noexcept;
	DECLARE_DYNCREATE(CMy25032019View)
public:
	CMy25032019Doc* GetDocument() const;
	DImage* img;
public: 
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//Fukncije za zadatak:
	void DrawWheel(CDC* pDC, double r1, double r2, double w);
	void DrawWP(CDC* pDC, double r1, double r2, double w, double L, double alpha, double d);
	//Transformacije
	void Rotate(CDC* pDC, float angle, bool right);
	void Translate(CDC* pDC, float x, float y, bool right);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy25032019View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in 25.03.2019View.cpp
inline CMy25032019Doc* CMy25032019View::GetDocument() const
   { return reinterpret_cast<CMy25032019Doc*>(m_pDocument); }
#endif