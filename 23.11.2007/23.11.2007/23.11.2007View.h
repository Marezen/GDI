#pragma once
#include "DImage.h"
class CMy23112007View : public CView
{
protected: // create from serialization only
	CMy23112007View() noexcept;
	DECLARE_DYNCREATE(CMy23112007View)
public:
	//atributi za zadatak:
	DImage* router;
	int pos; // pozicija koverte

public:
	CMy23112007Doc* GetDocument() const;
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//funkcije za zadatak:
	void DrawRouters(CDC* pDC, CPoint* pts, int count);
	void DrawSerialLink(CDC* pDC, CPoint pt1, CPoint pt2);
	void DrawPacket(CDC* pDC, CPoint pt, int h);
	void DrawMessage(CDC* pDC, CPoint pt1, CPoint pt2, int pos, CSize size);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	virtual ~CMy23112007View();
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
};

#ifndef _DEBUG  // debug version in 23.11.2007View.cpp
inline CMy23112007Doc* CMy23112007View::GetDocument() const
   { return reinterpret_cast<CMy23112007Doc*>(m_pDocument); }
#endif

