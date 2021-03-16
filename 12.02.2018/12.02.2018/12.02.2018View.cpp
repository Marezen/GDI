#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "12.02.2018.h"
#endif
#include "12.02.2018Doc.h"
#include "12.02.2018View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy12022018View, CView)

BEGIN_MESSAGE_MAP(CMy12022018View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CMy12022018View::CMy12022018View() noexcept
{
}
CMy12022018View::~CMy12022018View()
{
}
BOOL CMy12022018View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy12022018View::OnDraw(CDC* pDC)
{
	CMy12022018Doc* pDoc = GetDocument();
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
	// pod A)
	LoadIdentity(memDC);
	Translate(memDC, 200, 100, true);
	DrawTop(memDC, 25);
	//pod F)

	LoadIdentity(memDC);
	DrawTop2(memDC,20);

	// pod G)
	//Prva slika , 0 stepeni
	LoadIdentity(memDC);
	Translate(memDC,50,250,true);
	DrawTail(memDC,10,5,0);
	//Druga slika, za 20 stepeni
	LoadIdentity(memDC);
	Translate(memDC, 300, 300, true);
	DrawTail(memDC, 10, 5,20);

	//treca slika,za 45 stepeni
	/*LoadIdentity(memDC);
	Translate(memDC, 600, 350, true);
	DrawTail(memDC, 10, 5, 45);*/
	

	//kraj crtanja
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;

}
//Funkcije za zadatak:
void CMy12022018View::DrawTop(CDC* pDC,int size)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,0,255));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	CPen* oldPen = pDC->SelectObject(&pen);

	//Ne ispuni se lepo...,trebalo bi odraditi uz pomoc putanja 
	//pDC->BeginPath();
	pDC->SetArcDirection(AD_CLOCKWISE);
	
	//najveci
	pDC->Arc(-size, -size, size, size, 0, size / 2, size, 0);
	//desni
	pDC->Arc(-size, -2 * size, size, 2 * size, size, 0, 0, size * 2);
	//manji
	pDC->Arc(-size / 2, size, size / 2, 2 * size, 0, size, 0, 2 * size);

	//pDC->EndPath();
	//pDC->FillPath()
	;
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}
void CMy12022018View::DrawTop2(CDC* pDC, int size)
{
	Rotate(pDC, -90, true);
	Mirror(pDC,true,true);
	DrawTop(pDC,size);
}
void CMy12022018View::DrawTail(CDC* pDC, int size, int count, double alfa)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(210, 210, 210));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	int pozicija = 0;
	int y = 0;
	int repX, repY;
	for (int i = 0; i < count; i++)
	{
		pDC->Ellipse(-size*2,-size,2*size,size);
		pozicija += size*4 ;
		//TranslateRotate(pDC,alfa,pozicija,y,size);
		Translate(pDC, size*4,y, true);
		Rotate(pDC,-alfa,false);
		Translate(pDC, 0,0,true);
	}
	DrawTop2(pDC,size*1.5);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}
//transformacije:
void CMy12022018View::LoadIdentity(CDC* pDC)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = 0;
	form.eDy = 0;
	pDC->SetWorldTransform(&form);
}
void CMy12022018View::Translate(CDC* pDC, double dx, double dy, bool right)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = dx;
	form.eDy = dy;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
void CMy12022018View::Rotate(CDC* pDC, double angle, bool right)
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
void CMy12022018View::Mirror(CDC* pDC,bool x,bool right)
{
	XFORM form;
	form.eM11 = x;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = -x;
	form.eDx = 0.0;
	form.eDy = 0.0;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
void CMy12022018View::TranslateRotate(CDC* pDC, float angle, float dx, float dy, float distance)
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
#pragma region ...
BOOL CMy12022018View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy12022018View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy12022018View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy12022018View::AssertValid() const
{
	CView::AssertValid();
}
void CMy12022018View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy12022018Doc* CMy12022018View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy12022018Doc)));
	return (CMy12022018Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion