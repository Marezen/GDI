
#pragma once
#include "DImage.h"
class CMy11032012View : public CView
{
protected: // create from serialization only
	CMy11032012View() noexcept;
	DECLARE_DYNCREATE(CMy11032012View)

// Attributes
public:
	CMy11032012Doc* GetDocument() const;
	//Koordinate centra:
	int CenterX, CenterY;
	DImage* img; // slika koju secemo  i dobijamo bmp u obliku trougla
	int size; // velicina cveta

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//funkcije za zadatak:
	void DrawRosete(CDC* pDC,int x,int y,int size,int count);
	void CreateTriangleBmp(CString fileName);
	//transformacije:
	void Rotate(CDC* pDC,float angle,bool right);
	void TranslateRotate(CDC* pDC,float x,float y,float angle,float distance);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy11032012View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 11.03.2012View.cpp
inline CMy11032012Doc* CMy11032012View::GetDocument() const
   { return reinterpret_cast<CMy11032012Doc*>(m_pDocument); }
#endif

