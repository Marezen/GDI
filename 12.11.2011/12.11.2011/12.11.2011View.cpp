#pragma region fiksno
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "12.11.2011.h"
#endif
#include "12.11.2011Doc.h"
#include "12.11.2011View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CMy12112011View, CView)
BEGIN_MESSAGE_MAP(CMy12112011View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()
CMy12112011View::CMy12112011View() noexcept
{
}
CMy12112011View::~CMy12112011View()
{
}
BOOL CMy12112011View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy12112011View::OnDraw(CDC* pDC)
{
	CMy12112011Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//podesimo antiflicker i poseban memDC na kome ce da se iscrta slika

	CRect rect;
	GetClientRect(&rect);

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(&bmp);
	//za transformacije

	int oldMode = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM form;
	memDC->GetWorldTransform(&form);

	////////////////  Crtanje scene ////////////

	XFORM transForm = Translate(300,300); // odredjivanje centra

	//GORE LEVO
	XFORM rotForm1 = Rotate(180);
	XFORM tmpForm1;
	CombineTransform(&tmpForm1,&rotForm1,&transForm);
	memDC->SetWorldTransform(&tmpForm1);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);

	//Dole Levo
	XFORM rotForm2 = Rotate(90);
	XFORM tmpForm2;
	CombineTransform(&tmpForm2,&rotForm2,&transForm);
	memDC->SetWorldTransform(&tmpForm2);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);

	//preostala 2 dela moraju da imaju Reflect transformaciju

	//DOLE DESNO
	XFORM rotForm3 = Rotate(90);
	XFORM reflectForm3 = Reflect(-1,1);
	XFORM tmpForm3;
	XFORM FormFinal1;
	CombineTransform(&tmpForm3, &rotForm3, &reflectForm3); // prvo rotacija i reflect se kombinuju
	CombineTransform(&FormFinal1,&tmpForm3,&transForm);
	memDC->SetWorldTransform(&FormFinal1);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);

	//GORE DESNO
	XFORM rotForm4 = Rotate(180);
	XFORM reflectForm4 = Reflect(-1, 1);
	XFORM tmpForm4;
	XFORM FormFinal2;
	CombineTransform(&tmpForm4, &rotForm4, &reflectForm4); // prvo rotacija i reflect se kombinuju
	CombineTransform(&FormFinal2, &tmpForm4, &transForm);
	memDC->SetWorldTransform(&FormFinal2);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);




	////////////////  Kraj crtanja scene ///////////
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),memDC,0,0, SRCCOPY);

	Save();

	memDC->DeleteDC();
	delete memDC;

}


//FUNKCIJE:

XFORM CMy12112011View::Translate(float x,float y)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = x;
	form.eDy = y;
	return form;
}
XFORM CMy12112011View::Rotate(float a)
{
	XFORM form;
	form.eM11 = cos((a * 3.14) / 180); // pretvaramo u radijane
	form.eM12 = sin((a * 3.14) / 180);
	form.eM21 = -sin((a * 3.14) / 180);
	form.eM22 = cos((a * 3.14) / 180);
	form.eDx = 0;
	form.eDy = 0;
	return form;
}
XFORM CMy12112011View::Reflect(float Sx,float Sy)
{
	XFORM form;
	form.eM11 = Sx;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = Sy;
	form.eDx = 0;
	form.eDy = 0;
	return form;

}
void CMy12112011View::DrawTriangle(CDC* pDC)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(78,78,78));
	CBrush* oldBrush = pDC->SelectObject(&brush);
	CPen cpen(PS_SOLID,2,RGB(80,250,100));
	CPen* oldPen = pDC->SelectObject(&cpen);

	CPoint Pt[3];
	Pt[0] = CPoint(0, 0);
	Pt[1] = CPoint(100, 0);
	Pt[2] = CPoint(0, 200);
	pDC->Polygon(Pt,3);

	//obavezno brisanje
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	cpen.DeleteObject();
	brush.DeleteObject();

}
void CMy12112011View::Save()
{
	int width = 400;
	int height = 300;

	CDC* pDC = GetDC(); // uzme dc u kome je crtano
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, width, height);
	memDC->SelectObject(&bmp);

	memDC->BitBlt(0, 0, width, height, pDC, 100, 100, SRCCOPY);

	DImage img(bmp);
	img.Save((CString)"fig.bmp");

	memDC->DeleteDC();
	delete memDC;
}

#pragma region ..
BOOL CMy12112011View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy12112011View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy12112011View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy12112011View diagnostics

#ifdef _DEBUG
void CMy12112011View::AssertValid() const
{
	CView::AssertValid();
}

void CMy12112011View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy12112011Doc* CMy12112011View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy12112011Doc)));
	return (CMy12112011Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy12112011View message handlers
#pragma endregion