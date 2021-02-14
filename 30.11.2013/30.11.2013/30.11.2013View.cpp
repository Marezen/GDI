#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "30.11.2013.h"
#endif
#include "30.11.2013Doc.h"
#include "30.11.2013View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CMy30112013View, CView)

BEGIN_MESSAGE_MAP(CMy30112013View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()
CMy30112013View::CMy30112013View() noexcept
{
	stop = false;
	size = 60;
	move = 20.0;
	rotAngle = 0.0;
	centerX = 100;
	centerY = 200;

	sky = new DImage();
	sky->Load((CString)"sky.jpg");
	bark = new DImage();
	bark->Load((CString)"bark.jpg");
}
CMy30112013View::~CMy30112013View()
{}
BOOL CMy30112013View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion
void CMy30112013View::OnDraw(CDC* pDC)
{
	CMy30112013Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(bmp);

	int oldMode = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM form;
	memDC->GetWorldTransform(&form);

	//crtanje
	//prvo ucitamo pozadinu:
	sky->Draw(memDC, CRect(0, 0, sky->Width(), sky->Height()), CRect(0, 0, rect.Width(), rect.Height()));
	bark->Draw(memDC, CRect(0, 0, bark->Width(), bark->Height()), CRect(rect.Width() - bark->Width(), 0, rect.Width(), rect.Height()));

	Translate(memDC, centerX, centerY); // pozicioniraj na centar
	Rotate(memDC, rotAngle); // rotiraj za ugao koji dobijamo pritiskom na dugme
	DrawStar(memDC, size); // nakon toga nacrtaj zvezdu
	//kraj crtanja
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}
//Funkcije
void CMy30112013View::DrawStar(CDC* pDC,int size)
{
	float angle = 360 / 4;
	float tmpAngle = 0;
	for (int i = 0; i < 4; i++)
	{
		Rotate(pDC,tmpAngle);
		DrawBlade(pDC,size/2);
		tmpAngle += angle;
	}
}
void CMy30112013View::DrawBlade(CDC* pDC, int size)
{
	CPen pen(PS_SOLID, 1, RGB(68, 68, 68));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush tamno, svetlo;
	tamno.CreateSolidBrush(RGB(128, 128, 128));
	svetlo.CreateSolidBrush(RGB(180, 180, 180));
	CBrush* oldBrush = pDC->SelectObject(&svetlo);

	//Svetli deo prvo:
	CPoint Pts[4];
	Pts[0] = CPoint(0,0);
	Pts[1] = CPoint(4*size,0);
	Pts[2] = CPoint(size, size);
	Pts[3] = CPoint(0, 0);
	pDC->Polygon(Pts, 4);
	//sada tamni deo:
	pDC->SelectObject(&tamno);
	Pts[0] = CPoint(0, 0);
	Pts[1] = CPoint(4 * size, 0);
	Pts[2] = CPoint(size, -size);
	Pts[3] = CPoint(0, 0);
	pDC->Polygon(Pts, 4);
	//nakon crtanja brisemo
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	tamno.DeleteObject();
	svetlo.DeleteObject();
	pen.DeleteObject();
	//Sada text:
	CFont font;
	font.CreateFont(0.7 * size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Monotype Corsiva");
	CFont* oldFont = pDC->SelectObject(&font);

	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	int oldAlign = pDC->SetTextAlign(TA_CENTER);
	COLORREF col = pDC->SetTextColor(RGB(255, 255, 255)); //prvo "Bela senka"
	pDC->TextOut(2 * size, -0.35 * size, (CString)"Shuricane");
	//pa preko nje se nacrta crno,maloo pomereno u stranu
	pDC->SetTextColor(RGB(20, 20, 20));
	pDC->TextOut(2 * size - 3, -0.34 * size+1, (CString)"Shuricane");

	pDC->SetBkMode(oldBkMode);
	pDC->SetTextAlign(oldAlign);
	pDC->SetTextColor(col);
	pDC->SelectObject(oldFont);
	font.DeleteObject();
}
//Transformacije
void CMy30112013View::Translate(CDC* pDC, float x, float y)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = x;
	form.eDy = y;
	pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
void CMy30112013View::Rotate(CDC* pDC,float angle)
{
	XFORM form;
	form.eM11 = cos((angle * 3.14) / 180);
	form.eM12 = sin((angle * 3.14) / 180);
	form.eM21 = -sin((angle * 3.14) / 180);
	form.eM22 = cos((angle * 3.14) / 180);
	form.eDx = 0;
	form.eDy = 0;
	pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
//AntiFlicker - tasteri:
void CMy30112013View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CRect rect;
	GetClientRect(&rect);
	if (stop==false && nChar == 'W') // ako jos nije udario u drvo
	{
		centerX += move;
		rotAngle += 10;
		if ((centerX + (2 * size)) - (rect.Width() - bark->Width()) >= ((2 * size) * 0.1)) //ako je udario u drvo,prestane
		{
			stop = true;
		}
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
BOOL CMy30112013View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
#pragma region ..
BOOL CMy30112013View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy30112013View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}
void CMy30112013View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}
#ifdef _DEBUG
void CMy30112013View::AssertValid() const
{
	CView::AssertValid();
}
void CMy30112013View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy30112013Doc* CMy30112013View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy30112013Doc)));
	return (CMy30112013Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion