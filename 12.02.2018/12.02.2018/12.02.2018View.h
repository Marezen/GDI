#pragma once
class CMy12022018View : public CView
{
protected: // create from serialization only
	CMy12022018View() noexcept;
	DECLARE_DYNCREATE(CMy12022018View)

// Attributes
public:
	CMy12022018Doc* GetDocument() const;
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//Funkcije za zadatak:
	void DrawTop(CDC* pDC,int size);
	void DrawTop2(CDC* pDC,int size);
	void DrawTail(CDC* pDC,int size,int count,double alfa);
	//transformacije:
	void LoadIdentity(CDC* pDC);
	void Mirror(CDC* pDC,bool x,bool right);
	void Translate(CDC* pDC,double x,double y,bool right);
	void Rotate(CDC* pDC,double angle,bool right);
	void TranslateRotate(CDC* pDC, float angle, float dx, float dy, float distance);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	virtual ~CMy12022018View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 12.02.2018View.cpp
inline CMy12022018Doc* CMy12022018View::GetDocument() const
   { return reinterpret_cast<CMy12022018Doc*>(m_pDocument); }
#endif