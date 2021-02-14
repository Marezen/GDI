#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "03.06.2015.h"
#endif
#include "03.06.2015Doc.h"
#include "03.06.2015View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy03062015View, CView)
BEGIN_MESSAGE_MAP(CMy03062015View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CMy03062015View::CMy03062015View() noexcept
{

}
CMy03062015View::~CMy03062015View()
{
	delete background;
}
BOOL CMy03062015View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

#pragma endregion
void CMy03062015View::OnDraw(CDC* pDC)
{
	CMy03062015Doc* pDoc = GetDocument();
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

	int radius = 100; // precnik novcica
	CPoint point(200, 200); // Centar novcica

	//crtanje
	DrawCoin(memDC, point, radius, (CString)"Republika Srbija Narodna banka", 12, (CString)"50", 100, RGB(0, 5, 5));
	//kraj crtanja
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	//Save screenshot novcica
	SaveBMP((CString)"Slika.bmp", pDC, point, radius);

	memDC->DeleteDC();
	delete memDC;

}
//Funkcije:
void CMy03062015View::DrawBackground(CDC* pDC, CPoint ptCenter, int radius, CString strPicture)
{
	background = new DImage();
	background->Load(strPicture);
	CRect rect(ptCenter.x - radius,ptCenter.y - radius,ptCenter.x+radius,ptCenter.y+radius); // Rectangle na kome ce biti ucitana slika
	//Region:
	CRgn rgn;
	rgn.CreateEllipticRgn(rect.left, rect.top, rect.right, rect.bottom);
	pDC->SelectClipRgn(&rgn);
	background->Draw(pDC, CRect(0,0,background->Width(),background->Height()),rect);
	pDC->SelectClipRgn(NULL);
}
void CMy03062015View::DrawCoin(CDC* pDC, CPoint ptCenter, int radius, CString strText, int fsizeText, CString strCoin, int fsizeCoin, COLORREF clrText)
{
	DrawBackground(pDC, ptCenter, radius,(CString)"bg.jpg");
	// crtanje ivice novcica
	CPen pen(PS_SOLID, 3, RGB(35, 55, 100));
	CPen* oldPen = pDC->SelectObject(&pen);
	//transparentna cetka
	CBrush* oldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	CRect rect(ptCenter.x - radius, ptCenter.y - radius, ptCenter.x + radius, ptCenter.y + radius); //(gore levo je tacka x=centar.x-radius i y = centar.y - radius)
	pDC->Ellipse(&rect);
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();

	//priprema olovke i brusheva
	CPen blackPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen1 = pDC->SelectObject(&blackPen);

	CBrush brush;
	brush.CreateSolidBrush(clrText);
	CBrush* oldBrush1 = pDC->SelectObject(&brush);

	//Sada ispisujemo tekst u sredini. Vrednost novcica
	CFont font1;
	font1.CreateFont(fsizeCoin, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont* oldFont = pDC->SelectObject(&font1);

	int oldBkMode1 = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign1 = pDC->SetTextAlign(TA_CENTER);
	COLORREF oldTextCol1 = pDC->SetTextColor(clrText);
	//ispise vrednost
	pDC->TextOut(ptCenter.x, (ptCenter.y - (fsizeCoin / 2)), strCoin);
	//nakon toga podesi ono fiksno
	pDC->SetTextColor(oldTextCol1);
	pDC->SetTextAlign(oldTextAlign1);
	pDC->SetBkMode(oldBkMode1);

	//Ispis onog teksta sa strane
	CFont font2;
	font2.CreateFont(fsizeText, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	pDC->SelectObject(&font2);

	int oldBkMode2 = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign2 = pDC->SetTextAlign(TA_CENTER);
	COLORREF oldTextCol2 = pDC->SetTextColor(clrText);
	// za njega mora da prodjemo za svako slovo u tekstu
	//svako slovo nacrta, i onda pomeri za ugao "angle"
	float angle = 360 / strText.GetLength(); // nije bitno kolika je dimenzija teksta. uvek ce ravnomerno da rasporedi
	float tmpAngle = 0;
	for (int i = 0; i < strText.GetLength(); i++)
	{
		XFORM form;
		pDC->GetWorldTransform(&form);

		TranslateRotate(pDC,ptCenter.x,ptCenter.y,tmpAngle,radius);// pozicija gde treba da se crta tekst
		Rotate(pDC, 90, false);
		pDC->TextOutW(0,fsizeText,(CString)strText.GetAt(i));
		pDC->SetWorldTransform(&form);
		tmpAngle += angle; // pomera udesno

	}
	pDC->SetTextColor(oldTextCol2);
	pDC->SetTextAlign(oldTextAlign2);
	pDC->SetBkMode(oldBkMode2);
	//ciscenje
	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldPen1);
	pDC->SelectObject(oldBrush1);
	//obavezno brisanje
	brush.DeleteObject();
	blackPen.DeleteObject();
	font1.DeleteObject();
	font2.DeleteObject();
}
void CMy03062015View::SaveBMP(CString name, CDC* pDC, CPoint ptCenter, int radius)
{
	int novcic_width = radius * 2; // dupla velicina,da bi stao ceo novcic na sliku.
	int novcic_height = radius * 2;
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, novcic_width, novcic_height);
	memDC->SelectObject(&bmp);

	memDC->BitBlt(0, 0, novcic_width, novcic_height, pDC, ptCenter.x - radius, ptCenter.y - radius, SRCCOPY);

	DImage* img = new DImage(bmp);
	img->Save(name);
	delete img;

	memDC->DeleteDC();
	delete memDC;
}
//transformacije
void CMy03062015View::Rotate(CDC* pDC, float angle, bool right)
{
	XFORM form;
	form.eM11 = cos((3.14*angle)/180);
	form.eM12 = sin((3.14 * angle) / 180);
	form.eM21 = -sin((3.14 * angle) / 180);
	form.eM22 = cos((3.14 * angle) / 180);
	form.eDx = 0;
	form.eDy = 0;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
void CMy03062015View::TranslateRotate(CDC* pDC, float x, float y, float angle, float distance)
{
	XFORM form;
	form.eM11 = cos((3.14 * angle) / 180);
	form.eM12 = sin((3.14 * angle) / 180);
	form.eM21 = -sin((3.14 * angle) / 180);
	form.eM22 = cos((3.14 * angle) / 180);
	form.eDx = x + (distance * cos((3.14 * angle) / 180));
	form.eDy = y + (distance * sin((3.14 * angle) / 180));
	pDC->SetWorldTransform(&form);
}
#pragma region ..
BOOL CMy03062015View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy03062015View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy03062015View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy03062015View::AssertValid() const
{
	CView::AssertValid();
}
void CMy03062015View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy03062015Doc* CMy03062015View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy03062015Doc)));
	return (CMy03062015Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion