#pragma once
#include "DImage.h"
class CMy09122017View : public CView
{
protected: // create from serialization only
	CMy09122017View() noexcept;
	DECLARE_DYNCREATE(CMy09122017View)

// Attributes
public:
	CMy09122017Doc* GetDocument() const;
	//atributi za zadatak
	DImage *body, * leg1, * leg2, * leg3, *back;
	int width = 1920;
	int height = 1080;
	int bodyX;
	int bodyY;
	bool povecaj, smanji;
	int moveX, moveY; // za pomeranje 
	//Koordinate Pozadine koje dodajemo kada stiskamo WASD
	int x1, y1;
	int x2, y2;
	//Rotacije nogu  prilikom pritiska strelice na desno
	int frontRight, frontLeft; // prednje noge
	int backRight, backLeft; // zadnje noge
	int Step; // za promenu rotacije
// Operations
public:

public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//Funkcije za zadatak:
	
	void DrawScene(CDC* pDC,CRect rect);
	void DrawLeg(CDC* pDC,double angle,double dx,double dy);
	//Transformacije
	void LoadIdentity(CDC* pDC); // reset sve
	void Translate(CDC* pDC,float dX,float dY,bool right);
	void Rotate(CDC* pDC,float angle,bool right);
	void Scale(CDC* pDC,float sX,float sY,bool right);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy09122017View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in 09.12.2017View.cpp
inline CMy09122017Doc* CMy09122017View::GetDocument() const
   { return reinterpret_cast<CMy09122017Doc*>(m_pDocument); }
#endif

