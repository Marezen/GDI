#pragma once
class CMy08122012View : public CView
{
protected: // create from serialization only
	CMy08122012View() noexcept;
	DECLARE_DYNCREATE(CMy08122012View)

// Attributes
public:
	CMy08122012Doc* GetDocument() const;
	//Atributi za zadatak
	//za levi tocak
	int leftX;
	int leftY;
	//za srednji
	int midX;
	int midY;
	//za desni 
	int rightX;
	int rightY;
	//vrednosti za rotaciju:
	float leftRot, midRot, rightRot;




// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//Funkcije za zadatak
	void DrawScene(CDC* pDC);
	void Trapez(CDC* pDC, float a, float b, float h);
	void DrawGear(CDC* pDC,int count,float width,int cx,int cy,float a); // morao sam da dodam koordinate
	//Transformacije
	void Translate(CDC* pDC,float x,float y);
	void Rotate(CDC* pDC,float angle);
	void Transform(CDC* pDC,float x,float y,float angle);
	void TranslateRotate(CDC* pDC,float x,float y,float angle,float distance);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy08122012View();
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in 08.12.2012View.cpp
inline CMy08122012Doc* CMy08122012View::GetDocument() const
   { return reinterpret_cast<CMy08122012Doc*>(m_pDocument); }
#endif

