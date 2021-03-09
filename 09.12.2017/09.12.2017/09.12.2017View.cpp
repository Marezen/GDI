#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "09.12.2017.h"
#endif
#include "09.12.2017Doc.h"
#include "09.12.2017View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy09122017View, CView)

BEGIN_MESSAGE_MAP(CMy09122017View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()
#
CMy09122017View::CMy09122017View() noexcept
{
	body = new DImage();
	leg1 = new DImage();
	leg2 = new DImage();
	leg3 = new DImage();
	back = new DImage();
	body->Load((CString)"Body.png");
	leg1->Load((CString)"Leg1.png");
	leg2->Load((CString)"Leg2.png");
	leg3->Load((CString)"Leg3.png");
	back->Load((CString)"Back2.jpg");
	bodyX = 100;
	bodyY = 100;
	y1 = 0;
	x1 = 0;
	x2 = back-> Width() / 2;
	y2 = back->Height() / 2;
	//rotacije za koracanje
	frontRight = -10;
	frontLeft = 20;
	backLeft = 20;
	backRight = -10;
	Step = 0;
}
CMy09122017View::~CMy09122017View()
{
	delete body;
	delete leg1;
	delete leg2;
	delete leg3;
	delete back;
}
BOOL CMy09122017View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion
void CMy09122017View::OnDraw(CDC* pDC)
{
	CMy09122017Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(width, height);
	CRect rect;
	GetClientRect(&rect);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(0, 0);
	pDC->OffsetViewportOrg(0, 0);
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	//sad isto kao gore
	memDC->SetMapMode(MM_ANISOTROPIC);
	memDC->SetWindowExt(width, height);
	memDC->SetViewportExt(rect.right, rect.bottom);
	memDC->SetWindowOrg(0, 0);
	memDC->OffsetViewportOrg(0, 0);
	memDC->SetGraphicsMode(GM_ADVANCED);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(&bmp);
	//crtanje scene:
	DrawScene(memDC, CRect(0, 0, width, height));
	//kraj crtanja



	pDC->BitBlt(0, 0, width, height, memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;

}
//Funkcije za zadatak
void CMy09122017View::DrawScene(CDC* pDC,CRect rect)
{
	back->Draw(pDC, CRect(x1, y1, x2, y2), rect);
	//pre ucitavanja,potrebno odraditi Scale
	XFORM form;
	if (povecaj || smanji)
	{
		GetWorldTransform(pDC->m_hDC, &form);
		if (povecaj)
			Scale(pDC, 1.1, 1.1, true);
		else
			Scale(pDC, 0.9, 0.9, true);
	}
	//ucitamo telo transportera:
	body->DrawTransparent(pDC, CRect(0, 0, body->Width(), body->Height()), CRect(bodyX, bodyY, bodyX + body->Width(), bodyY + body->Height()));
	DrawLeg(pDC, frontRight, 270, 168); // prednja desna
	DrawLeg(pDC, frontLeft, 270, 168); // prednja leva
	DrawLeg(pDC, backLeft, 65, 170); // zadnja leva
	DrawLeg(pDC, backRight, 65, 170); // zadnja desna , cisto reda radi
	if (povecaj || smanji)
	{
		SetWorldTransform(pDC->m_hDC, &form);
	}
}
//dx,dy - za slucaj pritiska tastera pa da se vrsi pomeranje
//angle - takodje za ugao ,prilikom pritiska na taster
void CMy09122017View::DrawLeg(CDC* pDC,double angle,double dx,double dy)
{
	XFORM form;
	GetWorldTransform(pDC->m_hDC, &form);

	Translate(pDC,dx + bodyX + 21,dy + bodyY +20,false);
	Rotate(pDC,angle,false);
	//butina
	leg1->DrawTransparent(pDC, CRect(0, 0, leg1->Width(), leg1->Height()), CRect(-28, -28, -28 + leg1->Width(), -28 + leg1->Height()));
	SetWorldTransform(pDC->m_hDC, &form);
	int distance = leg1->Height() - 50;
	//drugi deo noge,list
	float xLeg2 = dx + bodyX - sin((angle*3.14)/180)*distance;
	float yLeg2 = dy + bodyY + cos((angle * 3.14) / 180) * distance;
	leg2->DrawTransparent(pDC, CRect(0, 0, leg2->Width(), leg2->Height()), CRect(xLeg2, yLeg2, xLeg2 + leg2->Width(), yLeg2 + leg2->Height()));
	//stopalo
	float xLeg3 = xLeg2 + leg2->Width() / 2 - leg3->Width() / 2;
	float yLeg3 = yLeg2 + leg2->Height();
	leg3->DrawTransparent(pDC, CRect(0, 0, leg3->Width(), leg3->Height()), CRect(xLeg3, yLeg3, xLeg3 + leg3->Width(), yLeg3 + leg3->Height()));
}
//Transformacije
void CMy09122017View::Translate(CDC* pDC,float dX,float dY,bool right)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = dX;
	form.eDy = dY;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
void CMy09122017View::Rotate(CDC* pDC,float angle,bool right)
{
	XFORM form;
	form.eM11 = cos((angle*3.14)/180);
	form.eM12 = sin((angle*3.14)/180);
	form.eM21 = -sin((angle*3.14)/180);
	form.eM22 = cos((angle*3.14)/180);
	form.eDx = 0;
	form.eDy = 0;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
void CMy09122017View::Scale(CDC* pDC,float sX,float sY,bool right)
{
	XFORM form;
	form.eM11 = sX;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = sY;
	form.eDx = 0;
	form.eDy = 0;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
void CMy09122017View::LoadIdentity(CDC* pDC)
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
//Antiflicker - Buttons:
BOOL CMy09122017View::OnEraseBkgnd(CDC* pDC)
{
	return true;
}
void CMy09122017View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//buttons sa pomeranje celog transportera na slici
	if (nChar == 'S')
	{
		if (y2 + 200 <= back->Height())
		{
			y1 += 200;
			y2 += 200;
		}
		Invalidate();
	}
	else if (nChar == 'A')
		{
			if (x1 - 200 >= 0)
			{
				x1 -= 200;
				x2 -= 200;
			}
			Invalidate();
		}
	else if(nChar == 'D')
	{
		if (x2 +200 <= back->Width())
		{
			x1 += 200;
			x2 += 200;
		}
		Invalidate();
	}
	else if (nChar == 'W')
	{
		if (y1 - 200 >=0)
		{
			y1 -= 200;
			y2 -= 200;
		}
		Invalidate();
	}
	//Scale,uvecanje ili umanjenje:
	if (nChar == VK_UP)
	{
		povecaj = true;
		smanji = false;
		Invalidate();
	}
	else
		if (nChar == VK_DOWN)
		{
			smanji = true;
			povecaj = false;
			Invalidate();
		}
	//rotacija
	if (nChar == VK_RIGHT)
	{
		if (Step!=3)
		{
			frontRight += 10;
			frontLeft -= 10;
			backLeft -= 10;
			backRight += 10;
			Step++;
		}
		else if (Step == 3)
		{
			Step = 0;
			frontRight = -10;
			frontLeft = 20;
			backLeft = 20;
			backRight = -10;
		}
		bodyX += 20;

		Invalidate();
	}
	//dodato za unazad,ali nije najbolje..
	if (nChar == VK_LEFT)
	{
		if (Step != 0)
		{
			frontRight -= 10;
			frontLeft += 10;
			backLeft += 10;
			backRight -= 10;
			Step--;
		}
		//ovo nije dobro odradjeno samo..
		else if (Step == 0)
		{
			Step = 3;
			frontRight = 20;
			frontLeft = -10;
			backLeft = -10;
			backRight = 20;
		}
		bodyX -= 20;

		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
#pragma region ...
BOOL CMy09122017View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy09122017View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy09122017View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy09122017View::AssertValid() const
{
	CView::AssertValid();
}
void CMy09122017View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy09122017Doc* CMy09122017View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy09122017Doc)));
	return (CMy09122017Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion