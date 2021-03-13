#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "05.02.2020.h"
#endif
#include "05.02.2020Doc.h"
#include "05.02.2020View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy05022020View, CView)

BEGIN_MESSAGE_MAP(CMy05022020View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CMy05022020View::CMy05022020View() noexcept
{

}
CMy05022020View::~CMy05022020View()
{
}
BOOL CMy05022020View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy05022020View::OnDraw(CDC* pDC)
{
	CMy05022020Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(&rect);
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(&bmp);

	int oldMode = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM form;
	memDC->GetWorldTransform(&form);
	//Crtanje:
	Translate(memDC,300,200,true);
	//DrawCycle(memDC,50,20,3);
	DrawBicycle(memDC,100,20,3,10,5);
	//kraj crtanja


	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	SaveDC(memDC, rect, CRect(0, 0, rect.Width() * 0.5, rect.Height()));
	//SaveDC(memDC, rect, CRect(0, 0, rect.Width() * 0.5, rect.Height()));
	memDC->DeleteDC();
	delete memDC;
}
//Funkcije za zadatak:
void CMy05022020View::DrawCycle(CDC* pDC, int r, int n, int d)
{
	// n spona
	CPen pen;
	pen.CreatePen(PS_SOLID,d,RGB(10,10,255));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateStockObject(HOLLOW_BRUSH);
	CBrush* oldBrush = pDC->SelectObject(&brush);
	//Veci krug
	pDC->Ellipse(-r,-r,r,r);
	//spone,tanja linija je potrebna
	CPen pen2;
	pen2.CreatePen(PS_SOLID, d-2, RGB(10, 15, 255));
	oldPen = pDC->SelectObject(&pen2);

	int x, y; // pomocne promenljive
	double innerAngle = ((360 / n) * 3.141 / 180);
	for (int i = 0; i < n; i++)
	{
		pDC->MoveTo(0,0);
		x = r * cos((double)(innerAngle * i));
		y = r * sin((double)(innerAngle * i));
		pDC->LineTo(x,y);
	}
	
	CBrush innerBrush;
	innerBrush.CreateSolidBrush(RGB(10,10,255));
	pDC->SelectObject(&innerBrush);
	pDC->SelectObject(&pen);
	//manji krug
	pDC->Ellipse(-2*d,-2*d,2*d,2*d);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pen.DeleteObject();
	pen2.DeleteObject();
}
void CMy05022020View::DrawBicycle(CDC* pDC,int r,int n,int d,int alfa,int beta)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, d, RGB(10, 10, 255));
	CPen* oldPen = pDC->SelectObject(&pen);

	CPen pen2;
	pen2.CreatePen(PS_SOLID, d, RGB(10, 10, 255));
	//Prednja osovina:
	float visinaOsovine = 1.4 * r;
	float pom = 0.2 * r;  // odnosi se na upravljac i pedale

	//osovina
	pDC->MoveTo(0,0);
	pDC->LineTo(0,-visinaOsovine);
	//upravljac
	pDC->LineTo(pom,-visinaOsovine);

	//pedale:
	int x, y;
	//zarotirana za ugao alfa
	x = 0.4*r * cos((double)(alfa));
	y = 0.4*r * sin((double)(alfa));
	pDC->MoveTo(x-pom/3,y); // malo na levo da ide,da bi crtica koju povucemo bila lepo postavljena
	pDC->LineTo(x+pom/2, y); // crtamo pedalu
	pDC->MoveTo(x,y);// nakon toga se podesimo na tacku odakle da povucemo sled  ecu liniju koja predstavlja liniju izmedju pedala
	pDC->LineTo(-x,-y); // krajnja tacka 
	pDC->MoveTo(-x+pom/3,-y); // i onda crtamo drugu pedalu
	pDC->LineTo(-x-pom/2,-y);
	//pedale ce uvek biti crtane horizontalno,jer se crtica koju povecavamo, menja samo po X osi
	pDC->SelectObject(&pen);
	//prvi luk
	int luk = 1.2 * r;
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->Arc(-luk,-luk,luk,luk,0,-luk,luk,0);
	//sediste:
	oldPen = pDC->SelectObject(&pen2);
	x = 1.4 * r * cos((double)(beta));
	y = 1.2 * r * sin((double)(beta));
	pDC->MoveTo(x, y);
	pDC->LineTo(x + 0.2 * r, y - 0.2 * r);
	//horizontalni deo
	oldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(x+0.2*r-0.1*r,y-0.2*r);
	pDC->LineTo(x+0.2*r+0.1*r,y-0.2*r);

	//drugi luk,koji nadovezujemo na prvi
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->Arc(luk,-r/1.5,2*luk,r/1.5,luk,0,luk+luk/2,r/1.5);
	//oslonac za penjanje
	pDC->MoveTo(luk,0);
	pDC->LineTo(luk+0.2*r,0);

	DrawCycle(pDC,r,n-2,d);
	//na kraj luka,stavimo drugi tocak
	Translate(pDC, luk + luk / 2, r / 1.5,true);
	DrawCycle(pDC,r/4,n,d);
	Translate(pDC,30,-30, true);
	DrawText(pDC,20,(CString)"penny-farthing",RGB(10,10,255));
	pDC->SelectObject(oldPen);
	pen2.DeleteObject();
	pen.DeleteObject();
}
void CMy05022020View::DrawText(CDC* pDC, int size, CString strText, COLORREF colorText)
{
	CFont font;
	font.CreateFont(size, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont* oldFont = pDC->SelectObject(&font);
	int oldTextMode = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	COLORREF oldCol = pDC->SetTextColor(colorText);
	Rotate(pDC, -90, false);
	pDC->TextOutW(1, -5, strText);


	pDC->SetBkMode(oldTextMode);
	pDC->SetTextAlign(oldTextAlign);
	pDC->SetTextColor(oldCol);
	pDC->SelectObject(oldFont);
}
void CMy05022020View::SaveDC(CDC* pDC, CRect rcDC, CRect rcBmp)
{
	int width = rcBmp.Width();
	int height = rcBmp.Height();
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rcDC.Width() / 2 - 50, rcDC.Height());
	memDC->SelectObject(&bmp);
	memDC->BitBlt(0, 0, width, height, pDC, 100, 0, SRCCOPY);
	DImage* picture = new DImage(bmp);
	picture->Save((CString)"Slika.bmp");
	delete picture;
	memDC->DeleteDC();
	delete memDC;
}
//Transformacije:
void CMy05022020View::Translate(CDC* pDC,float dx,float dy,bool right)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = dx;
	form.eDy = dy;
	if (right)
		pDC->ModifyWorldTransform(&form,MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
void CMy05022020View::Rotate(CDC* pDC, float angle, bool right)
{
	XFORM form;
	form.eM11 = cos((angle * 3.14) / 180);
	form.eM12 = sin((angle * 3.14) / 180);
	form.eM21 = -sin((angle * 3.14) / 180);
	form.eM22 = cos((angle * 3.14) / 180);
	form.eDx = 0;
	form.eDy = 0;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
#pragma region .....
BOOL CMy05022020View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy05022020View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy05022020View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy05022020View::AssertValid() const
{
	CView::AssertValid();
}
void CMy05022020View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy05022020Doc* CMy05022020View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy05022020Doc)));
	return (CMy05022020Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion