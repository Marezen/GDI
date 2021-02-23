#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "08.12.2012.h"
#endif
#include "08.12.2012Doc.h"
#include "08.12.2012View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy08122012View, CView)

BEGIN_MESSAGE_MAP(CMy08122012View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CMy08122012View::CMy08122012View() noexcept
{
	leftX = 210;
	leftY = 148;
	rightX = 601;
	rightY = 275;
	midX = 400;
	midY = 230;
	midRot = -10;
	leftRot = 0;
	rightRot = 4;
}
CMy08122012View::~CMy08122012View()
{
}
BOOL CMy08122012View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion
void CMy08122012View::OnDraw(CDC* pDC)
{
	CMy08122012Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(&rect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* oldBmp = memDC->SelectObject(&bmp);

	int oldGMode = memDC->SetGraphicsMode(GM_ADVANCED);

	CBrush whiteBrush;
	whiteBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush* oldBrush = memDC->SelectObject(&whiteBrush);

	memDC->Rectangle(0, 0, rect.Width(), rect.Height());
	memDC->SelectObject(oldBrush);

	DrawScene(memDC);
	//pDC->SetWorldTransform(&oldForm);
	//DrawGear(memDC,20,20);

	memDC->SetGraphicsMode(oldGMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	whiteBrush.DeleteObject();
	memDC->SelectObject(oldBmp);
	memDC->DeleteDC();
	delete memDC;

}
//Funkcije za zadatak
void CMy08122012View::DrawScene(CDC* pDC)
{
	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);


	Translate(pDC, midX, midY);
	DrawGear(pDC, 20, 20, midX, midY, midRot);
	pDC->SetWorldTransform(&oldForm);

	Translate(pDC, leftX, leftY);
	DrawGear(pDC, 10, 20, leftX,leftY,leftRot);
	pDC->SetWorldTransform(&oldForm);


	Translate(pDC, rightX, rightY);
	DrawGear(pDC, 10, 20, rightX, rightY, rightRot);
	pDC->SetWorldTransform(&oldForm);
	//Translate(pDC, 0, 0);
	//Rotate(pDC,midRot);

}
void CMy08122012View::Trapez(CDC* pDC,float a,float b, float h)
{
	CPoint pts[4];
	pts[0] = CPoint(-a/2,h/2); // gore levo
	pts[1] = CPoint(-b/2,-h/2); // dole levo
	pts[2] = CPoint(b/2,-h/2);  //dole desno
	pts[3] = CPoint(a/2,h/2);   // gore desno
	pDC->Polygon(pts, 4);
}
void CMy08122012View::DrawGear(CDC* pDC,int count,float width,int cx,int cy,float dAngle)
{
	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	float angleT = 360 /  (2*count); // ugao tetive
	//distance od centra kruga do centra trapeza,da bismo znali na kojoj distanci crtamo onu isprekidanu liniju
	float distance = width / tan(angleT  * (3.14 / 180));
	//float r = sqrt(distance*distance+(width/2)*(width/2));
	float r = distance + width/2; // distanca na kojoj ce da se nadje centar trapeza manjih

	CPen grayPen;
	grayPen.CreatePen(PS_DASH,1,RGB(200,200,200));
	CPen* oldPen = pDC->SelectObject(&grayPen);

	//pDC->Ellipse(-r, -r, r, r);
	pDC->SelectObject(oldPen);

	CPen bluePen;
	bluePen.CreatePen(PS_SOLID,2,RGB(0,0,255));
	oldPen = pDC->SelectObject(&bluePen);

	CBrush blueBrush;
	blueBrush.CreateSolidBrush(RGB(5,100,255));
	CBrush* oldBrush = pDC->SelectObject(&blueBrush);

	
	//nakon kruga,potrebno je nacrtati trapeze na vrhu
	float angle = 0;
	float tmpAngle = 360 / count;
	for (int i = 0; i < count; i++)
	{
		XFORM form;
		pDC->GetWorldTransform(&form);
		TranslateRotate(pDC, cx, cy, angle+dAngle , r - 2); // pozicionira od centra rotacije (-2 da bi priblizio,da lepse izgleda)
		Rotate(pDC,90); // da se zupcanik dobro okrene.
		//Translate(pDC, 0, 0); // skroz gore (prvi se crta na 12 sati)
		Trapez(pDC, 1.4 * width, width/1.4 , width);
		pDC->SetWorldTransform(&form);
		angle += tmpAngle;
	}
	pDC->Ellipse(-r + width / 2, -r + width / 2, r - width / 2, r - width / 2);


	pDC->Rectangle(-width/2,-width/2,width/2,width/2);


	CFont font;
	font.CreateFontW(count,0,0,0,0,0,0,0,0,0,0,0,0,(CString)"Arial");
	CFont* oldFont = pDC->SelectObject(&font);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER);

	CString broj; // da se odstampa broj zubaca
	broj.Format(_T("%d"),count);
	broj.Append((CString(" zubaca")));


	pDC->TextOutW(0, width / 2+5, broj);


	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

	grayPen.DeleteObject();
	bluePen.DeleteObject();
	blueBrush.DeleteObject();
	font.DeleteObject();
}

//transformacije
void CMy08122012View::Translate(CDC* pDC,float x,float y)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = x;
	form.eDy = y;
	pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
}
void CMy08122012View::Rotate(CDC* pDC, float angle)
{
	XFORM form;
	form.eM11 = cos((angle*3.14)/180);
	form.eM12 = sin((angle * 3.14) / 180);
	form.eM21 = -sin((angle * 3.14) / 180);
	form.eM22 = cos((angle * 3.14) / 180);
	form.eDx = 0;
	form.eDy = 0;
	pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
void CMy08122012View::TranslateRotate(CDC* pDC, float x, float y, float angle, float distance)
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

//AntiFlicker + Buttons
void CMy08122012View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	if (nChar == VK_UP)
	{
		leftRot += 4;
		midRot -= 2;
		rightRot += 4;
	}
	else if (nChar == VK_DOWN)
	{
		leftRot -= 4;
		midRot += 2;
		rightRot -= 4;
	}
	Invalidate();
}
BOOL CMy08122012View::OnEraseBkgnd(CDC* pDC)
{
	return false;
}
#pragma region .....
BOOL CMy08122012View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy08122012View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy08122012View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy08122012View::AssertValid() const
{
	CView::AssertValid();
}
void CMy08122012View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy08122012Doc* CMy08122012View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy08122012Doc)));
	return (CMy08122012Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion