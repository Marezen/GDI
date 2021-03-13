#pragma once

class CMy05022020View : public CView
{
protected: 
	CMy05022020View() noexcept;
	DECLARE_DYNCREATE(CMy05022020View)
public:
	CMy05022020Doc* GetDocument() const;
public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//Funkcije za zadatak:
	void DrawCycle(CDC* pDC,int r,int n,int d);
	void DrawBicycle(CDC* pDC,int r,int n,int d,int alfa,int beta);
	void DrawText(CDC* pDC,int size,CString strText,COLORREF colorText);
	void SaveDC(CDC* pDC,CRect rcDC,CRect rcBMP);
	//Transformacije:
	void Reset(CDC* pDC);
	void Translate(CDC* pDC,float dx,float dy,bool right);
	void Rotate(CDC* pDC,float angle,bool right);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	virtual ~CMy05022020View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in 05.02.2020View.cpp
inline CMy05022020Doc* CMy05022020View::GetDocument() const
   { return reinterpret_cast<CMy05022020Doc*>(m_pDocument); }
#endif

