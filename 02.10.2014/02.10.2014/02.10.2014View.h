#pragma once
class CMy02102014View : public CView
{
protected: // create from serialization only
	CMy02102014View() noexcept;
	DECLARE_DYNCREATE(CMy02102014View)

public:
	CMy02102014Doc* GetDocument() const;

public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//Funkcije za zadatak:
	void DrawTree(CDC* pDC, int values[], int n, int dHor, int dVer, int rad, COLORREF colNode, COLORREF colLine);
	void Mirror(CDC* pDC);
	void SaveToBMP(CDC* pDC);
	//transformacije

	void Translate(CDC* pDC, float dx, float dy, bool right);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	virtual ~CMy02102014View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in 02.10.2014View.cpp
inline CMy02102014Doc* CMy02102014View::GetDocument() const
   { return reinterpret_cast<CMy02102014Doc*>(m_pDocument); }
#endif