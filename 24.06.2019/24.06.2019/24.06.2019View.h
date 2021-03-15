#pragma once

class CMy24062019View : public CView
{
protected: // create from serialization only
	CMy24062019View() noexcept;
	DECLARE_DYNCREATE(CMy24062019View)
public:
	CMy24062019Doc* GetDocument() const;
	int x, y;
	CPoint point;
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//funkcije za zadatak:
	void DrawArrow(CDC* pDC,double r,int n,CString strParts,COLORREF colFill,COLORREF colLine,float angle);
	void DrawRoundedText(CDC* pDC,CRect rcText,double perc,COLORREF colFillRect,COLORREF colLineRect,CString Text,COLORREF colText,CPoint ptMouse,double r,int n,CString strParts,COLORREF colFillArrow,COLORREF colLIneArrow);

	//transformacije:
	void Translate(CDC* pDC,float dx,float dy,bool right);
	void Rotate(CDC* pDC,float angle,bool right);
	void TranslateRotate(CDC* PDC,float dx,float dy,float angle,float distance);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy24062019View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMsgName(UINT nHitTest, CPoint point);
};

#ifndef _DEBUG  // debug version in 24.06.2019View.cpp
inline CMy24062019Doc* CMy24062019View::GetDocument() const
   { return reinterpret_cast<CMy24062019Doc*>(m_pDocument); }
#endif

