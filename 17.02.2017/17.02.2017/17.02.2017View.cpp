#pragma region fiksno
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "17.02.2017.h"
#endif
#include "17.02.2017Doc.h"
#include "17.02.2017View.h"
#include "DIMage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CMy17022017View, CView)
BEGIN_MESSAGE_MAP(CMy17022017View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()
CMy17022017View::CMy17022017View() noexcept
{
	CenterX = 125;
	CenterY = 125;
	UgaoAlfa = 0;
}
CMy17022017View::~CMy17022017View()
{
}
BOOL CMy17022017View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion
void CMy17022017View::OnDraw(CDC* pDC)
{
	CMy17022017Doc* pDoc = GetDocument();
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

	int radius = 100; // poluprecnik spoljasnjeg kruga
	//crtanje:
	Translate(memDC, CenterX, CenterY, true); // pozicioniramo centar
	DrawFanyCircle(memDC, radius, 8, UgaoAlfa, 6, RGB(150, 150, 150), RGB(200, 100, 100), (CString)"TEXT");
	SavePicture(memDC, (CString)"Slika.bmp", radius);
	//kraj crtanja
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}
//Transformacije:
void CMy17022017View::Translate(CDC* pDC, float x, float y, bool right)
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
void CMy17022017View::Rotate(CDC* pDC, float angle, bool right)
{
	XFORM form;
	form.eM11 = cos((angle*3.14)/180);
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
void CMy17022017View::TranslateRotate(CDC* pDC, float x, float y, float angle, float distance)
{
	XFORM form;
	form.eM11 = cos((angle * 3.14) / 180);
	form.eM12 = sin((angle * 3.14) / 180);
	form.eM21 = -sin((angle * 3.14) / 180);
	form.eM22 = cos((angle * 3.14) / 180);
	form.eDx = x + (distance * cos((angle * 3.14) / 180));
	form.eDy = y + (distance * sin((angle * 3.14) / 180));
	pDC->SetWorldTransform(&form);
}
//Crtanje krugova:
void CMy17022017View::DrawMultiCircle(CDC* pDC, int radius, int nConc, COLORREF colFill, CString strText)
{
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CPen* oldPen = pDC->SelectObject(&pen);

	int tmpRadius = radius; // distanca
	//izvucemo vrednosti boja:
	int tmpR = GetRValue(colFill);
	int tmpG = GetGValue(colFill);
	int tmpB = GetBValue(colFill);
	//nConc puta se izvrsi petlja, gde se crta krug
	// i na svaku iteraciju smanjujemo radius. 
	//POcinjemo sa Spoljasnjim krugom, i svaki sledeci je manji za 10%,zato imamo tmpRadius

	for (int i = 0; i < nConc; i++)
	{
		//moramo svaki put da kreiramo brush,jer je svaki krug razlicite boje, za 5% svetliji
		CBrush brush;
		brush.CreateSolidBrush(RGB(tmpR, tmpG, tmpB));
		CBrush* oldBrush = pDC->SelectObject(&brush);

		//CRect elipse(-tmpRadius, -tmpRadius, tmpRadius, tmpRadius);
		pDC->Ellipse(-tmpRadius, -tmpRadius, tmpRadius, tmpRadius);
		// i nakon crtanja elipse,smanjimo radius za 10%, i promenimo boju za 5%
		tmpRadius = tmpRadius - (tmpRadius * 0.10);
		tmpR = tmpR + (tmpR * 0.05);
		tmpG = tmpG + (tmpG * 0.05);
		tmpB = tmpB + (tmpB * 0.05);

		pDC->SelectObject(oldBrush);
		brush.DeleteObject();
	}
	//Text je sledeci:
	CFont font;
	font.CreateFont(12, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont* oldFont = pDC->SelectObject(&font);
	int oldTextMode = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	COLORREF oldCol = pDC->SetTextColor(RGB(0, 0, 0));
	pDC->TextOutW(1, -5, strText); // pozicionirano u centru manjeg kruga

	pDC->SetBkMode(oldTextMode);
	pDC->SetTextAlign(oldTextAlign);
	pDC->SetTextColor(oldCol);
	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
	font.DeleteObject();
}
void CMy17022017View::DrawFanyCircle(CDC* pDC, int radius, int nCircle, double dAlpha, int nConc, COLORREF colFillBig, COLORREF colFillSmall, CString strText)
{
	//Veliki
	DrawMultiCircle(pDC, radius, nConc, colFillBig, strText);
	//Sada mali krugovi:
	float angle = 360 / nCircle; // ugao na kome ce mali krug da se crta
	float tmpAngle = 0;
	for (int i = 0; i < nCircle; i++)
	{
		XFORM form;
		pDC->GetWorldTransform(&form);
		//za 240 stepeni , iz zadatka
		TranslateRotate(pDC, CenterX, CenterY, 240+tmpAngle+dAlpha, radius); // pozicija kruga u odnosu na centar
		Rotate(pDC, -tmpAngle-240-dAlpha, false);
		// mora da oduzme tmpAngle i 240 i dAlpha , da bi Broj u malom krugu bio uspravan uvek

		CString str;
		str.Format(_T("%d"), (i + 1));
		DrawMultiCircle(pDC, 0.15 * radius, 2, colFillSmall, str);
		pDC->SetWorldTransform(&form);
		tmpAngle += angle;
	}
}
void CMy17022017View::SavePicture(CDC* pDC, CString pic, int radius)
{
	int width = (radius * 2) + (2 * radius * 0.2);
	int height = (radius * 2) +(2 * radius * 0.2);
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, width, height);
	memDC->SelectObject(&bmp);
	memDC->BitBlt(0, 0, width, height, pDC, -width / 2, -height / 2, SRCCOPY);
	DImage* img = new DImage(bmp);
	img->Save(pic);
	delete img;
	memDC->DeleteDC();
	delete memDC;
}
//Antiflicker  +  pomeranje malih uglova:
void CMy17022017View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'W') 
	{
		UgaoAlfa += 5;
		Invalidate();
	}
	else if(nChar == 'Q')
	{
		UgaoAlfa -= 5;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
BOOL CMy17022017View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
#pragma region ..
BOOL CMy17022017View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy17022017View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{}
void CMy17022017View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy17022017View::AssertValid() const
{
	CView::AssertValid();
}

void CMy17022017View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy17022017Doc* CMy17022017View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy17022017Doc)));
	return (CMy17022017Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion