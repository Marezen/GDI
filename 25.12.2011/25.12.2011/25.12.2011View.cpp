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
	pDC->SetWindowExt(rect.right, rect.bottom);
	pDC->SetViewportExt(rect.right, rect.bottom);

	Translate(pDC, rect.CenterPoint().x, rect.CenterPoint().y);
	CreateGradientBitmap(pDC, rect.Width(), rect.Height(), RGB(255, 255, 255), RGB(0, 0, 0));

}
//Funkcije za zadatak
void CMy25122011View::CreateGradientBitmap(CDC* pDC, double w, double h, COLORREF col1, COLORREF col2)
{
	int w1 = (int)w;
	int h1 = (int)h;
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, w, h);
	DImage im(bmp);
	byte* bytes = im.GetDIBBits();

	byte B1 = col1;
	col1 = col1 >> 8;
	byte G1 = col1;
	col1 = col1 >> 8;
	byte R1 = col1;

	byte B2 = col2;
	col2 = col2 >> 8;
	byte G2 = col2;
	col2 = col2 >> 8;
	byte R2 = col2;

	int j = 0;
	double rmax = sqrt(pow(0 - w / 2.0, 2.0) + pow(0 - h / 2.0, 2.0));
	double rtr, intc1, intc2;
	for (int i = 0; i < im.Width() * im.Height() * im.BPP(); i = i + im.BPP())
	{
		int column = (i % (im.Width() * im.BPP())) / 4;

		rtr = sqrt(pow((double)(column - w / 2.0), 2.0) + pow((double)(j - h / 2.0), 2.0));
		intc2 = rtr / rmax;
		intc1 = 1 - intc2;

		int R = ((int)((int)R1 * intc1 + (int)R2 * intc2));
		int G = ((int)((int)G1 * intc1 + (int)G2 * intc2));
		int B = ((int)((int)B1 * intc1 + (int)B2 * intc2));

		bytes[i] = (byte)R;
		bytes[i + 1] = (byte)G;
		bytes[i + 2] = (byte)B;

		im.Update();
		if (column == 0 && i != 0)
			j++;
	}
	im.Draw(pDC, CRect(0, 0, w1, h1), CRect(0, 0, w1, h1));
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