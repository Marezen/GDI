#pragma once
#include "DImage.h"
class CMy05122015View : public CView
{
protected: // create from serialization only
	CMy05122015View() noexcept;
	DECLARE_DYNCREATE(CMy05122015View)

// Attributes
public:
	CMy05122015Doc* GetDocument() const;
	//atributi za zadatak:
	DImage* pozadina;
	int pacmanP; // poluprecnik pacmana
	int eyeP;    //poluprecnik pacmanovog oka
	int pomX;
	int pomY;

	bool stanjeUsta; // kad otvori i zatori usta
	bool desno;
	bool gore;
	bool kraj; // indikator da li je dosao u kontakt sa duhom.

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//Funkcije za zadatak:
	void NacrtajScenu(CDC* pDC, CRect rect);
	void NacrtajPozadinu(CDC* pDC, CRect rect);
	void DrawPacman(CDC* pDC, CRect rect, float angle);
	void DrawGhost(CDC* pDC, CRect rect);
	void NacrtajOko(int pomeraj, CDC* pDC, CRect& rect);
	//Funkcije transformacija
	void Transform(CDC* pDC, CRect rect, int cx, int cy, int x, int y, double angle, double scale, bool mirror);
	void Translate(CDC* pDC, float x, float y);
	void Rotate(CDC* pDC, float angle);
	void Mirror(CDC* pDC);
	void Scale(CDC* pDC, float scale);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy05122015View();
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

#ifndef _DEBUG  // debug version in 05.12.2015View.cpp
inline CMy05122015Doc* CMy05122015View::GetDocument() const
   { return reinterpret_cast<CMy05122015Doc*>(m_pDocument); }
#endif

