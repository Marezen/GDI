#pragma once
#include "DImage.h"
//kreiramo novu klasu
class CMipMap 
{
public:	
	DImage *img;
	CMipMap(CString imageName);
	~CMipMap();
	CDC* DrawToDC(CDC *pDC, CRect rect);
	CDC* DrawMipMap(CDC *pDC, CRect rect, int x, int y, int size);
};

