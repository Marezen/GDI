
// 12.11.2011View.h : interface of the CMy12112011View class
//
#pragma once
class CMy12112011View : public CView
{
protected: // create from serialization only
	CMy12112011View() noexcept;
	DECLARE_DYNCREATE(CMy12112011View)

// Attributes
public:
	CMy12112011Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC); 
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//funkcije koje se traze u zadatku:
	XFORM Translate(float x, float y);
	XFORM Rotate(float a);
	XFORM Reflect(float Sx,float Sy);
	void DrawTriangle(CDC* pDC);
	void Save();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy12112011View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 12.11.2011View.cpp
inline CMy12112011Doc* CMy12112011View::GetDocument() const
   { return reinterpret_cast<CMy12112011Doc*>(m_pDocument); }
#endif

