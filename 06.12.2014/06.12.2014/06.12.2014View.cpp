#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "06.12.2014.h"
#endif
#include "06.12.2014Doc.h"
#include "06.12.2014View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CMy06122014View, CView)

BEGIN_MESSAGE_MAP(CMy06122014View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CMy06122014View::CMy06122014View() noexcept
{
	carCenterX = 0;
	carCenterY = 0;
	carW = 450;
	carH =   carW/2.5;
	wheelSize = 38;
	moveAngle = 0;
	angleGround = 10;
	move = 0;
	clio = GetEnhMetaFile((CString)"clio.emf");
	wheel = new DImage();
	wheel->Load((CString)"Wheel.png");
}
CMy06122014View::~CMy06122014View()
{
	DeleteEnhMetaFile(clio);
	delete wheel;
}
BOOL CMy06122014View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy06122014View::OnDraw(CDC* pDC)
{
	CMy06122014Doc* pDoc = GetDocument();
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
	//crtanje scene
	DrawGround(memDC, angleGround);
	carCenterX += move; // pomeranje centra automobila
	Translate(memDC, carW / 2, -carH / 2, true); // ovo +4 da bi vrh tocka bio tacno na liniji
	Rotate(memDC, -angleGround, true); // mora minus
	Translate(memDC, 0, rect.Height(), true); // da rotira oko tacke (0,rect.Height()) -- Dole levo
	DrawCar(memDC, carCenterX, carCenterY, carW, carH);
	float rotAngle = ((moveAngle / (3.14 * 2)) * 3.14) / 180;

	DrawWheel(memDC, carCenterX - 155, carCenterY + 70, wheelSize, rotAngle);
	DrawWheel(memDC, carCenterX + 135, carCenterY + 70, wheelSize, rotAngle);
	//kraj crtanja

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;
}
//Funkcije za zadatak
void CMy06122014View::DrawGround(CDC* pDC, float angle)
{
	CRect rect;
	GetClientRect(&rect);

	CPen pen(PS_SOLID, 3, RGB(60, 30, 40));
	CPen* oldPen = pDC->SelectObject(&pen);
	CBrush nebo, podloga;
	nebo.CreateSolidBrush(RGB(0, 120, 200));
	podloga.CreateHatchBrush(HS_FDIAGONAL, RGB(0, 128, 128));
	CBrush* oldBrush = pDC->SelectObject(&nebo);
	//nebo:
	pDC->Rectangle(rect); // preko celog

	//potrebno je izracunati uspon
	float nasp;
	float nal = rect.Width();
	nasp = (angle * 3.14 / 180) * nal;
	//uzimamo Brush za podlogu
	pDC->SelectObject(&podloga);
	CPoint pts[4];
	pts[0] = CPoint(0, rect.Height()); //dole levo
	pts[1] = CPoint(rect.Width(), rect.Height() - nasp);
	pts[2] = CPoint(rect.Width(),rect.Height());
	pts[3] = CPoint(0,rect.Height());
	pDC->Polygon(pts, 4);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();


}
void CMy06122014View::DrawCar(CDC* pDC, int x, int y, int w, int h)
{
	//(x - w / 2, y - h / 2, x + w / 2, y + h / 2) // da bude okrenut na levo
	CRect invertBounds(x + w / 2, y - h / 2, x - w / 2, y + h / 2);
	pDC->PlayMetaFile(clio, invertBounds);
}
void CMy06122014View::DrawWheel(CDC* pDC, int x, int y, int r, float angle)
{
	XFORM form;
	pDC->GetWorldTransform(&form);
	Translate(pDC, x, y, false);
	Rotate(pDC, angle, false);
	// (52,15) // gornji levi okvirni ugao
	wheel->Draw(pDC, CRect(52, 15, 52 + 376, 15 + 376), CRect(-r, -r, r, r));
	//nemam funkciju DrawTransparent,zato ima pozadina..
	pDC->SetWorldTransform(&form);
}

//transformacije
void CMy06122014View::Translate(CDC* pDC,float x,float y,bool right)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = x;
	form.eDy = y;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
void CMy06122014View::Rotate(CDC* pDC,float angle,bool right)
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
void CMy06122014View::Scale(CDC* pDC, float Sx, float Sy, bool right)
{
	XFORM form;
	form.eM11 = Sx;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = Sy;
	form.eDx = 0;
	form.eDy = 0;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

//Antiflicker i Buttons;
BOOL CMy06122014View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
void CMy06122014View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//Lose pomeranje
	if (nChar == VK_RIGHT && move<= 100) {
		move += 10;
		moveAngle += 10;
		Invalidate();
	}
	else if (nChar == VK_LEFT && move >= 0) {
		move -= 10;
		moveAngle -= 10;
		Invalidate();
	}
	else if (nChar == VK_UP && angleGround < 80) {
		angleGround += 10;
		Invalidate();
	}
	else if (nChar == VK_DOWN && angleGround > 10) {
		angleGround -= 10;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
#pragma region ..
BOOL CMy06122014View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy06122014View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy06122014View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy06122014View::AssertValid() const
{
	CView::AssertValid();
}
void CMy06122014View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy06122014Doc* CMy06122014View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy06122014Doc)));
	return (CMy06122014Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion