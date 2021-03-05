#pragma once
#include "DImage.h"
class CMy26112018View : public CView
{
protected: // create from serialization only
	CMy26112018View() noexcept;
	DECLARE_DYNCREATE(CMy26112018View)

// Attributes
public:
	CMy26112018Doc* GetDocument() const;

	//Atributi za zadatak:
	DImage* bager;
	DImage* arm1;
	DImage* arm2;
	DImage* pozadina;
	HENHMETAFILE viljuska;
	CRect rectViljuska;
	CRect rect;
	float ugao_Arm1 = 0; 
	float ugao_Arm2 = 0;
	float ugao_Viljuska = 0;
	float napred_nazad; // za kretanje bagera levo desno


// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//Funkcije za zadatke
	void DrawBackground(CDC* pDC);
	void DrawTransparent(CDC* pDC,DImage* image); // ovo smo napravili u DImage klasi
	void DrawBody(CDC* pDC);
	void DrawArm1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawFork(CDC* pDC);
	void DrawExcavator(CDC* pDC);

	//Transformacije
	void Translate(CDC* pDC,float dx,float dy,bool right);
	void Rotate(CDC* pDC,float angle,bool right);
	void Scale(CDC* pDC,float dx,float dy,bool right);


protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy26112018View();
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

#ifndef _DEBUG  // debug version in 26.11.2018View.cpp
inline CMy26112018Doc* CMy26112018View::GetDocument() const
   { return reinterpret_cast<CMy26112018Doc*>(m_pDocument); }
#endif

