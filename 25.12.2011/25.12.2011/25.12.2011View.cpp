#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "25.12.2011.h"
#endif
#include "25.12.2011Doc.h"
#include "25.12.2011View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy25122011View, CView)
BEGIN_MESSAGE_MAP(CMy25122011View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()


CMy25122011View::CMy25122011View() noexcept
{

}
CMy25122011View::~CMy25122011View()
{
}

BOOL CMy25122011View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy25122011View::OnDraw(CDC* pDC)
{
	CMy25122011Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);

	CDC* memDC = this->createGradientBitmap(pDC, 500, 500, RGB(255, 255, 255), RGB(0, 0, 0));
	//ako hocemo da prikazemo rectangle slike onda ide ovo:
	//pDC->SetStretchBltMode(HALFTONE);
	//pDC->StretchBlt(100, 100, 200, 200, memDC, 0, 0, w, h, SRCCOPY);
	//a da prikazemo zvezdu:
	this->drawStar(pDC, memDC, 500, 500, 8, 150, 50, rect.Width()/2, rect.Height()/2);

	delete memDC;
}
//Funkcije za zadatak
CDC* CMy25122011View::createGradientBitmap(CDC* pDC, double w, double h, COLORREF col1, COLORREF col2)
{
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateBitmap(w,h,1,32,NULL); //kreiramo bitmapu
	memDC->SelectObject(&bmp);
	CPen pen;
	pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	CPen* oldPen = memDC->SelectObject(&pen);

	CBrush brush;
	CBrush* oldBrush = memDC->SelectObject(&brush);

	BYTE r1 = ((int)col1 & 0x000000FF);
	BYTE g1 = ((int)col1 & 0x0000FF00) >> 8;
	BYTE b1 = ((int)col1 & 0x00FF0000) >> 16;

	BYTE r2 = ((int)col2 & 0x000000FF);
	BYTE g2 = ((int)col2 & 0x0000FF00) >> 8;
	BYTE b2 = ((int)col2 & 0x00FF0000) >> 16;
	BYTE ri, gi, bi;
	int n = w * sqrt(2.0) / 2;
	int x0 = w / 2;

	//////////////////////////////////////////////////////////////////////////////////

	int prevMode = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM newT, oldT;
	memDC->GetWorldTransform(&oldT);

	newT.eM11 = 1;
	newT.eM12 = 0;
	newT.eM21 = 0;
	newT.eM22 = h / w;
	newT.eDx = 0;
	newT.eDy = 0;

	memDC->SetWorldTransform(&newT);
	for (int i = n; i >= 0; i--)
	{
		ri = r1 + i * (r2 - r1) / n;
		gi = g1 + i * (g2 - g1) / n;
		bi = b1 + i * (b2 - b1) / n;

		//za svaki piksel  kreiramo brush 
		brush.DeleteObject();
		brush.CreateSolidBrush(RGB(ri, gi, bi));
		memDC->SelectObject(&brush);

		memDC->Ellipse(x0 - i - 1, x0 - i - 1, x0 + i + 1, x0 + i + 1);
	}
	memDC->SetWorldTransform(&oldT);
	memDC->SetGraphicsMode(prevMode);

	pen.DeleteObject();
	brush.DeleteObject();
	bmp.DeleteObject();
	memDC->SelectObject(&oldPen);
	memDC->SelectObject(&oldBrush);
	return memDC;
}

void CMy25122011View::drawStar(CDC* pDC, CDC* bmpDC, int wBmp, int hBmp, int N, int R1, int R2, int Xc, int Yc)
{
	CPoint* points = new CPoint[2 * N]; //N kraka(najdalje tacke) i + jos N tacaka koje su one blize
	double pi = acos(-1.0);
	for (int i =0 ;i<N; i++)
	{
		points[2 * i].x = Xc - R1 * sin(2*pi*i/N);
		points[2 * i].y = Yc - R1 * cos(2 * pi * i / N);

		points[2 * i + 1].x = Xc - R2 * sin(2 * pi * i / N + pi / N);
		points[2 * i + 1].y = Yc - R2 * cos(2 * pi * i / N + pi / N);
	}
	//nakon sto podesimo sve tacke neophodne za crtanje zvezde
	//treba napraviti region koji ce prikazati samo deo slike koji je obuhvacen poligonom
	CRgn clipRegion;
	clipRegion.CreatePolygonRgn(points, N * 2, WINDING);
	pDC->SelectClipRgn(&clipRegion);

	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(Xc-R1,Yc-R1,2*R1,2*R1,bmpDC,0,0,wBmp,hBmp,SRCCOPY);
	delete points;
	clipRegion.DeleteObject();


}

void CMy25122011View::Translate(CDC* pDC,float dX,float dY)
{
	XFORM form;
	form.eM11 = 1.0;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1.0;
	form.eDx = dX;
	form.eDy = dY;
	pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
}
#pragma region ....
BOOL CMy25122011View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy25122011View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy25122011View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy25122011View::AssertValid() const
{
	CView::AssertValid();
}
void CMy25122011View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy25122011Doc* CMy25122011View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy25122011Doc)));
	return (CMy25122011Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion