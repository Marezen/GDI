#pragma once
#include "DImage.h"
class CMy24042017View : public CView
{
protected: // create from serialization only
	CMy24042017View() noexcept;
	DECLARE_DYNCREATE(CMy24042017View)

// Attributes
public:
	CMy24042017Doc* GetDocument() const;
	
	DImage* img;
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//funkcije za zadatak:
	void DrawRosete(CDC* pDC,int x,int y,int size,int count);
	void RotateImage(char* filename,double alfa);
	//transformacije
	void Rotate(CDC* pDC,float angle);
	void TranslateRotate(CDC* pDC, float x, float y, float angle, float distance);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy24042017View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 24.04.2017View.cpp
inline CMy24042017Doc* CMy24042017View::GetDocument() const
   { return reinterpret_cast<CMy24042017Doc*>(m_pDocument); }
#endif

