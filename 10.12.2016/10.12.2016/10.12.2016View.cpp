#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "10.12.2016.h"
#endif
#include "10.12.2016Doc.h"
#include "10.12.2016View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy10122016View, CView)

BEGIN_MESSAGE_MAP(CMy10122016View, CView)

	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CMy10122016View::CMy10122016View() noexcept
{
	table = new DImage();
	frame = new DImage();
	table->Load(CString("felt2.jpg"));
	frame->Load(CString("wood.jpg"));
	angle = 220;
	stickX = 60;
	stickY = 80;
	ballAngle = 0;
	ballX = 0;
	ballY = 0;
	ballR = 30;
	stick =true; // indikator ,da li je vec stap udario lopticu
	
}
CMy10122016View::~CMy10122016View()
{
	delete table;
	delete frame;
}
BOOL CMy10122016View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy10122016View::OnDraw(CDC* pDC)
{
	CMy10122016Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(rect);

	CDC* memDC = new CDC();;
	memDC->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(&bmp);

	memDC->SetWindowExt(rect.right, rect.bottom);
	memDC->SetViewportExt(rect.right, rect.bottom);
	memDC->Rectangle(0, 0, rect.Width(), rect.Height());

	//crtanj scene
	DrawScene(memDC, rect, 30);
	//kraj crtanja scene
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	bmp.DeleteObject();
	memDC->DeleteDC();
	delete memDC;
}
//Funkcije za zadatak:
void CMy10122016View::DrawScene(CDC* pDC,CRect rect,int size) 
{
	DrawBorder(pDC, rect, size);

	XFORM form;
	int oldMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->GetWorldTransform(&form);

	//pozicioniranje loptice
	Transform(pDC,400,250,ballX,-ballY,ballAngle);

	pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	DrawBall(pDC, 30);
	pDC->SetWorldTransform(&form);
	SetGraphicsMode(pDC->m_hDC, oldMode);

	//crtanje stapa
	oldMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->SetGraphicsMode(GM_ADVANCED);
	pDC->GetWorldTransform(&form);
	//pozicioniranje stapa
	Transform(pDC,400,250,0,-stickY,angle); 

	pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	DrawStick(pDC, 500);
	pDC->SetWorldTransform(&form);
	SetGraphicsMode(pDC->m_hDC, oldMode);

	DrawHoles(pDC,rect,size);
}
void CMy10122016View::DrawBorder(CDC* pDC, CRect rect, int w)
{
	//vise puta nacrta sliku felt2.jpg
	//dokle god ne dodje do rect.Height() i rect.Height() ,crta sliku , i onda pomeri za width
	int x = 0; // pocne od tacke gore levo
	int y = 0;
	while (y <= rect.Height())
	{
		//crta s leva na desno 
		x = 0;
		while (x <= rect.Width())
		{
			table->Draw(pDC, CRect(0, 0, table->Width(), table->Height()), CRect(x, y, table->Width() + x, table->Height() + y));
			x += table->Width();//pomeri za sliku za table->Width()
			// i onda crta dokle god ne nacrta jedan ceo red slika
		}
		//posle toga predje ispod red
		y += table->Height();
	}
	//Nakon toga je potrebno da nacrtamo okvir.. 
	// OKVIR crtamo tak osto cemo formirati region.

	CRgn unutrasnjost;
	unutrasnjost.CreateRectRgn(0 + w, 0 + w, rect.Width() - w, rect.Height() - w);
	pDC->SelectClipRgn(&unutrasnjost, RGN_DIFF); // region je obuhvatio zeleni deo,ali zato ide RGN_DIFF da nacrta frame svuda osim tu
	frame->Draw(pDC, CRect(0, 0, frame->Width(), frame->Height()), CRect(0, 0, rect.Width(), rect.Height()));
	pDC->SelectClipRgn(NULL);
	unutrasnjost.DeleteObject();
}
void CMy10122016View::DrawStick(CDC* pDC,int w)
{
	//Crtamo prvo duzi i svetliji deo
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush svetliBrush;
	svetliBrush.CreateSolidBrush(RGB(255,255,225));
	CBrush* oldBrush = pDC->SelectObject(&svetliBrush);

	CPoint svetliDeo[4];
	svetliDeo[0] = CPoint(-2.5,0);
	svetliDeo[1] = CPoint(2.5,0);
	svetliDeo[2] = CPoint(5,-w*2/3);
	svetliDeo[3] = CPoint(-5,-w*2/3);
	pDC->Polygon(svetliDeo,4);

	//Sada tamniji deo:
	CBrush tamnijiBrush;
	tamnijiBrush.CreateSolidBrush(RGB(100,50,0));
	//selektujemo novi brush
	pDC->SelectObject(&tamnijiBrush);

	CPoint tamnijiDeo[4];
	tamnijiDeo[0] = CPoint(-5, -w*2/3);
	tamnijiDeo[1] = CPoint(5, -w*2/3);
	tamnijiDeo[2] = CPoint(10, -w);
	tamnijiDeo[3] = CPoint(-10, -w);
	pDC->Polygon(tamnijiDeo, 4);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	svetliBrush.DeleteObject();
	tamnijiBrush.DeleteObject();
	pen.DeleteObject();
}
void CMy10122016View::DrawBall(CDC* pDC,int w)
{
	//1 olovka i 2 cetkice
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush redBrush;
	redBrush.CreateSolidBrush(RGB(250, 0, 0));
	CBrush* oldBrush = pDC->SelectObject(&redBrush);
	//kugla
	pDC->Ellipse(-w / 2, -w / 2, w / 2, w / 2);

	CBrush whiteBrush;
	whiteBrush.CreateSolidBrush(RGB(255,255,255));
	pDC->SelectObject(&whiteBrush);
	//unutrasnja elipsa()
	pDC->Ellipse(0,0,w/3,-w/3);
	//manji

	pDC->SelectObject(&oldPen);
	pDC->SelectObject(&oldBrush);
	pen.DeleteObject();
	redBrush.DeleteObject();
	whiteBrush.DeleteObject();
}
void CMy10122016View::DrawHoles(CDC* pDC,CRect rect,int size)
{
	//30 jer zeleni deo pocinje od (30,30)
	DrawHole(pDC,rect,size,size,size); // gore levo
	DrawHole(pDC, rect, size, size, rect.Height() - size); // dole levo
	DrawHole(pDC,rect,size,rect.Width()/2,size); // srednja gore
	DrawHole(pDC,rect,size,rect.Width()/2,rect.Height() - size); // srednja dole
	DrawHole(pDC, rect, size, rect.Width() - size, size); // gore desno
	DrawHole(pDC,rect,size,rect.Width()-size,rect.Height()-size); // dole desno
}
void CMy10122016View::DrawHole(CDC* pDC, CRect rect, int size, int x, int y)
{
	//Olovka i cetkica:
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,0));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	//da bismo mogli da pozicioniramo rupu
	XFORM f;
	pDC->SetGraphicsMode(GM_ADVANCED);
	pDC->GetWorldTransform(&f);

	//pre nego sto nacrtamo elipsu potrebno je da odredimo poziciju:
	Transform(pDC,x-size/2,y-size/2,0,0,0);
	pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
	pDC->Ellipse(0, 0, size, size);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pen.DeleteObject();

	pDC->SetWorldTransform(&f);

}
//Funkcija za transformacije:
void CMy10122016View::Translate(CDC* pDC,float x,float y,bool right)
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
void CMy10122016View::Rotate(CDC* pDC,float angle,bool right)
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
void CMy10122016View::Reset(CDC *pDC)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = 0;
	form.eDy = 0;
	pDC->SetWorldTransform(&form);
}
void CMy10122016View::Transform(CDC* pDC, float x, float y, float cx, float cy, float angle)
{
	Reset(pDC);
	Translate(pDC, cx, cy,true);
	Rotate(pDC, angle,true);
	Translate(pDC, x, y,true);
}
//AntiFlicker + Buttons:
void CMy10122016View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_LEFT:
		angle += 5;
		if (angle>=360)
		{
			angle = 0;
		}
		break;
	case VK_RIGHT:
		angle -= 5;
		if (angle <= -360)
			angle = 0;
		break;
	case VK_UP:
		if (stick)
		{
			stickY -= 5;
			if (stickY < ballR)
			{
				stick = false;
				ballAngle = angle;
			}
		}
		else
		{//ako je stap udario lopticu,loptica pocinje da se pomera,a stap ostaje u mestu
			ballY -= 5;
		}
		break;
	case VK_DOWN:
		if (stick)
		{
			//povlaci unazad
			stickY += 5;
			if (stickY > 105)
				stickY = 500;
		}
		else
		{
			//loptica se vraca unazad
			ballY += 5;
			if (ballY >= 0) // ako stane na pocetno mesto, pocinje stap da se mrda
			{
				ballY = 0;
				stick = true;
				ballAngle = angle;
			}
		}
		break;
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
BOOL CMy10122016View::OnEraseBkgnd(CDC* pDC)
{
	return true;
}



#pragma region .....
BOOL CMy10122016View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy10122016View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}
void CMy10122016View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy10122016View::AssertValid() const
{
	CView::AssertValid();
}
void CMy10122016View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy10122016Doc* CMy10122016View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy10122016Doc)));
	return (CMy10122016Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion