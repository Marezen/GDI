#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "26.11.2018.h"
#endif
#include "26.11.2018Doc.h"
#include "26.11.2018View.h"
#include "DImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CMy26112018View, CView)
BEGIN_MESSAGE_MAP(CMy26112018View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CMy26112018View::CMy26112018View() noexcept
{
	napred_nazad = 0;

	bager = new DImage();
	arm1 = new DImage();
	arm2 = new DImage();
	pozadina = new DImage();
	bager->Load(CString("bager.png"));
	arm1->Load(CString("arm1.png"));
	arm2->Load(CString("arm2.png"));
	pozadina->Load(CString("pozadina.png"));
	viljuska = GetEnhMetaFile(CString("viljuska.emf"));

	ENHMETAHEADER heder;
	GetEnhMetaFileHeader(viljuska, sizeof(ENHMETAHEADER), &heder);
	rectViljuska.right = heder.rclBounds.right - heder.rclBounds.left;
	rectViljuska.bottom = heder.rclBounds.bottom - heder.rclBounds.top;
}
CMy26112018View::~CMy26112018View()
{
	delete bager;
	delete arm1;
	delete arm2;
	delete pozadina;
	DeleteEnhMetaFile(viljuska);
}
BOOL CMy26112018View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy26112018View::OnDraw(CDC* pDC)
{
	CMy26112018Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

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
	DrawBackground(memDC);
	DrawExcavator(memDC);
	//kraj crtanja

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),memDC,0,0,SRCCOPY);
	memDC->DeleteDC();
	delete memDC;
}
//Funkcije za zadatak
void CMy26112018View::DrawBackground(CDC* pDC)
{
	pozadina->Draw(pDC, CRect(0, 0, pozadina->Width(), pozadina->Height()), CRect(0, 0, rect.Width(), rect.Height()));
}
void CMy26112018View::DrawBody(CDC* pDC)
{
	Translate(pDC, rect.Width() - bager->Width(), rect.Height() - bager->Height(), false);
	Translate(pDC, napred_nazad, 0, false); // trasnlacija posebno za pomeranje
	bager->DrawTransparent(pDC, CRect(0, 0, bager->Width(), bager->Height()), CRect(0, 0, bager->Width(), bager->Height()));
}
void CMy26112018View::DrawArm1(CDC* pDC)
{
	Translate(pDC, 58, bager->Height() * 0.6, true); // malo na gore od pozicije gde je telo
	Rotate(pDC, -90, false); // da bi deblji deo stajao uspravno
	Rotate(pDC, ugao_Arm1, false); // poseban rotate za 
	arm1->DrawTransparent(pDC, CRect(0, 0, arm1->Width(), arm1->Height()), CRect(-58, -61, arm1->Width() - 58, 61));
}
void CMy26112018View::DrawArm2(CDC* pDC)
{
	//inic. se crta uspravno
	Rotate(pDC, 90, false); // rotira oko cetra tela, i pozicionira skroz gore
	Translate(pDC, 0, -bager->Height() + 50, false);
	Rotate(pDC, -180, false); // rotira da bi gornja ruka bila okrenuta na levo
	Rotate(pDC, ugao_Arm2, false);
	arm2->DrawTransparent(pDC, CRect(0, 0, arm2->Width(), arm2->Height()), CRect(-36, -40, arm2->Width() - 36, 40));
}
void CMy26112018View::DrawFork(CDC* pDC)
{
	Translate(pDC, arm2->Width()-61, 0, false); // pocinje od vrha arm1 , i onda za duzinu manje ruke se pomeri levo i jos 55 da bi dobro pozic.
	Rotate(pDC, -90, false); // potrebna rotacija viljuske da bi bila nadole
	Rotate(pDC, ugao_Viljuska, false); // a ovo je za dalju rotaciju
	Scale(pDC, 2.5, 2.5, false); // obaezan scale,jer je viljjuska dosta manja
	pDC->PlayMetaFile(viljuska, CRect(-14, -20, rectViljuska.right - 14, rectViljuska.bottom - 20));
}
void CMy26112018View::DrawExcavator(CDC* pDC)
{
	DrawBody(pDC);
	DrawArm1(pDC);
	DrawArm2(pDC);
	DrawFork(pDC);
}
//Transformacije
void CMy26112018View::Translate(CDC* pDC,float dx,float dy,bool right)
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
void CMy26112018View::Rotate(CDC* pDC,float angle,bool right)
{
	XFORM form;
	form.eM11 = cos(angle * 3.14 / 180);
	form.eM22 = cos(angle * 3.14 / 180);
	form.eM12 = sin(angle * 3.14 / 180);
	form.eM21 = -sin(angle * 3.14 / 180);
	form.eDx = 0;
	form.eDy = 0;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
void CMy26112018View::Scale(CDC* pDC,float dx,float dy,bool right)
{
	XFORM form;
	form.eM11 = dx;
	form.eM22 = dy;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eDx = 0;
	form.eDy = 0;
	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}
//AntiFlicker + Buttons
BOOL CMy26112018View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
void CMy26112018View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == '1')
	{
		ugao_Arm1 += 10.0;
		Invalidate();
	}
	if (nChar == '2')
	{
		ugao_Arm1 -= 10.0;
		Invalidate();
	}
	if (nChar == '3')
	{
		ugao_Arm2 += 10.0;
		Invalidate();
	}
	if (nChar == '4')
	{
		ugao_Arm2 -= 10.0;
		Invalidate();
	}
	if (nChar == '5')
	{
		ugao_Viljuska += 10.0;
		Invalidate();
	}
	if (nChar == '6')
	{
		ugao_Viljuska -= 10.0;
		Invalidate();
	}
	if (nChar == VK_LEFT)
	{
		napred_nazad -= 10.0;
		Invalidate();
	}
	if (nChar == VK_RIGHT)
	{
		napred_nazad += 10.0;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

#pragma region ...
BOOL CMy26112018View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy26112018View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}
void CMy26112018View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CMy26112018View::AssertValid() const
{
	CView::AssertValid();
}
void CMy26112018View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy26112018Doc* CMy26112018View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy26112018Doc)));
	return (CMy26112018Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion
