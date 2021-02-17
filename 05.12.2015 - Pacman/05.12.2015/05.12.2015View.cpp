#pragma region fiksno
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "05.12.2015.h"
#endif
#include "05.12.2015Doc.h"
#include "05.12.2015View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy05122015View, CView)

BEGIN_MESSAGE_MAP(CMy05122015View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CMy05122015View::CMy05122015View() noexcept
{
	pozadina = new DImage();
	pozadina->Load(CString("blue.png")); // ucitava se jednom,a crta vise puta
	pomX = 400;
	pomY = 300; // na 400 mnogo dole mi nacrta
	stanjeUsta = true; // otvorena inicijalno..
	desno = true;
	gore = false;
	kraj = false;
	pacmanP = 48;
	eyeP = 4;

}
CMy05122015View::~CMy05122015View()
{
}
BOOL CMy05122015View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion
void CMy05122015View::OnDraw(CDC* pDC)
{
	CMy05122015Doc* pDoc = GetDocument();
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
	memDC->SetWindowExt(rect.right, rect.bottom);
	memDC->SetViewportExt(rect.right, rect.bottom);
	memDC->Rectangle(0, 0, rect.right, rect.bottom);
	//crtanje
	NacrtajScenu(memDC, rect);
	//kraj crtannja
	pDC->BitBlt(0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	bmp.DeleteObject();
	delete memDC;
}
//funkcije za zadatak:
void CMy05122015View::NacrtajScenu(CDC* pDC,CRect rect)
{
	NacrtajPozadinu(pDC, rect);
	CRect r(100, 120, 196, 216); // Rectangle u kome se crta duh
	//pDC->Rectangle(400, 300, 496, 396); // HITBOX
	//Moramo imati transformacije
	XFORM f;
	int oldMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->GetWorldTransform(&f);
	Transform(pDC, rect, 100, 100, 0, 0, 0, 0, false); // pozicija duha na 100,100  -> bez rotacije
	pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
	DrawGhost(pDC, r);
	pDC->SetWorldTransform(&f);
	SetGraphicsMode(pDC->m_hDC, oldMode);

	float ugao;
	if (gore)
		ugao = 90;
	else
		ugao = 0;

	oldMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->GetWorldTransform(&f);
	Transform(pDC, rect, pomX, pomY, 0, 0, ugao, 0, !desno);
	pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);

	if (stanjeUsta)
		DrawPacman(pDC, rect, 20);
	else
		DrawPacman(pDC, rect, 1);
	stanjeUsta = !stanjeUsta;
	pDC->SetWorldTransform(&f);
	SetGraphicsMode(pDC->m_hDC, oldMode);

	//nakon crtanja pacman-a,treba proveriti da li je dotakao duha:
	if (kraj)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetTextAlign(TA_CENTER);

		CFont font;
		font.CreateFont(72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));
		pDC->SelectObject(&font);

		pDC->TextOut(rect.CenterPoint().x, rect.CenterPoint().y, CString("The End!!!"));
		font.DeleteObject();
	}


}
void CMy05122015View::NacrtajPozadinu(CDC* pDC, CRect rect)
{
	pozadina->Draw(pDC, CRect(0, 0, pozadina->Width(), pozadina->Height()), CRect(0, 0, rect.right, rect.bottom));
}
void CMy05122015View::DrawPacman(CDC* pDC,CRect rect,float angle)
{
	CPen blackPen; // za oblik
	blackPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	CPen* oldPen = pDC->SelectObject(&blackPen);

	CBrush yellowBrush; // za telo
	yellowBrush.CreateSolidBrush(RGB(255, 255, 0));

	CBrush blackBrush; // za oko
	blackBrush.CreateSolidBrush(RGB(0,0,0));

	CBrush* oldBrush = pDC->SelectObject(&yellowBrush); // uzimamo zutu

	//koordinate pacmana
	double x = pacmanP - pacmanP * cos(angle * 3.14 / 180);
	double y = pacmanP *  sin(angle*3.14/180);
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->Pie(-pacmanP, -pacmanP, pacmanP, pacmanP, pacmanP - x, - y, pacmanP - x,y);

	pDC->SelectObject(blackBrush);
	pDC->Ellipse(eyeP+eyeP/2, -pacmanP + eyeP, +pacmanP / 2 - eyeP , -pacmanP / 2 - eyeP);
	pDC->SelectObject(&oldPen);
	pDC->SelectObject(&oldBrush);
	blackPen.DeleteObject();
	yellowBrush.DeleteObject();
	blackBrush.DeleteObject();
}
void CMy05122015View::DrawGhost(CDC* pDC, CRect rect)
{
	int max = 106;
	int min = 10;
	//Boja duha:
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 0, 0));
	CBrush* oldBrush = pDC->SelectObject(&brush);
	//ivice
	CPen pen;
	pen.CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);

	// Mora da se primeni sa Putanjom
	int p = 16;
	int x;
	pDC->MoveTo(10, 42);

	pDC->BeginPath();
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(min, min, max, max, min, 42, max, 42);
	pDC->LineTo(max, max); // dole desno
	pDC->ArcTo(max - p / 2, max - p, max + p / 2, max, max, max, max - p / 2, max - p / 2);
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	x = max - p / 2;
	for (int i = 0; i < 5; i++) // pet manjih(donji deo duha)
	{
		if (i % 2 == 0)
			pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
		else
			pDC->SetArcDirection(AD_CLOCKWISE);
		pDC->ArcTo(x - p, max - p, x, max, x, max - p / 2, x - p, max - p / 2);
		x -= 16;
	}
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(x - p, max - p, x, max, x, max - p / 2, x - p / 2, max);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	NacrtajOko(48, pDC, rect);
	NacrtajOko(78, pDC, rect);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}
void CMy05122015View::NacrtajOko(int pomeraj, CDC* pDC, CRect& rect)
{
	//Beonjaca
	CBrush whiteBrush;
	whiteBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush* oldBrush = pDC->SelectObject(&whiteBrush);

	pDC->Ellipse(pomeraj, 35, pomeraj+20, 58);

	//Zenica
	CBrush blueBrush;
	blueBrush.CreateSolidBrush(RGB(15, 20, 255));
	pDC->SelectObject(&blueBrush);
	pDC->Ellipse(pomeraj+5, 40, pomeraj+20, 53); //pomeraj + 5, da se skupi zenica po vertikali
	pDC->SelectObject(oldBrush);
	blueBrush.DeleteObject();
	whiteBrush.DeleteObject();
}

//funkcije trasnformacije
void CMy05122015View::Translate(CDC* pDC,float x,float y)
{
	XFORM f;
	f.eM11 = 1;
	f.eM12 = 0;
	f.eM21 = 0;
	f.eM22 = 1;
	f.eDx = x;
	f.eDy = y;
	pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
}
void CMy05122015View::Rotate(CDC* pDC, float angle)
{
	XFORM f;
	f.eM11 = cos((angle*3.14)/180);
	f.eM12 = sin((angle * 3.14) / 180);
	f.eM21 = -sin((angle * 3.14) / 180);
	f.eM22 = cos((angle * 3.14) / 180);
	f.eDx = 0;
	f.eDy = 0;
	pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
}
void CMy05122015View::Mirror(CDC* pDC)
{
	XFORM f;
	f.eM11 = -1;
	f.eM12 = 0;
	f.eM21 = 0;
	f.eM22 = 1;
	f.eDx = 0;
	f.eDy = 0;
	pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
}
void CMy05122015View::Scale(CDC* pDC, float scale)
{
	XFORM f;
	f.eM11 = scale;
	f.eM12 = 0;
	f.eM21 = 0;
	f.eM22 = scale;
	f.eDx = 0;
	f.eDy = 0;
	pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
}
void CMy05122015View::Transform(CDC* pDC, CRect rect, int cx, int cy, int x, int y, double angle, double scale, bool mirror)
{
	Scale(pDC, scale);
	if (mirror)
		Mirror(pDC);
	Translate(pDC,x, y);
	Rotate(pDC, angle);
	Translate(pDC,cx, cy); // oko centra da rotira
}
//Buttons + AntiFlicker
void CMy05122015View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!kraj)
	{
		switch (nChar)
		{
		case VK_UP:
			pomY -= 10;
			gore = true;
			desno = false;
			break;
		case VK_DOWN:
			pomY += 10;
			gore = true;
			desno = true;
			break;
		case VK_RIGHT:
			pomX += 10;
			gore = false;
			desno = true;
			break;
		case VK_LEFT:
			pomX -= 10;
			gore = false;
			desno = false;
			break;
		}
	}
	int x = pomX - 148;
	int y = pomY - 148;
	if (x < 0)
		x = -x;
	if (y < 0)
		y = -y;
	if (x < 96 && y < 96)
		kraj = true;
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
BOOL CMy05122015View::OnEraseBkgnd(CDC* pDC)
{
	return true;
}
#pragma region ....
BOOL CMy05122015View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy05122015View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{}
void CMy05122015View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{}
#ifdef _DEBUG
void CMy05122015View::AssertValid() const
{
	CView::AssertValid();
}
void CMy05122015View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy05122015Doc* CMy05122015View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy05122015Doc)));
	return (CMy05122015Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion