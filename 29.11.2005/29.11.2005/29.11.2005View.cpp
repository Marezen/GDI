#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "29.11.2005.h"
#endif
#include "29.11.2005Doc.h"
#include "29.11.2005View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CMy29112005View, CView)

BEGIN_MESSAGE_MAP(CMy29112005View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CMy29112005View::CMy29112005View() noexcept
{
}
CMy29112005View::~CMy29112005View()
{
}
BOOL CMy29112005View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy29112005View::OnDraw(CDC* pDC)
{
	CMy29112005Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	DrawRectangle(pDC);
	DrawCircle(pDC);
	DrawDimensionLines(pDC);
}
//Funkcije za zadatak:
void CMy29112005View::DrawRectangle(CDC* pDC)
{
	CPen pen;
	pen.CreatePen(PS_SOLID,3,RGB(0,0,192));
	CPen* oldPen = pDC->SelectObject(&pen);
	
	CBrush brush;
	brush.CreateHatchBrush(HS_BDIAGONAL,RGB(0,0,192));
	CBrush* oldBrush = pDC->SelectObject(&brush);
	COLORREF oldColor = pDC->SetBkColor(RGB(255, 255, 0));

	pDC->Rectangle(100, 100, 300, 200); // ceo teren

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	pDC->SetBkColor(oldColor);
	brush.DeleteObject();
	pen.DeleteObject();
}
void CMy29112005View::DrawDimensionLines(CDC* pDC)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 192));
	CPen* oldPen = pDC->SelectObject(&pen);
	//prvo elipsa:
	//gornja
	pDC->MoveTo(150, 125);
	pDC->LineTo(78, 125);
	//donja
	pDC->MoveTo(150, 175);
	pDC->LineTo(78, 175);
	//od gore do dole,sa leve strane ove linije ide tekst
	pDC->MoveTo(85, 120);
	pDC->LineTo(85, 180);

	//one dve crtice manje
	pDC->MoveTo(78, 120);
	pDC->LineTo(92, 130);

	pDC->MoveTo(78, 170);
	pDC->LineTo(92, 180);

	//desna strana,visina terena
	//gornja linija
	pDC->MoveTo(300, 100);
	pDC->LineTo(322, 100);
	//donja linija
	pDC->MoveTo(300, 200);
	pDC->LineTo(322, 200);
	//od gornje do donje,sa desne strane ove linije je tekst
	pDC->MoveTo(315, 95);
	pDC->LineTo(315, 205);
	//2 manje
	pDC->MoveTo(308, 95);
	pDC->LineTo(322, 105);
	pDC->MoveTo(308, 195);
	pDC->LineTo(322, 205);

	//sirina terena
	//leva crta 
	pDC->MoveTo(100, 200);
	pDC->LineTo(100, 222);
	//desna
	pDC->MoveTo(300, 200);
	pDC->LineTo(300, 222);
	//s leva na desno,ispod te linije je tekst
	pDC->MoveTo(95, 215);
	pDC->LineTo(305, 215);
	//2 one manje crtice
	pDC->MoveTo(95, 222);
	pDC->LineTo(105, 208);

	pDC->MoveTo(295, 222);
	pDC->LineTo(305, 208);

	//sada tekstovi
	CFont font1;
	font1.CreateFontW(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Verdana"));
	CFont font2;//zarotirani
	font2.CreateFontW(12, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Verdana"));

	UINT flags=pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);
	int prevMode = pDC->SetBkMode(TRANSPARENT);
	CFont* oldFont = pDC->SelectObject(&font1);
	//ispis
	pDC->TextOutW(200, 215, CString("200 mm"));

	pDC->SelectObject(&font2);
	//ispis,levo i desno,zarotirano
	pDC->TextOutW(85, 150, CString("50 mm"));
	pDC->TextOutW(315, 150, CString("100 mm"));

	pDC->SetTextAlign(flags);
	pDC->SetBkMode(prevMode);
	font1.DeleteObject();
	font2.DeleteObject();
	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}
void CMy29112005View::DrawCircle(CDC* pDC)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 3, RGB(0, 0, 192));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 192));
	CBrush* oldBrush = pDC->SelectObject(&brush);
	COLORREF oldColor = pDC->SetBkColor(RGB(255, 128, 0));

	pDC->Ellipse(125, 125, 175, 175);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	pDC->SetBkColor(oldColor);
	pen.DeleteObject();
	brush.DeleteObject();
}
#pragma region ...
BOOL CMy29112005View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy29112005View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy29112005View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy29112005View::AssertValid() const
{
	CView::AssertValid();
}
void CMy29112005View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy29112005Doc* CMy29112005View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy29112005Doc)));
	return (CMy29112005Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion