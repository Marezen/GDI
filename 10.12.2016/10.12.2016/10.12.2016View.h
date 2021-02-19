
#pragma once
#include "DImage.h"

class CMy10122016View : public CView
{
protected: // create from serialization only
	CMy10122016View() noexcept;
	DECLARE_DYNCREATE(CMy10122016View)

// Attributes
public:
	CMy10122016Doc* GetDocument() const;

	//atributi za zadatak:
	DImage* table;
	DImage* frame;
	//posto imamo pomeranja:
	double angle;
	double ballAngle;
	int stickX;
	int stickY;
	int ballX;
	int ballY;
	int ballR; // poluprecnik kugle
	bool stick;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//funkcije za zadatak:
	void DrawScene(CDC* pDC,CRect rect,int size);
	void DrawBorder(CDC* pDC, CRect rect, int w); // okvir i sto
	void DrawStick(CDC* pDC,int w);
	void DrawBall(CDC* pDC, int w);
	void DrawHoles(CDC* pDC,CRect rect,int size); // crta 6 rupa
	//pomocna: 
	void DrawHole(CDC* pDC, CRect rect, int size, int x, int y); // crta 1 rupu i pozicionira je
	//funkcije za transformacije:
	void Translate(CDC* pDC,float x,float y,bool right);
	void Rotate(CDC* pDC,float angle,bool right);
	void Reset(CDC* pDC);   // uvek je potrebno resetovati
	void Transform(CDC* pDC, float x, float y, float cx, float cy, float angle); // da bi bio kraci kod
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy10122016View();
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

#ifndef _DEBUG  // debug version in 10.12.2016View.cpp
inline CMy10122016Doc* CMy10122016View::GetDocument() const
   { return reinterpret_cast<CMy10122016Doc*>(m_pDocument); }
#endif

