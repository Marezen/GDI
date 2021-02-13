
// 09.09.2016View.h : interface of the CMy09092016View class
//

#pragma once


class CMy09092016View : public CView
{
protected: // create from serialization only
	CMy09092016View() noexcept;
	DECLARE_DYNCREATE(CMy09092016View)

// Attributes
public:
	CMy09092016Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//funkcije za resenje zadatka:
	//glavna:
	void DrawClock(CDC* pDC,int h,int m, int s);
	//transformacije
	void Translate(CDC* pDC,float x,float y,bool right);
	void Rotate(CDC* pDC,float angle,bool right);
	void TranslateRotate(CDC* pDC,float x,float y,float angle,float distance);
	//za crtanje sata:
	void DrawNum(CDC* pDC,int x,int y);
	void DrawMarks(CDC* pDC,int x, int y);
	void DrawH(CDC* pDC, int x, int y); //hour
	void DrawM(CDC* pDC,int x,int y);   //minute
	void DrawS(CDC* pDC, int x, int y); //second
	void DrawNeedles(CDC* pDC,int x,int y,int sat,int min,int sek);
	//Poslednja,da se sacuva bitmapa:
	void Save(CString name,int x,int y);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	virtual ~CMy09092016View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 09.09.2016View.cpp
inline CMy09092016Doc* CMy09092016View::GetDocument() const
   { return reinterpret_cast<CMy09092016Doc*>(m_pDocument); }
#endif

