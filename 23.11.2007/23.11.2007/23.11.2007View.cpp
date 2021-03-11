#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "23.11.2007.h"
#endif
#include "23.11.2007Doc.h"
#include "23.11.2007View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy23112007View, CView)

BEGIN_MESSAGE_MAP(CMy23112007View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CMy23112007View::CMy23112007View() noexcept
{
	router = new DImage();
	pos = 100;
}
CMy23112007View::~CMy23112007View()
{
	delete router;
}
BOOL CMy23112007View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy23112007View::OnDraw(CDC* pDC)
{
	CMy23112007Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(&rect);
	//zadato u zadatku
	CPoint points[2] = { CPoint(100, 100), CPoint(200, 200) };
	DrawRouters(pDC,points,2); // 2 rutera iscrtamo
	DrawSerialLink(pDC,points[0],points[1]);
	DrawPacket(pDC,CPoint(200,50),20);
	DrawMessage(pDC, points[0], points[1], pos, CSize(40, 20));
}

//funkcije za zadatak:
void CMy23112007View::DrawRouters(CDC* pDC, CPoint* pts, int count)
{
	router->Load((CString)"Ruter.jpg");
	int width = router->Width();
	int height = router->Height();

	//count - broj rutera
	for (int i = 0; i < count; i++)
	{
		//Rectangle u kome se nalazi slika
		CRect result(pts[i].x-width/2,pts[i].y-height/2,pts[i].x + width/2,pts[i].y+height/2);
		router->Draw(pDC,CRect(0,0,width,height),result);
	}

}
void CMy23112007View::DrawSerialLink(CDC* pDC,CPoint pt1,CPoint pt2)
{
	HENHMETAFILE link = GetEnhMetaFile(CString("Link2.emf"));

	//formiramo rectangle u kome ce biti nacrtano
	CRect rect(-(pt2.x-pt1.x)/2,-10,(pt2.y-pt1.y)/2,10);


	int prevMode = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM form, oldXForm;
	pDC->GetWorldTransform(&oldXForm);

	//ugao na osnovu rastojanja
	double a = atan2((double)(pt2.y - pt1.y), (double)(pt2.x - pt1.x));
	form.eM11 = cos(a);
	form.eM12 = sin(a);
	form.eM21 = -sin(a);
	form.eM22 = cos(a);
	form.eDx = pt1.x+(pt2.x - pt1.x) / 2;
	form.eDy = pt1.y+(pt2.y - pt1.y) / 2;

	//primenimo transformaciju
	pDC->SetWorldTransform(&form);
	pDC->PlayMetaFile(link,&rect);
	pDC->SetWorldTransform(&oldXForm);
	pDC->SetGraphicsMode(prevMode);

	DeleteEnhMetaFile(link);

}
void CMy23112007View::DrawPacket(CDC* pDC,CPoint pt,int h)
{
	int prevMode = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM form, oldForm;
	pDC->GetWorldTransform(&oldForm);
	//centar pravougaonika
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = pt.x - 8 * h;
	form.eDy = pt.y - 0.5 * h;
	pDC->SetWorldTransform(&form);

	CBrush brush; // zuta ispuna
	brush.CreateSolidBrush(RGB(255,255,0)); 
	CBrush* oldBrush = pDC->SelectObject(&brush);

	pDC->Rectangle(0,0,4*h,h); // od 0 do 8
	pDC->Rectangle(4 * h, 0, 8 * h, h); //od 8 do 16
	pDC->Rectangle(8*h,0,16*h,h);      // od 16 do 32

	//nakon toga ubacujemo tekstove unutar pravougaonika
	CFont font;
	font.CreateFontW(0.8*h,0,0,0,0,0,0,0,0,0,0,0,0,(CString)"Arial");
	CFont* oldFont = pDC->SelectObject(&font);

	int prevBkMode = pDC->SetBkMode(TRANSPARENT);

	CSize ext;
	ext = pDC->GetTextExtent(CString("Type: 0x8"));
	pDC->TextOutW(2*h-ext.cx/2,0.1*h,CString("Type: 0x8"));
	ext = pDC->GetTextExtent(CString("Code: 0x0"));
	pDC->TextOutW(6* h - ext.cx/2, 0.1 * h, CString("Code: 0x0"));
	ext = pDC->GetTextExtent(CString("Checksum: 0x2F41"));
	pDC->TextOutW(12 * h - ext.cx / 2, 0.1 * h, CString("Checksum: 0x2F41"));

	ext = pDC->GetTextExtent(CString("0"));
	pDC->TextOutW(0-ext.cx/2,-h,CString("0"));
	ext = pDC->GetTextExtent(CString("8"));
	pDC->TextOutW(4*h - ext.cx / 2, -h, CString("8"));
	ext = pDC->GetTextExtent(CString("16"));
	pDC->TextOutW(8*h - ext.cx / 2, -h, CString("16"));
	ext = pDC->GetTextExtent(CString("32"));
	pDC->TextOutW(16*h - ext.cx / 2, -h, CString("32"));

	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
}
void CMy23112007View::DrawMessage(CDC* pDC,CPoint p1,CPoint p2,int pos,CSize size)
{
	int prevMode = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM form, oldXForm;
	pDC->GetWorldTransform(&oldXForm);

	//ugao na osnovu rastojanja
	double a = atan2((double)(p2.y - p1.y), (double)(p2.x - p1.x));
	form.eM11 = cos(a);
	form.eM12 = sin(a);
	form.eM21 = -sin(a);
	form.eM22 = cos(a);
	form.eDx = p1.x;
	form.eDy = p1.y;

	pDC->SetWorldTransform(&form);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,0));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	//velicina 
	int cx = size.cx;
	int cy = size.cy;
	//rastojanje tacaka u koordinatnom sistemu
	int d = sqrt((double)((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)))-cx; // ovo "-cx" da se pozicionira na tacku 2,kao na slici

	pDC->Rectangle(d*pos/100,-cy,d*pos/100+cx,0);
	pDC->MoveTo(d*pos/100,-cy); // od gore levo
	pDC->LineTo(d*pos/100 + cx/2,-cy/2); // povuce ka centru
	pDC->MoveTo(d*pos/100 + cx/2,-cy/2);
	pDC->LineTo(d*pos/100 + cx,-cy);

	pDC->SetWorldTransform(&oldXForm);
	pDC->SetGraphicsMode(prevMode);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
}
//Button;
void CMy23112007View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'Q')
	{
		pos -= 5;
	}
	else if(nChar == 'W')
	{
		pos += 5;
	}
	//da ne predje drugu tacku
	if (pos>100)
	{
		pos = 100;
	}
	//da ne predje prvu tacku
	if(pos<0)
	{
		pos = 0;
	}
	this->Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
#pragma region ....
BOOL CMy23112007View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy23112007View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}
void CMy23112007View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy23112007View::AssertValid() const
{
	CView::AssertValid();
}
void CMy23112007View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy23112007Doc* CMy23112007View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy23112007Doc)));
	return (CMy23112007Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion