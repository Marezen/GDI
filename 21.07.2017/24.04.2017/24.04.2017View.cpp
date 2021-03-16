#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "24.04.2017.h"
#endif
#include "24.04.2017Doc.h"
#include "24.04.2017View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy24042017View, CView)

BEGIN_MESSAGE_MAP(CMy24042017View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CMy24042017View::CMy24042017View() noexcept
{
	img = new DImage();

}
CMy24042017View::~CMy24042017View()
{
	delete img;
}
BOOL CMy24042017View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy24042017View::OnDraw(CDC* pDC)
{
	CMy24042017Doc* pDoc = GetDocument();
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

	//kao iz primera iz 2012,isto
	DrawRosete(memDC, 100, 100, 50, 8);
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	//rotacija, koristi se PlgBit
	RotateImage("bg.jpg", 10);
	memDC->DeleteDC();
	delete memDC;
}

void CMy24042017View::DrawRosete(CDC* pDC, int x, int y, int size, int count)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(150, 150, 0));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brushOrange;
	brushOrange.CreateSolidBrush(RGB(255, 165, 0));
	CBrush* oldBrushOrange = pDC->SelectObject(&brushOrange);

	pDC->Ellipse(x - size, y - size, x + size, y + size);

	//elipse koje predstavljaju latice:
	CBrush brushWhite;
	brushWhite.CreateSolidBrush(RGB(255, 252, 255));
	pDC->SelectObject(&brushWhite);

	int visinaElipsi = size / 3;
	float angle = 360 / count; // koliko latica /2
	float tmpAngle = 0;
	for (int i = 0; i < count; i++)
	{
		XFORM form;
		pDC->GetWorldTransform(&form);
		TranslateRotate(pDC, x, y, tmpAngle, size / 2);
		pDC->Ellipse(-size / 2, -visinaElipsi / 2, size / 2, visinaElipsi / 2);
		pDC->SetWorldTransform(&form);
		tmpAngle += angle;
	}
	pDC->SelectObject(&brushOrange);
	pDC->Ellipse(x - visinaElipsi, y - visinaElipsi, x + visinaElipsi, y + visinaElipsi);

	pDC->SelectObject(oldBrushOrange);
	pDC->SelectObject(oldPen);
	//obavezno brisanje
	brushWhite.DeleteObject();
	brushOrange.DeleteObject();
	pen.DeleteObject();
}
void CMy24042017View::RotateImage(char* filename, double alfa)
{
	img->Load((CString)filename);
	CRect rect;
	GetClientRect(&rect);
	CDC* pDC = GetDC();
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()); // preko celog prozorceta
	memDC->SelectObject(&bmp);

	img->Draw(pDC, CRect(0, 0, img->Width(), img->Height()), CRect(0, 0, rect.Width(), rect.Height()));

	POINT points[3];
	points[0] = CPoint(100,110);
	points[1] = CPoint(100+img->Width()*0.8 *cos(alfa*3.14/180), 110 -img->Height()*0.8*sin(alfa*3.14/180));
	points[2] = CPoint(100+img->Width()*0.8*sin(alfa*3.4/180), 110 +img->Height()*0.8*cos(alfa * 3.4 / 180));
	CBitmap Bmp;

	memDC->PlgBlt(points,pDC,0 , 0,rect.Width()*0.9,rect.Height(),Bmp,0,0);
	
	//pDC->PlgBlt(points, pDC, 0, 0, img->Width()/2,img->Height()/2, bmp, 0, 0);
	DImage image(bmp);
	image.Save((CString)"Output.jpg");

	memDC->DeleteDC();
	delete memDC;
}
void CMy24042017View::Rotate(CDC* pDC, float angle)
{
	XFORM form;
	form.eM11 = cos((angle * 3.14) / 180);
	form.eM12 = sin((angle * 3.14) / 180);
	form.eM21 = -sin((angle * 3.14) / 180);
	form.eM22 = cos((angle * 3.14) / 180);
	form.eDx = 0.0;
	form.eDy = 0.0;
	pDC->ModifyWorldTransform(&form,MWT_RIGHTMULTIPLY);
}
void CMy24042017View::TranslateRotate(CDC* pDC, float x, float y, float angle, float distance)
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

#pragma region ....
BOOL CMy24042017View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy24042017View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy24042017View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy24042017View::AssertValid() const
{
	CView::AssertValid();
}
void CMy24042017View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy24042017Doc* CMy24042017View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy24042017Doc)));
	return (CMy24042017Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion
