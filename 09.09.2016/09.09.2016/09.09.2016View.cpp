#pragma region fiksno

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "09.09.2016.h"
#endif

#include "09.09.2016Doc.h"
#include "09.09.2016View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CMy09092016View, CView)
BEGIN_MESSAGE_MAP(CMy09092016View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy09092016View construction/destruction
CMy09092016View::CMy09092016View() noexcept
{
}
CMy09092016View::~CMy09092016View()
{
}
BOOL CMy09092016View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

#pragma endregion 

void CMy09092016View::OnDraw(CDC* pDC)
{
	CMy09092016Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	memDC->SelectObject(&bmp);

	int oldMode = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM form;
	memDC->GetWorldTransform(&form);

	//crtanje
	DrawClock(memDC, 10, 8, 37);
	//zavrseno crtanje

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	//cuvanje
	Save(CString("name.bmp"),250, 250);

	//nakon cuvanja brisemo
	memDC->DeleteDC();
	delete memDC;
}


//FUNKCIJE Transformacija
void CMy09092016View::Translate(CDC* pDC,float x,float y, bool right)
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
void CMy09092016View::Rotate(CDC* pDC,float angle,bool right)
{
	XFORM form;
	form.eM11 = cos((3.14 * angle) / 180);
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
void CMy09092016View::TranslateRotate(CDC* pDC, float x, float y,float angle, float distance)
{
	XFORM form;
	form.eM11 = cos((3.14*angle)/180);
	form.eM12 = sin((3.14 * angle) / 180);
	form.eM21 = -sin((3.14 * angle) / 180);
	form.eM22 = cos((3.14 * angle) / 180);
	form.eDx = x + (distance * cos((3.14 * angle) / 180));
	form.eDy = y + (distance * sin((3.14 * angle) / 180));
	pDC->SetWorldTransform(&form);
}

//Glavna:
void CMy09092016View::DrawClock(CDC* pDC,int h, int m, int s)
{
	DrawNum(pDC, 250, 250);
	DrawNeedles(pDC, 250, 250, h, m, s);
}
//Funkcije za crtanje sata:
void CMy09092016View::DrawNum(CDC* pDC,int x,int y)
{
	//pozadina sata:
	CBrush bkBrush;
	bkBrush.CreateSolidBrush(RGB(80,80,80));
	CBrush* oldBrush = pDC->SelectObject(&bkBrush);
	//ovo je ..
	pDC->Rectangle(x - 100, y - 100, x + 100, y + 100);
	
	DrawMarks(pDC, 250, 250);
	//sada je potrebno,iznad svake tacke da se nacrta broj:
	CFont font;
	font.CreateFont(16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont* oldFont = pDC->SelectObject(&font);
	//obavezno postavimo da pozadina bude transparentna
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	COLORREF oldColTex = pDC->SetTextColor(RGB(255, 255, 0));

	int angle = 360 / 12;
	int tmpAngle = -90 + angle; // podesimo da pocne da crta od jedinice
	//da pocne od 12 ,tada je tmpAngle = 0 , tmpAngle +=angle je na mesto gde treba da bude jedinica.
	//minus  90 jer bez toga bi pocinjao da broji od 3..
	for (int i = 0; i < 12; i++)
	{
		XFORM form;
		pDC->GetWorldTransform(&form);
		TranslateRotate(pDC,x,y,tmpAngle,90);
		Rotate(pDC, -tmpAngle, false); // rotira font,da bude uspravno napisano
		CString str;
		str.Format(_T("%d"), (i+1));
		pDC->TextOut(1, -8, str);
		pDC->SetWorldTransform(&form);
		tmpAngle += angle;
	}
	pDC->SetTextColor(oldColTex);
	pDC->SetTextAlign(oldTextAlign);
	pDC->SetBkMode(oldBkMode);
	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldBrush);
	bkBrush.DeleteObject();
	font.DeleteObject();
}
void CMy09092016View::DrawMarks(CDC* pDC, int x, int y)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	pDC->SelectObject(&brush);

	//tacke koje oznacavaju sat
	float angle = 360 / 12;
	float tmpAngle = 0; // pocinje od 12.. i posle se uvecava za angle
	for (int i = 0; i < 12; i++)
	{
		XFORM form;
		pDC->GetWorldTransform(&form);
		TranslateRotate(pDC, x, y, tmpAngle, 78); // 78 je distanca od centra
		pDC->Rectangle(-2, -2, 6, 2);
		pDC->SetWorldTransform(&form);
		tmpAngle += angle;
	}
	brush.DeleteObject();
	pen.DeleteObject();
	pDC->SelectObject(oldPen);
}
void CMy09092016View::DrawH(CDC* pDC,int x,int y) // kazaljka za sat
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	Translate(pDC, x, y, true); // pozicioniranje na centar

	CPoint Pt[4];
	Pt[0] = CPoint(-5, 0);
	Pt[1] = CPoint(0, 5);
	Pt[2] = CPoint(50, 0);
	Pt[3] = CPoint(0,-5);
	pDC->Polygon(Pt, 4);

	pDC->SetWorldTransform(&oldForm);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pen.DeleteObject();
}
void CMy09092016View::DrawM(CDC* pDC,int x,int y)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	Translate(pDC, x, y, true); // pozicioniranje na centar

	CPoint Pt[4];
	Pt[0] = CPoint(-4, 0);
	Pt[1] = CPoint(0, 4);
	Pt[2] = CPoint(71, 0);
	Pt[3] = CPoint(0, -4);
	pDC->Polygon(Pt, 4);

	pDC->SetWorldTransform(&oldForm);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pen.DeleteObject();
}
void CMy09092016View::DrawS(CDC* pDC, int x, int y)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 0, 0));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	Translate(pDC, x, y, true); // pozicioniranje na centar

	CPoint Pt[4];
	Pt[0] = CPoint(-1, 1);
	Pt[1] = CPoint(80, 1);
	Pt[2] = CPoint(80, -1);
	Pt[3] = CPoint(-1, -1);
	pDC->Polygon(Pt, 4);

	pDC->SetWorldTransform(&oldForm);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pen.DeleteObject();
}
void CMy09092016View::DrawNeedles(CDC* pDC, int x, int y, int h, int m, int s)
{
	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	float rotAngleH = (h * (360/12)) -90;
	float rotAngleM = (m * (360 / 60)) - 90;
	float rotAngleS = (s * (360 / 60)) - 90;

	//nakon izracunavanja pozicije,odnosno ugla kazaljke
	//crtamo svaku kazaljku

	Rotate(pDC, rotAngleH, false);
	DrawH(pDC, x, y);
	pDC->SetWorldTransform(&oldForm);

	Rotate(pDC, rotAngleM, false);
	DrawM(pDC, x, y);
	pDC->SetWorldTransform(&oldForm);

	Rotate(pDC, rotAngleS, false);
	DrawS(pDC, x, y);
	pDC->SetWorldTransform(&oldForm);

}
void CMy09092016View::Save(CString name,int x, int y)
{
	CDC* pDC = GetDC();

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, 200, 200);
	memDC->SelectObject(&bmp);

	memDC->BitBlt(0, 0, 200, 200, pDC, x - 100, y - 100, SRCCOPY);

	DImage img(bmp);
	img.Save(name);

	memDC->DeleteDC();
	delete memDC;
}
#pragma region ..
BOOL CMy09092016View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy09092016View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy09092016View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy09092016View diagnostics

#ifdef _DEBUG
void CMy09092016View::AssertValid() const
{
	CView::AssertValid();
}

void CMy09092016View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy09092016Doc* CMy09092016View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy09092016Doc)));
	return (CMy09092016Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion
