#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "24.06.2019.h"
#endif
#include "24.06.2019Doc.h"
#include "24.06.2019View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy24062019View, CView)

BEGIN_MESSAGE_MAP(CMy24062019View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

CMy24062019View::CMy24062019View() noexcept
{
	x = 50;
	y = 50;
}
CMy24062019View::~CMy24062019View()
{
}
BOOL CMy24062019View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy24062019View::OnDraw(CDC* pDC)
{
	CMy24062019Doc* pDoc = GetDocument();
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
	GetCursorPos(&point);
	ScreenToClient(&point);
	//kraj crtanja
	DrawRoundedText(memDC,CRect(0,0,200,100),5,RGB(212,212,212),RGB(255,0,0),(CString)"Strelica",RGB(0,0,0),point,10,4,(CString)"text",RGB(255,255,255),RGB(0,10,10));

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;

}
//funkcije za zadatak
void CMy24062019View::DrawRoundedText(CDC* pDC, CRect rcText, double perc, COLORREF colFillRect, COLORREF colLineRect, CString Text, COLORREF colText, CPoint ptMouse, double r, int n, CString strParts, COLORREF colFillArrow, COLORREF colLIneArrow)
{
	bool unutar = false; // za proveru da l ije pokazivac unutar zaobljenog pravougaonika

	//cime crtamo pravougaonik
	CPen pen;
	pen.CreatePen(PS_SOLID,3,colLineRect);
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(colFillRect);
	CBrush* oldBrush = pDC->SelectObject(&brush);
	Translate(pDC,300,200,true);

	//Neuspesno ucitavanje koordinata misa....
	CRgn rgn;
	rgn.CreateRoundRectRgn(-rcText.Width(), -rcText.Height(), rcText.Width(), rcText.Height(), 4 * r, 4 * r);
	if (rgn.PtInRegion(ptMouse))
	{
		unutar = true;
	}
	pDC->RoundRect(-rcText.Width(),-rcText.Height(),rcText.Width(),rcText.Height(),4*r,4*r);

	//Napravimo region gde cemo ispitati koordinate pokazivaca

	//ispis teksta
	CFont font;
	font.CreateFont(50, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont* oldFont = pDC->SelectObject(&font);
	int oldTextMode = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	COLORREF oldCol = pDC->SetTextColor(colText);
	pDC->TextOutW(-10, 0, Text);

	//ovde treba da se ispita,da li se nalazi unutar 

	//ako je true,onda nacrta,ako ne,onda nece
	if (unutar)
	{
		//desna strelica
		Translate(pDC, rcText.Width() + 2 * r, -rcText.Height() / 2, true);
		DrawArrow(pDC, 10, 4, (CString)"Neki Tekst", RGB(255, 255, 0), RGB(255, 255, 255), 0);

		/*  Posto je rotacija strelice neuspesna,zakomentarisao sam
		*
		//donja strelica
		Translate(pDC, -rcText.Width()*1.5, +rcText.Height()+r, true);
		DrawArrow(pDC, 10, 4, (CString)"Neki Tekst", RGB(255, 255, 0), RGB(255, 255, 255), 90);

		//leva strelica
		Translate(pDC, -rcText.Width() * 2+r, -rcText.Height() - 2*r, true);
		DrawArrow(pDC, 10, 4, (CString)"Neki Tekst", RGB(255, 255, 0), RGB(255, 255, 255), 180);

		//gornja
		Translate(pDC, +rcText.Width()/2-6*r, -rcText.Height()*2-3*r, true);
		DrawArrow(pDC, 10, 4, (CString)"Neki Tekst", RGB(255, 255, 0), RGB(255, 255, 255), -90);
		*/
	}

	//oslobadjanje
	pDC->SetBkMode(oldTextMode);
	pDC->SetTextAlign(oldTextAlign);
	pDC->SetTextColor(oldCol);
	pDC->SelectObject(oldFont);
	pDC->SelectObject(&oldPen);
	pDC->SelectObject(&oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}
void CMy24062019View::DrawArrow(CDC* pDC, double r, int n, CString strParts, COLORREF colFill, COLORREF colLine, float angle)
{
	CPen pen;
	pen.CreatePen(PS_SOLID,1,colLine);
	CPen* oldPen = pDC->SelectObject(&pen);

	//n kolona , 
	int razmakKolona = 3 * r;
	int razmakRedova = 3 * r;
	CBrush brush;
	brush.CreateSolidBrush(colFill);
	CBrush* oldBrush = pDC->SelectObject(&brush);

	pDC->BeginPath();
	int pom = n; // broj elipsa koje se crtaju u koloni
	int pozic = 0;
	int oldPoz; // pozicija poslednje nacrtane elipse u koloni
	while (pom>0)
	{
		for (int i = 0; i < pom; i++)
		{
			pDC->Ellipse(-r, -r, r, r);
			Translate(pDC,  0, razmakRedova-sin(angle*3.14/180), true);
			pozic += razmakRedova;
		}
		oldPoz = -pozic;
		//pozicioniramo se gde ce sledeci element da se crta u sledecoj koloni
		Translate(pDC,razmakKolona,oldPoz+1.5*r,true);
		pozic = 0;
		pom--;
	}	
	pDC->EndPath();
	pDC->StrokeAndFillPath();
	brush.DeleteObject();
	pen.DeleteObject();
}
void CMy24062019View::OnMsgName(UINT nHitTest, CPoint Point)
{
	point.x = Point.x;
	point.y = Point.y;
}
//transformacij
void CMy24062019View::Translate(CDC* pDC, float dx, float dy, bool right)
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
void CMy24062019View::Rotate(CDC* pDC, float angle, bool right)
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
void CMy24062019View::TranslateRotate(CDC* pDC,float dx,float dy,float angle,float distance)
{
	XFORM form;
	form.eM11 = cos((angle * 3.14) / 180);
	form.eM12 = sin((angle * 3.14) / 180);
	form.eM21 = -sin((angle * 3.14) / 180);
	form.eM22 = cos((angle * 3.14) / 180);
	form.eDx = dx + distance + cos(angle*3.14/180);
	form.eDy = dy + distance + sin(angle * 3.14 / 180);
	pDC->ModifyWorldTransform(&form,MWT_RIGHTMULTIPLY);
}
#pragma region...
BOOL CMy24062019View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy24062019View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy24062019View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy24062019View::AssertValid() const
{
	CView::AssertValid();
}
void CMy24062019View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy24062019Doc* CMy24062019View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy24062019Doc)));
	return (CMy24062019Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion