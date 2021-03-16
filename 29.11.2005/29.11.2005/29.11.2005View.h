#pragma once

class CMy29112005View : public CView
{
protected: // create from serialization only
	CMy29112005View() noexcept;
	DECLARE_DYNCREATE(CMy29112005View)

public:
	CMy29112005Doc* GetDocument() const;
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//funkcije za zadatak:
	void DrawRectangle(CDC* pDC);
	void DrawCircle(CDC* pDC);
	void DrawDimensionLines(CDC* pDC);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	virtual ~CMy29112005View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in 29.11.2005View.cpp
inline CMy29112005Doc* CMy29112005View::GetDocument() const
   { return reinterpret_cast<CMy29112005Doc*>(m_pDocument); }
#endif

