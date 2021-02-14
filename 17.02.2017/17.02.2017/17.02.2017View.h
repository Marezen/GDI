
// 17.02.2017View.h : interface of the CMy17022017View class
//

#pragma once


class CMy17022017View : public CView
{
protected: // create from serialization only
	CMy17022017View() noexcept;
	DECLARE_DYNCREATE(CMy17022017View)

// Attributes
public:
	CMy17022017Doc* GetDocument() const;
	//3 atributa su potrebne
	int CenterX, CenterY;
	float UgaoAlfa;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//Funkcije za Zadatak:
	void DrawMultiCircle(CDC* pDC, int radius, int nConc, COLORREF colFill, CString strText);
	void DrawFanyCircle(CDC* pDC, int radius, int nCircle, double dAlpha, int nConc, COLORREF colFillBig, COLORREF colFillSmall, CString strText);
	void SavePicture(CDC* pDC, CString pic, int radius);
	//Funkcije transformacija:
	void Rotate(CDC* pDC, float angle, bool right);
	void TranslateRotate(CDC* pDC, float x, float y, float angle, float distance);
	void Translate(CDC* pDC, float x, float y, bool right);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy17022017View();
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

#ifndef _DEBUG  // debug version in 17.02.2017View.cpp
inline CMy17022017Doc* CMy17022017View::GetDocument() const
   { return reinterpret_cast<CMy17022017Doc*>(m_pDocument); }
#endif

