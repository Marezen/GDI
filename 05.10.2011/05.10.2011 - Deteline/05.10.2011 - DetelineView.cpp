#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "05.10.2011 - Deteline.h"
#endif
#include "05.10.2011 - DetelineDoc.h"
#include "05.10.2011 - DetelineView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy05102011DetelineView, CView)

BEGIN_MESSAGE_MAP(CMy05102011DetelineView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()


CMy05102011DetelineView::CMy05102011DetelineView() noexcept
{
}

CMy05102011DetelineView::~CMy05102011DetelineView()
{
}

BOOL CMy05102011DetelineView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy05102011DetelineView::OnDraw(CDC* pDC)
{
	CMy05102011DetelineDoc* pDoc = GetDocument();
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

	//crtanje
	COLORREF boje[] = { RGB(50, 200, 25), RGB(240, 50, 80), RGB(180, 255, 255) };
	DrawPicture(memDC, 60, boje, RGB(255, 0, 0), 1.4, 3, 3);
	//kraj crtanja
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;
}
void CMy05102011DetelineView::DrawFigure(CDC* pDC, int size, COLORREF colFill, COLORREF colLine)
{
	//Cime crtamo:
	CPen pen;
	pen.CreatePen(PS_SOLID,2,colLine);
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(colFill);
	CBrush* oldBrush = pDC->SelectObject(&brush);

	//Pomocna figura,odnosna onaj pomocni kvadrat za koga se odnosi SIZE:

	//Mora da se menja
	CRect rect;
	//za RECT.LEFT da je = size,onda bi pomocni bio skroz levo,a treba na pola "lista", znaci treba size/2
	rect.left = -size / 2 - size / 4;  // -size/2 da bi bilo polovina od levog lista, i -size/4 da bi mrdnulo jos zbog tacke odakle pocinje unutrasnji luk
	//isto tako i za top
	rect.top = -size / 2 - size / 4;
	//desni i donji su manji,jer se posle povecavaju
	rect.right = -size / 4;
	rect.bottom = -size / 4;

	//IMAMO 2 tacke 
	CPoint pointF(-size / 2, -size / 4); // tacka kraja
	CPoint pointS(-size / 4, -size / 2); // tacka pocetke crtanja luka

	//pocinjemo sa putanjom
	pDC->BeginPath();

	//prvo crtamo luk unutar pomocne kocke
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->MoveTo(pointF); // pocne desne tacke, i luk ide na levo dole
	pDC->ArcTo(rect, pointF, pointS);

	rect.left += size / 2;
	rect.right += size / 2;
	pointF = pointS; // sada tacka koja je na ivici pomocnog kvadrata, jer krajnja tacka
	pointS.x += size / 2; // povecamo samo X ,jer ide na desno
	//gornji list,veci luk
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(rect, pointF, pointS);

	//left i rgiht treba prosiriti ,da bismo smo desni luk da nacrtamo
	rect.left += size / 2;
	rect.right += size / 2;

	pointF = pointS; 
	//povecamo za size/4 , jer ide dole i desno za 4. velicine
	pointS.x += size / 4;
	pointS.y += size / 4;
	//sada unutrasnji luk , gornji desni
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(rect, pointF, pointS);

	rect.top += size / 2;
	rect.bottom += size / 2;
	pointF = pointS;
	//ovde samo poveca Y,jer tacka treba da bude dole samo,i tako dobijamo desni luk(list)
	pointS.y += size / 2;

	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(rect, pointF, pointS);
	//posto sada crtamo donji deo,top i bott povecamo
	rect.top += size / 2;
	rect.bottom += size / 2;
	pointF = pointS; // tacka kraja desnog lista, je pocetak unutrasnjeg luka dole desno
	pointS.x -= size / 4;
	pointS.y += size / 4;

	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(rect, pointF, pointS);
	//sada mora da smanjimo kvadrat
	rect.left -= size / 2;
	rect.right -= size / 2;
	pointF = pointS;
	// x  se smanji, jer tacka treba da se nadje levo od centra,jer crtamo donji list,veci luk
	pointS.x -= size / 2;

	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(rect, pointF, pointS);
	//mrdamo rect opet na levo
	rect.left -= size / 2;
	rect.right -= size / 2;
	pointF = pointS; // krajnja tacka 
	pointS.x -= size / 4;
	pointS.y -= size / 4;
	//unutrasnji dole levo 
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(rect, pointF, pointS);
	rect.top -= size / 2;
	rect.bottom -= size / 2;
	//i postavljamo koordinate za levi List,veci luk
	pointF = pointS;
	pointS.y -= size / 2; // tacka treba da ode gore
	
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(rect, pointF, pointS);

	pDC->EndPath();
	pDC->StrokeAndFillPath();
	pen.DeleteObject();
	brush.DeleteObject();
}
void CMy05102011DetelineView::DrawComplexFigure(CDC* pDC, int size, COLORREF colFill[], COLORREF colLine, double ratio, CString str)
{
	int sizeSmall = size / ratio;
	int sizeMid = size;
	int sizeLarge = size * ratio;
	//iscrtaju se sve 3
	DrawFigure(pDC, sizeLarge, colFill[0], colLine);
	DrawFigure(pDC, sizeMid, colFill[1], colLine);
	DrawFigure(pDC, sizeSmall, colFill[2], colLine);

	// i jos font:
	CFont font;
	font.CreateFontW(12, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");

	COLORREF clrOld = pDC->SetTextColor(colLine);
	int oldMode = pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER);

	CFont* oldFont = pDC->SelectObject(&font);
	pDC->TextOutW(0, 0, str);

	pDC->SelectObject(oldFont);
	pDC->SetTextColor(clrOld);
	pDC->SetBkMode(oldMode);
	font.DeleteObject();
}
void CMy05102011DetelineView::DrawPicture(CDC* pDC, int size, COLORREF colFill[], COLORREF colLine, double ratio, int row, int col)
{
	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	// pomocna promenljiva kojom odredjujemo pozicije detelina
	int pom = size * ratio + (size * ratio) / 2; 
	//size*ratio predstavlja onaj najveci,dakle to je ustvari 1 detelina, sabira se sa jos (size*ratio) / 2 , jer to predstavlja razmak

	int xPos = pom;
	int yPos = pom;

	int rowRazmak = (pom + size / 2) / 2;
	int columnRazmak = pom + size / 2;

	int kolone = col;
	bool nepar = true; // za prvi obilazak znaci da je neparan u prvom redu
	//zato sto ce nulti red odmah da se nacrta,pa tek onda pita da li je neparan
	//sada kroz matricu:
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < kolone; j++)
		{
			TranslateRotate(pDC, 0, xPos, yPos);
			DrawComplexFigure(pDC, size, colFill, colLine, ratio, L"10");
			pDC->SetWorldTransform(&oldForm);
			xPos +=columnRazmak; // pomerimo se na desno za sledecu detelinu
		}
		if (nepar)
		{
			//ako je neparan red,onda crta jednu kolonu manje
			kolone = col - 1; // 
			nepar = !nepar;
			//ali samim tim,pocetak prve figure je pomeren
			xPos = pom + pom / 2 + size / 4; // size/4 jer u neparnom redu se crta na jos desno
			yPos += rowRazmak; // za malo se spusti dole
		}
		else
		{
			kolone = col;
			nepar = !nepar;
			xPos = pom; // pozicionira na levo,inic, pozicija crtanja 
			yPos += rowRazmak; // i spusti za red
		}
	}
	pDC->SetWorldTransform(&oldForm);
}
void CMy05102011DetelineView::SaveHMetaFile(CDC* pDC)
{
	//HENHMETAFILE hEnhMetaFile = GetMetaFileFromSomeWhere(); 
	//UINT bytes = GetWinMetaFileBits(pDC->m_hDC, 0, NULL, MM_ANISOTROPIC, HDC);
	//::GetWinMetaFileBits(hEnhMetaFile, bytes, lpbBuffer, MM_ANISOTROPIC, metaDC);
	//HMETAFILE hMetaFile = SetMetaFileBitsEx(bytes, buffer);
	//CopyMetaFile(hMetaFile, file);
}
//transformacija
void CMy05102011DetelineView::Translate(CDC* pDC,float dx,float dy,bool right)
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
void CMy05102011DetelineView::TranslateRotate(CDC* pDC, float angle, float dx, float dy)
{
	XFORM form;
	form.eM11 = cos((angle * 3.14) / 180);
	form.eM12 = sin((angle * 3.14) / 180);
	form.eM21 = -sin((angle * 3.14) / 180);
	form.eM22 = cos((angle * 3.14) / 180);
	form.eDx = dx;
	form.eDy = dy;
	pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
}
#pragma region ....
BOOL CMy05102011DetelineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy05102011DetelineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy05102011DetelineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy05102011DetelineView::AssertValid() const
{
	CView::AssertValid();
}
void CMy05102011DetelineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy05102011DetelineDoc* CMy05102011DetelineView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy05102011DetelineDoc)));
	return (CMy05102011DetelineDoc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion
