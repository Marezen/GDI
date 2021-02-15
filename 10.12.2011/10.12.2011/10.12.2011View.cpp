#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "10.12.2011.h"
#endif
#include "10.12.2011Doc.h"
#include "10.12.2011View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CMy10122011View, CView)
BEGIN_MESSAGE_MAP(CMy10122011View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CMy10122011View::CMy10122011View() noexcept
{
	sky = new DImage();
	move = 0;
	wheel = GetEnhMetaFile((CString)"tocak.emf");
	car = GetEnhMetaFile((CString)"clio.emf");
	sky->Load((CString)"sky.jpg");
	car_width = 645;
	car_height = 260;
	wheel_width = 100;
	wheel_height = 100;

}
CMy10122011View::~CMy10122011View()
{
	delete sky;
	DeleteEnhMetaFile(car);
	DeleteEnhMetaFile(wheel);
}
BOOL CMy10122011View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion
void CMy10122011View::OnDraw(CDC* pDC)
{
	CMy10122011Doc* pDoc = GetDocument();
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
	//crtanje:
	sky->Draw(memDC, CRect(0, 0, sky->Width(), sky->Height()), CRect(0, 0, rect.Width(), rect.Height()));
	Draw(&rect, memDC);
	//kraj crtanja:
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;
}
//Funkcije crtanja:
void CMy10122011View::Draw(CRect rect,CDC* pDC)
{
	int postolje_width = 200;
	int postolje_height = rect.Height() - (rect.Height()/2 + car_height/2 + 80);
	//kordinate postolja:
	int postoljeStartX = rect.Width() / 2 - postolje_width / 2;
	int postoljeStartY = rect.Height() - postolje_height;
	int postoljeEndX = rect.Width() / 2 + postolje_width / 2;
	int postoljeEndY = rect.Height();

	CBrush blackBrush;
	blackBrush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* oldBrush = pDC->SelectObject(&blackBrush);
	pDC->Rectangle(postoljeStartX, postoljeStartY, postoljeEndX, postoljeEndY);
	pDC->SelectObject(oldBrush);

	//Portebno je nacrtati 2 bilborda:
	int sivi_width = car_width + 160; // 80 sa leve i 80 sa desne strane,zato je +160
	int sivi_height = car_height + 160;
	//koordinate sivog:
	int siviStartX = rect.Width() / 2 - sivi_width / 2;
	int siviStartY = rect.Height() / 2 - sivi_height / 2;
	int siviEndX = rect.Width() / 2 + sivi_width / 2;
	int siviEndY = rect.Height() / 2 + sivi_height / 2;
	//prvo crni pravougaonik koji ce da predstavlja senku
	CBrush blackBrush2;
	blackBrush2.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* oldBrushBlack = pDC->SelectObject(&blackBrush2);
	pDC->RoundRect(CRect(siviStartX + 5, siviStartY + 5, siviEndX + 5, siviEndY + 5),CPoint(10,10));
	pDC->SelectObject(&oldBrushBlack);
	blackBrush2.DeleteObject();

	CBrush grayBrush;
	grayBrush.CreateSolidBrush(RGB(170, 170, 170));
	CBrush* oldBrush2 = pDC->SelectObject(&grayBrush);
	pDC->RoundRect(CRect(siviStartX, siviStartY, siviEndX, siviEndY),CPoint(10,10));
	pDC->SelectObject(oldBrush2);
	grayBrush.DeleteObject();

	//Drugi pravougaonik , BELI:
	int beli_width = car_width + 80;
	int beli_height = car_height + 80;
	//koordinate:
	int beliStartX = rect.Width() / 2 - beli_width / 2;
	int beliStartY = rect.Height() / 2 - beli_height / 2;
	int beliEndX = rect.Width() / 2 + beli_width / 2;
	int beliEndY = rect.Height() / 2 + beli_height /2;
	//prvo senka:
	CBrush blackBrush3;
	blackBrush2.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* oldBrushBlack2 = pDC->SelectObject(&blackBrush2);
	pDC->RoundRect(CRect(beliStartX + 5, beliStartY + 5, beliEndX + 5, beliEndY + 5), CPoint(10, 10));
	pDC->SelectObject(&oldBrushBlack2);
	blackBrush3.DeleteObject();
	CBrush whiteBrush;
	whiteBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush* oldBrush3 = pDC->SelectObject(&whiteBrush);
	pDC->RoundRect(CRect(beliStartX, beliStartY, beliEndX, beliEndY), CPoint(10, 10));
	pDC->SelectObject(oldBrush3);
	whiteBrush.DeleteObject();

	//nakon bilborda,crtamo automobil:
	//koordinate vozila:
	int carStartX = rect.Width() / 2 - car_width / 2 + move; // "+move" - znaci pomeraj kad se stigsne dugme
	int carStartY = rect.Height() / 2 - car_height / 2;
	int carEndX = rect.Width() / 2 + car_width / 2 + move;
	int carEndY = rect.Height() / 2 + car_height / 2;
	//ucitavanje metafajla
	pDC->PlayMetaFile(car, CRect(carStartX, carStartY, carEndX, carEndY));

	// Ugao rotiranja guma
	float tmpAngle = move / (2 * 3.14);
	XFORM tmpForm;
	pDC->SetWorldTransform(&tmpForm);
	//pozicioniranje tockova:
	//LEVI TOCAK:
	int leviStartX = rect.Width() / 2 - car_width / 2 + move + 80;
	int leviStartY = rect.Height() / 2 + 55;
	int leviEndX = leviStartX + wheel_width;
	int leviEndY = leviStartY + wheel_height;
	//potrebno je izvrsiti transformaciju svaki put;
	TranslateRotate(pDC,leviStartX + wheel_width/2,leviStartY + wheel_height/2,tmpAngle);
	pDC->PlayMetaFile(wheel, CRect(leviStartX, leviStartY, leviEndX, leviEndY));
	pDC->SetWorldTransform(&tmpForm);

	//DESNI TOCAK:
	int desniStartX = rect.Width() / 2 + move  + 175; 
	int desniStartY = rect.Height() / 2 + 55;
	int desniEndX = desniStartX + wheel_width;
	int desniEndY = desniStartY + wheel_height;
	//Rotate(pDC, tmpAngle, false); // levo mnozenje
	//Translate(pDC, desniStartX + wheel_width / 2, desniStartY + wheel_height / 2,false);
	TranslateRotate(pDC,desniStartX + wheel_width/2,desniStartY+wheel_height/2,tmpAngle);
	pDC->PlayMetaFile(wheel, CRect(desniStartX, desniStartY, desniEndX, desniEndY));
	pDC->SetWorldTransform(&tmpForm);

}
//Transformacije:
void CMy10122011View::Translate(CDC* pDC,float x,float y,bool right)
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
void CMy10122011View::Rotate(CDC* pDC, float angle, bool right)
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
void CMy10122011View::TranslateRotate(CDC* pDC,float x,float y,float angle)
{
	XFORM form;
	form.eM11 = cos((angle * 3.14) / 180);
	form.eM12 = sin((angle * 3.14) / 180);
	form.eM21 = -sin((angle * 3.14) / 180);
	form.eM22 = cos((angle * 3.14) / 180);
	form.eDx = x - cos((angle * 3.14) / 180)*x + sin((angle * 3.14) / 180)*y;
	form.eDy = y - cos((angle * 3.14) / 180)*y - sin((angle * 3.14) / 180)*x;
	pDC->SetWorldTransform(&form);
}

//AntiFlicker + Buttons:   strelica levo i desno
void CMy10122011View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT) {
		move -= 5;
		Invalidate();
	}
	if (nChar == VK_RIGHT) {
		move += 5;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
BOOL CMy10122011View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
#pragma region ..
BOOL CMy10122011View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy10122011View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy10122011View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}
#ifdef _DEBUG
void CMy10122011View::AssertValid() const
{
	CView::AssertValid();
}
void CMy10122011View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy10122011Doc* CMy10122011View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy10122011Doc)));
	return (CMy10122011Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion