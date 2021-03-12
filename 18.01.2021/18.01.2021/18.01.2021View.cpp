#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "18.01.2021.h"
#endif
#include "18.01.2021Doc.h"
#include "18.01.2021View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CMy18012021View, CView)

BEGIN_MESSAGE_MAP(CMy18012021View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CMy18012021View::CMy18012021View() noexcept
{

}
CMy18012021View::~CMy18012021View()
{
}
BOOL CMy18012021View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion
void CMy18012021View::OnDraw(CDC* pDC)
{
	CMy18012021Doc* pDoc = GetDocument();
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
	//pocetak crtanja:
	//Centralna tacka:
	CPoint center;
	center.x = 300;
	center.y = 200;
	Translate(memDC,300,200,true);
	DrawVirus(memDC,center,150,6,15,6,2,90,15,(CString)"COVID-19",RGB(0,0,0));
	//kraj crtanja

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	SaveDC(memDC, rect, CRect(0, 0, rect.Width() * 0.5, rect.Height()));
	memDC->DeleteDC();
	delete memDC;
}
//Funkcije za zadatak:
void CMy18012021View::DrawCycle(CDC* pDC, int r, int n, int d)
{
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(255,255,255));
	CPen*  oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateStockObject(HOLLOW_BRUSH);
	CBrush* oldBrush = pDC->SelectObject(&brush);

	//pomocne promenljive da stavljamo vrednosti kooridnata tacaka
	int firstX;
	int firstY;
	//za radijalne duzi
	CPoint* radialPts= new CPoint[n];
	int toX, toY;
	//za mnogougao
	double innerAngle = ((360 / n) * 3.14159 / 180); 
	CPoint* points = new CPoint[n];
	for (int i = 0; i <= n; i++) 
	{
		firstX =  r * cos((double)(innerAngle * i));
		firstY =  r * sin((double)(innerAngle * i));
		//radijalne
		toX = 2* firstX;
		toY = 2*firstY;
		radialPts[i] = CPoint(toX,toY);
		points[i] = CPoint(firstX, firstY);
	}
	//crtamo mnogougao
	pDC->Polygon(points, n);

	CPen pen2;
	pen2.CreatePen(PS_SOLID, d, RGB(255, 255, 255));
	oldPen = pDC->SelectObject(&pen2);
	//crtanje radijalnih duzi:
	for (int i = 0; i < n; i++)
	{
		pDC->MoveTo(points[i].x, points[i].y);
		pDC->LineTo(radialPts[i].x, radialPts[i].y);
	}
	//nakon toga crtamo pravougaonik:
	//racunamo njegovu sirinu:
	//uzmemo 2 tacke mnogougla
	int sirina = sqrt((points[1].x - points[0].x) * (points[1].x - points[0].x) + (points[1].y - points[0].y) * (points[1].y - points[0].y));
	//int visina = 8 * length;
	int visina = 6 * r; // smanjio sam da bi se lakse i bolje videlo
	pDC->Rectangle(-sirina/2,r/2 + r/3,sirina/2,visina);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pen2.DeleteObject();
	pen.DeleteObject();
}
void CMy18012021View::DrawVirus(CDC* pDC, CPoint ptCenter, int rad, int m, int r, int n, int d, int alpha, int size, CString strText, COLORREF color)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, d, RGB(255, 255, 255));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(200,200,200));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	//crtamo veci krug
	pDC->Ellipse(-rad/2,-rad/2,rad/2,rad/2);
	//manji
	CPen pen2;
	pen2.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	oldPen = pDC->SelectObject(&pen2);

	CBrush brush2;
	brush2.CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = pDC->SelectObject(&brush2);

	pDC->Ellipse(-rad/2*0.8,-rad/2*0.8,rad/2*0.8,rad/2*0.8);


	int radius = rad+r; // da bi pozicionirali na obod veceg kruga
	int CenterX = ptCenter.x;
	int CenterY = ptCenter.y;

	float angle = 360 / m; 
	float tmpAngle = 0;
	for (int i = 0; i < m; i++)
	{
		XFORM form;
		pDC->GetWorldTransform(&form);
		//za 240 stepeni , iz zadatka
		TranslateRotate(pDC, tmpAngle+30, CenterX, CenterY, radius); // pozicija grane u odnosu na centar
		//ovo +30 je da bi se pozicioniralo kao na slici
		Rotate(pDC,alpha,false); // rotira za 90 da bi bilo dobro podeseno, bez ovoga Cycle ne stoji uspravno u odnosu na krug
		DrawCycle(pDC,r,6,d);
		// mora da oduzme tmpAngle i 240 i dAlpha , da bi Broj u malom krugu bio uspravan uvek
		pDC->SetWorldTransform(&form);
		tmpAngle += angle;
	}

	//tekst:
	CFont font;
	font.CreateFont(size, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont* oldFont = pDC->SelectObject(&font);
	int oldTextMode = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	COLORREF oldCol = pDC->SetTextColor(color);
	Rotate(pDC, -30, false);
	pDC->TextOutW(1, -5, strText); // pozicionirano u centru manjeg kruga


	pDC->SetBkMode(oldTextMode);
	pDC->SetTextAlign(oldTextAlign);
	pDC->SetTextColor(oldCol);
	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	pen.DeleteObject();
	pen2.DeleteObject();
	brush2.DeleteObject();
	brush.DeleteObject();
}
void CMy18012021View::SaveDC(CDC* pDC,CRect rcDC,CRect rcBmp) 
{
	int width = rcBmp.Width();
	int height = rcBmp.Height();
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rcDC.Width() / 2 - 100, rcDC.Height());
	memDC->SelectObject(&bmp);
	memDC->BitBlt(0, 0, width, height, pDC, 100 , 0 , SRCCOPY);
	DImage* picture = new DImage(bmp);
	picture->Save((CString)"Slika.bmp");
	delete picture;
	memDC->DeleteDC();
	delete memDC;
}
//Transformacije
void CMy18012021View::Translate(CDC* pDC,float dx,float dy,bool right)
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
void CMy18012021View::Rotate(CDC* pDC,float angle,bool right)
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
void CMy18012021View::TranslateRotate(CDC* pDC,float angle,float dx,float dy,float distance)
{
	XFORM form;
	form.eM11 = cos((angle * 3.14) / 180);
	form.eM12 = sin((angle * 3.14) / 180);
	form.eM21 = -sin((angle * 3.14) / 180);
	form.eM22 = cos((angle * 3.14) / 180);
	form.eDx = dx + (distance * cos((angle * 3.14) / 180));
	form.eDy = dy + (distance * sin((angle * 3.14) / 180));
	pDC->SetWorldTransform(&form);
}
#pragma region .....
BOOL CMy18012021View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy18012021View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy18012021View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CMy18012021View::AssertValid() const
{
	CView::AssertValid();
}
void CMy18012021View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy18012021Doc* CMy18012021View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy18012021Doc)));
	return (CMy18012021Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion