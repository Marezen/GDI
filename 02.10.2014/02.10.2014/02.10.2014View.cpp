#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "02.10.2014.h"
#endif
#include "02.10.2014Doc.h"
#include "02.10.2014View.h"
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy02102014View, CView)

BEGIN_MESSAGE_MAP(CMy02102014View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CMy02102014View::CMy02102014View() noexcept
{
}
CMy02102014View::~CMy02102014View()
{
}
BOOL CMy02102014View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}


#pragma endregion
void CMy02102014View::OnDraw(CDC* pDC)
{
	CMy02102014Doc* pDoc = GetDocument();
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

	int values[8] = { 1,2,3,4,5,6,7,8 };
	DrawTree(memDC,values,8,80,60,30,RGB(255,255,0),RGB(255,0,0));


	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;
}
//Funkcije za zadatak:
void CMy02102014View::DrawTree(CDC* pDC, int values[], int n, int dHor, int dVer, int rad, COLORREF colNode, COLORREF colLine)
{
	//dHor - razmak izmedju cvora,najnizi nivo,znaci za nivo iznad je duplo
	//dVer - razmak izmedju nivoa,uvek isti
	//rad - poluprecnik elipsi
	//n broj cvora
	//values  vrednosti cvoorva,krene od 1 pa navise
	//boja veze
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(192, 192, 192));
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(colNode);
	CBrush* oldBrush = pDC->SelectObject(&brush);

	CFont font;
	font.CreateFontW(25, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, CString("Arial"));

	UINT flags = pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);
	int prevMode = pDC->SetBkMode(TRANSPARENT);
	CFont* oldFont = pDC->SelectObject(&font);
	//boja veze
	CPen relPen;
	relPen.CreatePen(PS_SOLID, 3, colLine);
	
	int x, y;
	int leviX,desniX,leviY,desniY;
	int brCvoraNivoa;
	int visinaStabla = log2(n + 1); // toliko nivoa ima
	int nivo;
	x = 300;
	y = 100;
	int oldX = 0;
	int oldY = 0;
	int brojac = values[0];
	CString a;
	Translate(pDC, x, y, true);

	int rastojanje = dHor;
	for (int i = 0; i < visinaStabla; i++)
	{
		if (i == 0) // onda jedan cvor
		{
			
			pDC->Ellipse(-rad,-rad,rad,rad);


			a.Format(_T("%d"), brojac);
			pDC->TextOutW(0, 0, CString(a));
			brojac++;
		}
		else
		{
			brCvoraNivoa = i * 2; // odredi broj cvorova
			//odredi razmak izmedju cvorova zavisno od nivoa
			if (i != visinaStabla - 1)
			{
				rastojanje += i * dHor;
			}
			else
				rastojanje = dHor;
			//sada od prethodne pozicije,treba da se pomeri dole levo
			for (int j=1;j<=brCvoraNivoa;j++)
			{
				//levi
				if (j%2==1)
				{
					//potrebna jedna transformacija da bi crtalo na levo,ali nisam uspeo da napravim
					//Translate(pDC,oldX,oldY,true);
					x =-rastojanje / 2;
					y = dVer;
					pDC->SelectObject(&relPen);
					pDC->MoveTo(0,0);
					Translate(pDC,x,y,true);
					leviX = x;
					leviY = y;
					pDC->LineTo(-x,-y);
					pDC->SelectObject(&pen);
					pDC->Ellipse(-rad,-rad,rad,rad);
					a.Format(_T("%d"), brojac);
					pDC->TextOutW(0, 0, CString(a));
					brojac++;
				}
				else
				{
					x = rastojanje;
					y = 0;
					pDC->SelectObject(&relPen);
					pDC->MoveTo(0, 0);
					Translate(pDC,x,y,true);
					pDC->LineTo(-rastojanje/2, y-dVer);
					pDC->SelectObject(&pen);
					pDC->Ellipse(-rad, -rad, rad, rad);
					a.Format(_T("%d"), brojac);
					pDC->TextOutW(0, 0, CString(a));
					brojac++;
				}
			}
		}
	}
	pDC->SetTextAlign(flags);
	pDC->SetBkMode(prevMode);
	font.DeleteObject();
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pen.DeleteObject();
	relPen.DeleteObject();
}
//transformacije
void CMy02102014View::Translate(CDC* pDC, float dx, float dy, bool right)
{
	XFORM form;
	form.eM11 = 1;
	form.eM22 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eDx = dx;
	form.eDy = dy;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}


#pragma region .....
BOOL CMy02102014View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy02102014View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy02102014View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy02102014View::AssertValid() const
{
	CView::AssertValid();
}
void CMy02102014View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy02102014Doc* CMy02102014View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy02102014Doc)));
	return (CMy02102014Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion