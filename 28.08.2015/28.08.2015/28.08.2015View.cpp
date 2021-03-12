#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "28.08.2015.h"
#endif
#include "28.08.2015Doc.h"
#include "28.08.2015View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy28082015View, CView)

BEGIN_MESSAGE_MAP(CMy28082015View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CMy28082015View::CMy28082015View() noexcept
{
	img = new DImage();
	space = 0;
}
CMy28082015View::~CMy28082015View()
{
}
BOOL CMy28082015View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy28082015View::OnDraw(CDC* pDC)
{
	CMy28082015Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	DrawTablet(300, 400, CString("Prestigio"));

}
//Funkcije za zadatak:
void CMy28082015View::DrawHouse(CRect rect)
{
	CDC* pDC = GetDC();
	//moralo ovde da se ubaci pomeranje
	XFORM form;
	int oldMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->GetWorldTransform(&form);
	Translate(pDC, tabX, tabY);


	CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(255,255,255));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateStockObject(HOLLOW_BRUSH);
	CBrush* oldBrush = pDC->SelectObject(&brush);

	CPoint roof[3];
	roof[0] = CPoint(rect.Width()/2,0); // vrh
	roof[1] = CPoint(0,0.3*rect.Height()); // leva tacka
	roof[2] = CPoint(rect.Width(),0.3*rect.Height());  //desna

	CPoint house[4];
	house[0] = CPoint(0.2*rect.Width(),0.3*rect.Height()); // leva gore
	house[1] = CPoint(0.2 * rect.Width(),rect.Height());   // leva dole
	house[2] = CPoint(0.8*rect.Width(),rect.Height());     // desna dole
	house[3] = CPoint(0.8*rect.Width(),0.3*rect.Height()); // desna gore

	pDC->Polygon(roof,3);
	pDC->Polygon(house,4);


	SetGraphicsMode(pDC->m_hDC, oldMode);
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}
void CMy28082015View::DrawMenu(CRect rect)
{
	CDC* pDC = GetDC();
	//posto ovo crtamo posle kucice
	//menjamo koordinatu tabX
	tabX += space;
	//moralo ovde da se ubaci pomeranje
	XFORM form;
	int oldMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->GetWorldTransform(&form);
	Translate(pDC, tabX, tabY);

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateStockObject(HOLLOW_BRUSH);
	CBrush* oldBrush = pDC->SelectObject(&brush);

	//pravougaonik jedan u drugom
	pDC->Rectangle(0, 0, rect.Width(), rect.Height());//ceo
	pDC->Rectangle(0,0,rect.Width(),rect.Height()*0.3);
	pDC->Rectangle(0,0, rect.Width(),rect.Height()*0.5);
	pDC->Rectangle(0, 0, rect.Width(), rect.Height() * 0.7);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}
void CMy28082015View::DrawArrow(CRect rect)
{
	CDC* pDC = GetDC();
	//posto ovo crtamo posle menija
	//opet pomeramo na desno
	tabX += space;
	XFORM form;
	int oldMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->GetWorldTransform(&form);
	Translate(pDC, tabX, tabY);

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	CPen* oldPen = pDC->SelectObject(&pen);

	pDC->Arc(-rect.Width(), 0.1 * rect.Height(), rect.Width(), 2 * rect.Height(), rect.Width(), rect.Height(), 0, 0.1 * rect.Height());
	pDC->MoveTo(0, 0.1 * rect.Height());
	pDC->LineTo(0.3 * rect.Width(), 0);
	pDC->MoveTo(0, 0.1 * rect.Height());
	pDC->LineTo(0.32 * rect.Width(), 0.34* rect.Height());

	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}
void CMy28082015View::DrawMagnifier(CRect rect)
{
	CDC* pDC = GetDC();
	//posto ovo crtamo posle strelice
	//opet pomeramo na desno
	tabX += space;
	XFORM form;
	int oldMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->GetWorldTransform(&form);
	Translate(pDC, tabX, tabY);

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateStockObject(HOLLOW_BRUSH);
	CBrush* oldBrush = pDC->SelectObject(&brush);

	pDC->Ellipse(0, 0, 0.6 * rect.Width(), 0.6 * rect.Height()); // lupa
	//drska
	pDC->MoveTo(0.51 * rect.Width(), 0.51 * rect.Height());
	pDC->LineTo(rect.Width(), rect.Height());;



	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}
void CMy28082015View::DrawDisplay(CString sPicture, CRect rcPicture)
{
	CDC* pDC = GetDC();
	//kreiramo region za display
	CRgn rgn;
	rgn.CreateRoundRectRgn(rcPicture.left + 1, rcPicture.top + 1, rcPicture.right - 1, rcPicture.bottom - 1, rcPicture.Width() / 20, rcPicture.Width() / 20);
	pDC->SelectClipRgn(&rgn, RGN_AND);
	img->Load(sPicture);
	img->Draw(pDC, CRect(0, 0, img->Width(), img->Height()), rcPicture);
	pDC->SelectClipRgn(NULL);
}
void CMy28082015View::DrawTablet(float dx,float dy,CString name)
{
	CDC* pDC = GetDC();
	CBrush silverBrush;
	silverBrush.CreateSolidBrush(RGB(224,224,224));
	CBrush* oldBrush = pDC->SelectObject(&silverBrush);
	  //spolnji
	pDC->RoundRect(0,0,dx,dy,40,40);

	CBrush grayBrush;
	grayBrush.CreateSolidBrush(RGB(64,64,64));
	oldBrush = pDC->SelectObject(&grayBrush);
	//unutrasnji
	
	pDC->RoundRect(0.05*dx,0.05*dy,0.95*dx,0.95*dy,40,40);
	//pa posle toga display
	DrawDisplay(CString("Prestigio.bmp"), CRect(0.125 * dx, 0.15 * dy, 0.875 * dx, 0.75 * dy));
	//sada odredimo koordinate odakle ce poceti da se crtaju ona 4 cuda ispod displeja
	tabX = 0.145 * dx;
	tabY = 0.8 * dy;
	space = 0.185 * dx;

	CRect houseRect = CRect(0.125 * dx, 0.75 * dy, 0.275 * dx, 0.85 * dy);
	CRect menuRect = CRect(0.105 * dx, 0.75 * dy, 0.255 * dx, 0.85 * dy);
	CRect arrowRect = CRect(0.125 * dx, 0.75 * dy, 0.275 * dx, 0.85 * dy);
	CRect magnifierRect = CRect(0.125 * dx, 0.75 * dy, 0.275 * dx, 0.85 * dy);

	//iscrtaj sve 4
	DrawHouse(houseRect);
	DrawMenu(menuRect);
	DrawArrow(arrowRect);
	DrawMagnifier(magnifierRect);
	//i tekst skroz gore:
	pDC->SetBkMode(TRANSPARENT);
	COLORREF oldClr = pDC->SetTextColor(RGB(255, 255, 255));

	CFont nFont;
	nFont.CreateFont(0.08 * dy, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));
	CFont* oldFont = pDC->SelectObject(&nFont);

	pDC->SetTextAlign(TA_CENTER);
	pDC->TextOut(0.5 * dx, 0.06 * dy, name);

	pDC->SelectObject(oldFont);
	nFont.DeleteObject();

	pDC->SelectObject(oldBrush);
	silverBrush.DeleteObject();
	grayBrush.DeleteObject();
}
void CMy28082015View::Translate(CDC* pDC,float dx,float dy)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = dx;
	form.eDy = dy;
	pDC->ModifyWorldTransform(&form,MWT_RIGHTMULTIPLY);
}
#pragma region....
BOOL CMy28082015View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy28082015View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy28082015View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CMy28082015View::AssertValid() const
{
	CView::AssertValid();
}
void CMy28082015View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy28082015Doc* CMy28082015View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy28082015Doc)));
	return (CMy28082015Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion