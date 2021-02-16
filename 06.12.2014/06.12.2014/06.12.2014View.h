#pragma once
#include "DImage.h"

class CMy06122014View : public CView
{
protected: // create from serialization only
	CMy06122014View() noexcept;
	DECLARE_DYNCREATE(CMy06122014View)

// Attributes
public:
	CMy06122014Doc* GetDocument() const;
	//atributi zadatka
	HENHMETAFILE clio;
	DImage* wheel;
	int carW;
	int carH;
	int wheelSize;
	float moveAngle;
	float angleGround;
	float move;
	int carCenterX, carCenterY, lwX, lwY, rwX, rwY;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//funkcije za zadatak
	void DrawGround(CDC* pDC,float angle);
	void DrawCar(CDC* pDC,int x,int y,int w,int h);
	void DrawWheel(CDC* pDC,int x,int y,int r,float angle);

	//transformacije
	void Translate(CDC* pDC,float x,float y,bool right);
	void Rotate(CDC* pDC,float angle,bool right);
	void Scale(CDC* pDC,float Sx,float Sy,bool right);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy06122014View();
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

#ifndef _DEBUG  // debug version in 06.12.2014View.cpp
inline CMy06122014Doc* CMy06122014View::GetDocument() const
   { return reinterpret_cast<CMy06122014Doc*>(m_pDocument); }
#endif

