#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "25.03.2019.h"
#endif
#include "25.03.2019Doc.h"
#include "25.03.2019View.h"
#include "MipMap.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy25032019View, CView)

BEGIN_MESSAGE_MAP(CMy25032019View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CMy25032019View::CMy25032019View() noexcept
{
	img = new DImage();
	img->Load((CString)"tocak.png");
}
CMy25032019View::~CMy25032019View()
{
}
BOOL CMy25032019View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy25032019View::OnDraw(CDC* pDC)
{
	CMy25032019Doc* pDoc = GetDocument();
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

	XFORM form;
	int oldMode = memDC->SetGraphicsMode(GM_ADVANCED);
	memDC->GetWorldTransform(&form);
	//Crtanje tocka
	CMipMap* mipmap = new CMipMap((CString)"bg.jpg");
	DrawWP(memDC,50,35,15,300,10,150);
	//kraj crtanja tocka;
	//Rad sam mipmapom,ne moze oba lepo da rade
	//memDC = mipmap->DrawToDC(pDC, rect);
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
	delete mipmap;

}
//Funkcije za zadatak:
void CMy25032019View::DrawWheel(CDC* pDC,double r1,double r2,double w)
{
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(255,255,255));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(68,68,68));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	//da bismo nacrtali tocak,potrebno je koristiti putanju,da obojimo samo deo gde nije unutrasnji krug
	pDC->BeginPath();
	//veci krug
	pDC->Ellipse(-r1,-r1,r1,r1);
	//manji / unutrasnji
	pDC->Ellipse(-r2,-r2,r2,r2);

	pDC->EndPath();
	pDC->StrokeAndFillPath();
	pDC->SelectObject(&brush);

	CRect rect(-r2,-w/2,r2,w/2); // unutrasnji pravougaonik
	//posto na slici imamo 3 unutrasnja pravougaonika:
	float angle = 360 / 3; // delimo sa 3
	float tmpAngle = 90;
	// 3 puta se izvrti
	for (int i = 0; i < 3; i++)
	{
		XFORM form;
		pDC->GetWorldTransform(&form); // uzmemo sv. transformaciju
		// primenimo trasnformacije
		Rotate(pDC,tmpAngle,false);// rotira oko centra tocka
		pDC->Rectangle(rect);
		//nakon toga ih sacuvamo
		pDC->SetWorldTransform(&form); 
		//ugao pomerimo za angle
		tmpAngle += angle;
	}
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}
void CMy25032019View::DrawWP(CDC* pDC,double r1,double r2,double w,double L,double angle,double d)
{
	CRect rect;
	GetClientRect(&rect);
	//podesimo cime cemo crtati kosu ravan
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(255,255,255));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(68,68,68));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	float nagib = tan((angle * 3.14) / 180) * L;
	CPoint pts[3];
	
	pts[0] = CPoint(0,rect.Height());//donja leva tacka
	pts[1] = CPoint(L,rect.Height()); //pa za duzinu L udesno , donja desna tacka
	pts[2] = CPoint(0,rect.Height()-nagib);

	pDC->Polygon(pts,3);

	//racunamo poziciju centra tocka u odnosu na nagib i ugao
	float tmpNalegla = cos((angle * 3.14) / 180) * d;
	float tmpNaspramna = tan((angle * 3.14) / 180) * tmpNalegla;

	XFORM form;
	pDC->GetWorldTransform(&form);
	//rotira se i krug na osnovu distance
	float rotAngle = d / (2 * 3.14);
	Rotate(pDC, rotAngle, false);// u odnosu na cetar kruga
	//pozicioniramo tocak, i nacrtamo ga
	Translate(pDC, tmpNalegla, rect.Height() - nagib - r1 + tmpNaspramna, true);
	DrawWheel(pDC, r1, r2, w);

	pDC->SetWorldTransform(&form);
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}
//transformacije:
void CMy25032019View::Translate(CDC* pDC, float dx,float dy, bool right)
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
		pDC->ModifyWorldTransform(&form,MWT_LEFTMULTIPLY);
}
void CMy25032019View::Rotate(CDC* pDC, float angle, bool right)
{
	XFORM form;
	form.eM11 = cos(angle*3.14/180);
	form.eM12 = sin(angle * 3.14 / 180);
	form.eM21 = -sin(angle * 3.14 / 180);
	form.eM22 = cos(angle * 3.14 / 180);
	form.eDx = 0;
	form.eDy = 0;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
#pragma region ....
BOOL CMy25032019View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy25032019View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy25032019View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy25032019View::AssertValid() const
{
	CView::AssertValid();
}
void CMy25032019View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy25032019Doc* CMy25032019View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy25032019Doc)));
	return (CMy25032019Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion