#pragma once

class CMy18012021View : public CView
{
protected: // create from serialization only
	CMy18012021View() noexcept;
	DECLARE_DYNCREATE(CMy18012021View)

// Attributes
public:
	CMy18012021Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//Funkcije za zadatak
	void DrawCycle(CDC* pDC,int r,int n,int d);
	void DrawVirus(CDC* PDC, CPoint ptCenter, int rad, int m, int r, int n, int d, int alpha, int size, CString strText, COLORREF color);
	void SaveDC(CDC* PDC,CRect rcDC,CRect rcBmp);
	//Transformacije
	void Translate(CDC* pDC,float dx,float dy,bool right);
	void Rotate(CDC* PDC,float angle,bool right);
	void TranslateRotate(CDC* pDC,float angle,float dx,float dy,float distance);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy18012021View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 18.01.2021View.cpp
inline CMy18012021Doc* CMy18012021View::GetDocument() const
   { return reinterpret_cast<CMy18012021Doc*>(m_pDocument); }
#endif

