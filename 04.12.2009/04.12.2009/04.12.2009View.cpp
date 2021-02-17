#pragma region fiksno
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "04.12.2009.h"
#endif

#include "04.12.2009Doc.h"
#include "04.12.2009View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy04122009View, CView)

BEGIN_MESSAGE_MAP(CMy04122009View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CMy04122009View::CMy04122009View() noexcept
{
	im = new DImage();
	sto = new DImage();
}
CMy04122009View::~CMy04122009View()
{
}
BOOL CMy04122009View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

#pragma endregion
void CMy04122009View::OnDraw(CDC* pDC)
{
	CMy04122009Doc* pDoc = GetDocument();
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
	//crtanje scene:
	Room(memDC,&rect);
	Table(memDC, &rect);
	//kraj crtanja scene
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;

}
//Funkcije za zadatak:
void CMy04122009View::Room(CDC* pDC,CRect rect)
{
	//LEVI ZID
	CBrush brush1;
	brush1.CreateSolidBrush(RGB(32, 6, 5));
	CBrush *oldBrush = pDC->SelectObject(&brush1);
	
	pDC->Rectangle(0,0, rect.Width()/4, rect.Height());

	//DESNI ZID
	CBrush brush2;
	brush2.CreateSolidBrush(RGB(60,15,10));
	oldBrush = pDC->SelectObject(&brush2);

	pDC->Rectangle(rect.Width() / 4, 0, rect.Width(), rect.Height());

	//RAM ZA SLIKU
	CBrush brush3;
	brush3.CreateSolidBrush(RGB(128,65,5));
	oldBrush = pDC->SelectObject(&brush3);

	pDC->SelectObject(&brush3);

	pDC->Rectangle(rect.Width() / 4+25, rect.top + 25,  rect.Width() / 2 + rect.Width()/5, rect.Height()/2);

	//U RAM UCITAJ SLIKU
	im->Load(CString("Slika.jpg"));
	im->Draw(pDC, CRect(0, 0, im->Width(), im->Height()), CRect(rect.Width() / 4 + 35, rect.top + 25 + 10, rect.Width() / 2 + rect.Width() / 5 - 10, rect.Height() / 2 - 10));

	pDC->SelectObject(&oldBrush);
	brush1.DeleteObject();
	brush2.DeleteObject();
	brush3.DeleteObject();
}
void CMy04122009View::Table(CDC* pDC, CRect rect)
{
	CBrush brushTable;
	brushTable.CreateSolidBrush(RGB(127,65,5));
	CBrush* oldBrush = pDC->SelectObject(&brushTable);
	//Noge stola

	//Prednja leva noga
	pDC->Rectangle(rect.Width() * 0.12, rect.Height() * 0.85, rect.Width() * 0.14, rect.Height());
	pDC->Rectangle(rect.Width() * 0.14, rect.Height() * 0.85, rect.Width() * 0.15, rect.Height());
	//Zadnja leva noga
	pDC->Rectangle(rect.Width() * 0.32, rect.Height() * 0.75, rect.Width() * 0.34, rect.Height());
	pDC->Rectangle(rect.Width() * 0.34, rect.Height() * 0.75, rect.Width() * 0.35, rect.Height());
	//Zadnja desna noga
	pDC->Rectangle(rect.Width() * 0.66, rect.Height() * 0.75, rect.Width() * 0.68, rect.Height());
	pDC->Rectangle(rect.Width() * 0.68, rect.Height() * 0.75, rect.Width() * 0.69, rect.Height());
	//Prednja desna noga
	pDC->Rectangle(rect.Width() * 0.86, rect.Height() * 0.65, rect.Width() * 0.88, rect.Height());
	pDC->Rectangle(rect.Width() * 0.88, rect.Height() * 0.65, rect.Width() * 0.89, rect.Height());

	//Da bismo uspesno postavili gornju dasku stola
	sto->Load(CString("ASHSEN512.jpg"));
	//ucitamo sliku i iscrtamo REGION
	CRgn r1;
	//uzmimo 4 tacke za region
	CPoint pts[4];
	pts[0] = CPoint(20, rect.Height() - 40); // tacka dole levo
	pts[1] = CPoint(rect.Width() * 0.18+20, rect.Height()/2 + 35); // tacka gore levo
	pts[2] = CPoint(rect.Width() - 55, rect.Height() / 2 + 35);    //tacka gore desno
	pts[3] = CPoint(rect.Width() - 20 - rect.Width() * 0.18, rect.Height() - 40);  // tacka dole desno
	r1.CreatePolygonRgn(pts, 4, 1); // sada imamo rectangle poligon
	pDC->SelectClipRgn(&r1, RGN_AND); // da bi bilo iskrivljeno
	sto->Draw(pDC, CRect(0, 0, sto->Width(), sto->Height()), CRect(rect.left + 20, rect.CenterPoint().y + 20, rect.right - 20, rect.bottom - 40));

	//obavezno kad koristimo region:
	pDC->SelectClipRgn(NULL);
	r1.DeleteObject();
	//ploca stola, donja daska sto se vidi
	pDC->Rectangle(20, rect.Height() - 40, rect.Width() -rect.Width() * 0.18-20, rect.Height() - 30);
	//ploca stola,desni deo:
	CPoint TablePts[4];
	TablePts[0] = CPoint(rect.Width() - 20 - rect.Width() * 0.18, rect.Height() - 30);
	TablePts[1] = CPoint(rect.Width() - 20 -rect.Width()*0.18,rect.Height()-40);
	TablePts[2] = CPoint(rect.Width() - 55 ,rect.Height()/2+35);
	TablePts[3] = CPoint(rect.Width() - 55 , rect.Height()/2 + 45);
	pDC->Polygon(TablePts, 4);
	
	//FONT.
	CFont font;
	COLORREF oldClr = pDC->SetTextColor(RGB(255, 255, 255));
	int oldMode = pDC->SetBkMode(TRANSPARENT);
	font.CreateFont(36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, CString("Monotype Corsiva"));
	CFont* oldFont = pDC->SelectObject(&font);
	
	//da se ne bi poremetilo,potrebno je pre translacije i rotiranja da ucitamo flasu i case

	Bottle(pDC, rect, CPoint(rect.Width() * 0.35, rect.Height() * 0.35));
	//rotirana..
	 // ne uspeva rotacija
	Glass(pDC, rect, CPoint(rect.Width() * 0.36, rect.Height() * 0.55), 90);
	//uspravne
	Glass(pDC, rect, CPoint(rect.Width() * 0.41, rect.Height() * 0.49), 0); //najbliza flasi, casa levo
	Glass(pDC, rect, CPoint(rect.Width() * 0.44, rect.Height() * 0.52), 0); // u sredini
	Glass(pDC, rect, CPoint(rect.Width() * 0.464, rect.Height() * 0.46), 0); //gore desno

	Rotate(pDC, -45, false);

	//nabadao sam koordinate
	Translate(pDC, rect.Width()/2 - rect.Width() * 0.27+65, rect.Height()+rect.Height()/2+170, false);
	pDC->TextOut(0, 0, CString("Mare"));

	pDC->SetTextAlign(TA_CENTER);
	pDC->SetBkMode(oldMode);
	pDC->SetBkColor(oldClr);
	pDC->SelectObject(&oldBrush);
	font.DeleteObject();
	brushTable.DeleteObject();
}
void CMy04122009View::Bottle(CDC* pDC, CRect rect, CPoint bottle)
{
	ENHMETAHEADER eh; 
	HENHMETAFILE flasa = GetEnhMetaFile(CString("Flasa.emf"));;
	GetEnhMetaFileHeader(flasa, sizeof(ENHMETAHEADER), &eh);
	int width = eh.rclBounds.right - eh.rclBounds.left;
	int height = eh.rclBounds.bottom - eh.rclBounds.top;
	int factor = 3;
	PlayEnhMetaFile(pDC->m_hDC, flasa, CRect(bottle.x, bottle.y, bottle.x + width / factor, bottle.y + height / factor));
	DeleteEnhMetaFile(flasa); // obavezno brisanje
}
void CMy04122009View::Glass(CDC* pDC, CRect rect, CPoint glass, double dAngle)
{
	ENHMETAHEADER eh;
	HENHMETAFILE hendl = GetEnhMetaFile(CString("Casa.emf"));;
	GetEnhMetaFileHeader(hendl, sizeof(ENHMETAHEADER), &eh);
	int width = eh.rclBounds.right - eh.rclBounds.left; 
	int height = eh.rclBounds.bottom - eh.rclBounds.top;
	int factor = 3;
	//nakon ucitavanja case,potrebne su trasnformacije da se izvrse
	dAngle = dAngle * 3.14 / 180; // u radijane
	//Translate(pDC, -glass.x, -glass.y, false);
	//Rotate(pDC, -dAngle, true);
	//Translate(pDC,glass.x,glass.y,false);
	//TranslateRotate(pDC,glass.x , glass.y,dAngle,true);
	int oldMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM first, poc, skaliraj, rot, ret; // mora posebno da se pravi forma za rotaciju,da ne bi uticalo na dalje crtanje
	GetWorldTransform(pDC->m_hDC, &first);
	//pomeranje u centar CRect-a koji je dodeljen za crtanje
	poc.eM11 = 1.0;
	poc.eM12 = 0;
	poc.eM21 = 0;
	poc.eM22 = 1.0;
	poc.eDx = -glass.x;
	poc.eDy = -glass.y;
	SetWorldTransform(pDC->m_hDC, &poc);

	rot.eM11 = cos(dAngle);
	rot.eM12 = sin(dAngle);
	rot.eM21 = -sin(dAngle);
	rot.eM22 = cos(dAngle);
	rot.eDx = glass.x;
	rot.eDy = glass.y;
	ModifyWorldTransform(pDC->m_hDC, &rot, MWT_RIGHTMULTIPLY);
	SetGraphicsMode(pDC->m_hDC, oldMode);
	SetWorldTransform(pDC->m_hDC, &first);
	PlayEnhMetaFile(pDC->m_hDC, hendl, CRect(glass.x, glass.y, glass.x + width / factor, glass.y + height / factor));
	DeleteEnhMetaFile(hendl);
}
//transformacije
void CMy04122009View::Rotate(CDC* pDC,float angle,bool right)
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
void CMy04122009View::Translate(CDC* pDC,float x,float y,bool right)
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
void CMy04122009View::TranslateRotate(CDC* pDC,float x,float y,float angle,bool right)
{
	XFORM form;
	form.eM11 = cos((angle * 3.14) / 180);
	form.eM12 = sin((angle * 3.14) / 180);
	form.eM21 = -sin((angle * 3.14) / 180);
	form.eM22 = cos((angle * 3.14) / 180);
	form.eDx = x;
	form.eDy = y;
	if(right)
		ModifyWorldTransform(pDC->m_hDC, &form, MWT_RIGHTMULTIPLY);
	else
		ModifyWorldTransform(pDC->m_hDC, &form, MWT_RIGHTMULTIPLY);
}
#pragma region ....
BOOL CMy04122009View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy04122009View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy04122009View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy04122009View::AssertValid() const
{
	CView::AssertValid();
}
void CMy04122009View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy04122009Doc* CMy04122009View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy04122009Doc)));
	return (CMy04122009Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion