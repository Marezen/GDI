#pragma once
class CMy25122011View : public CView
{
protected: 
	CMy25122011View() noexcept;
	DECLARE_DYNCREATE(CMy25122011View)
public:
	CMy25122011Doc* GetDocument() const;
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//funkcije:
	void CreateGradientBitmap(CDC* pDC,double w,double h,COLORREF col1,COLORREF col2);
	void DrawStar(CDC* pDC,CDC* bmpDC,int N,int R1,int R2,int xC,int yC);

	//transformacije
	void Translate(CDC* pDC,float dX,float dY);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy25122011View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 25.12.2011View.cpp
inline CMy25122011Doc* CMy25122011View::GetDocument() const
   { return reinterpret_cast<CMy25122011Doc*>(m_pDocument); }
#endif

