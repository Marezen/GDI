#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "11.03.2012.h"
#endif
#include "11.03.2012Doc.h"
#include "11.03.2012View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CMy11032012View, CView)
BEGIN_MESSAGE_MAP(CMy11032012View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CMy11032012View::CMy11032012View() noexcept
{
	size = 100;
	CenterX = 100;
	CenterY = 100;
	img = new DImage();
}
CMy11032012View::~CMy11032012View()
{
}
BOOL CMy11032012View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion
void CMy11032012View::OnDraw(CDC* pDC)
{
	CMy11032012Doc* pDoc = GetDocument();
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

	CreateTriangleBmp((CString)"bg.jpg");
	//crtanje
	DrawRosete(memDC,CenterX,CenterY,100,8);
	//zavrseno crtanje
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}
//Funkcije
void CMy11032012View::DrawRosete(CDC* pDC,int x,int y,int size,int count)
{
	//prvo narandzasti krug .
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(150, 150, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	CBrush brushOrange;
	brushOrange.CreateSolidBrush(RGB(255,165,0));
	CBrush* oldBrushOrange = pDC->SelectObject(&brushOrange);

	pDC->Ellipse(x - size, y - size, x + size, y + size);
	//elipse koje predstavljaju latice:
	CBrush brushWhite;
	brushWhite.CreateSolidBrush(RGB(255, 252, 250));
	pDC->SelectObject(&brushWhite);
	int visinaElipsi = size / 3;
	float angle = 360 / count; // koliko latica /2
	float tmpAngle = 0;
	for (int i = 0; i < count; i++)
	{
		XFORM form;
		pDC->GetWorldTransform(&form);
		TranslateRotate(pDC,x,y,tmpAngle,size/2);
		pDC->Ellipse(-size/2,-visinaElipsi/2,size/2,visinaElipsi/2);
		pDC->SetWorldTransform(&form);
		tmpAngle += angle;
	}
	//i unutrasnja kruznica
	pDC->SelectObject(&brushOrange);
	pDC->Ellipse(x - visinaElipsi, y - visinaElipsi, x + visinaElipsi, y + visinaElipsi);

	pDC->SelectObject(oldBrushOrange);
	pDC->SelectObject(oldPen);
	//obavezno brisanje
	brushWhite.DeleteObject();
	brushOrange.DeleteObject();
	pen.DeleteObject();
}
void CMy11032012View::CreateTriangleBmp(CString fileName)
{
	img->Load(fileName);
	CRect rect;
	GetClientRect(&rect);
	CDC* pDC = GetDC();
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()); // preko celog prozorceta
	memDC->SelectObject(&bmp);
	//potrebno je napraviti trougao,koji ce da isece region

	CPoint pts[3];
	pts[0] = CPoint(0,rect.Height());
	pts[1] = CPoint(rect.Width()/2,0);
	pts[2] = CPoint(rect.Width(),rect.Height());

	//sada kreiramo region
	CRgn rgn;
	rgn.CreatePolygonRgn(pts, 3, GM_ADVANCED);
	pDC->SelectClipRgn(&rgn);

	img->Draw(pDC, CRect(0, 0, img->Width(), img->Height()), CRect(0, 0, rect.Width(), rect.Height()));

	pDC->SelectClipRgn(NULL);
	rgn.DeleteObject();

	memDC->BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);

	DImage img(bmp);
	img.Save((CString)"Output.bmp");

	memDC->DeleteDC();
	delete memDC;

}
//transformacije
void CMy11032012View::Rotate(CDC* pDC,float angle,bool right)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = 0;
	form.eDy = 0;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
void CMy11032012View::TranslateRotate(CDC* pDC,float x,float y,float angle,float distance)
{
	XFORM form;
	form.eM11 = cos((angle * 3.14) / 180);
	form.eM12 = sin((angle * 3.14) / 180);
	form.eM21 = -sin((angle * 3.14) / 180);
	form.eM22 = cos((angle * 3.14) / 180);
	form.eDx = x + (distance* cos((angle * 3.14) / 180));
	form.eDy = y + (distance * sin((angle * 3.14) / 180));
	pDC->SetWorldTransform(&form);
}
#pragma region ..
BOOL CMy11032012View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy11032012View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy11032012View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}
#ifdef _DEBUG
void CMy11032012View::AssertValid() const
{
	CView::AssertValid();
}
void CMy11032012View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy11032012Doc* CMy11032012View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy11032012Doc)));
	return (CMy11032012Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion