// RightMapView.cpp : 实现文件
//

#include "stdafx.h"
#include "2DMapEditor.h"
#include "RightMapView.h"


// CRightMapView

CRightMapView* CRightMapView::m_pSingleton=NULL;


CString   m_ImagePath;

IMPLEMENT_DYNCREATE(CRightMapView, CView)

CRightMapView::CRightMapView()
{
	m_pSingleton = this;
}

CRightMapView::~CRightMapView()
{
}

BEGIN_MESSAGE_MAP(CRightMapView, CView)
END_MESSAGE_MAP()


// CRightMapView 绘图

void CRightMapView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
	HDC      hdc    ;
	HBITMAP  m_hbmp  ;
	hdc    =  CreateCompatibleDC(pDC->m_hDC);
	m_hbmp =  (HBITMAP)LoadImage(::AfxGetInstanceHandle(),//
														  m_ImagePath, // m_ImagePath.GetBuffer(10), // m_ImagePath,//文件名
													      IMAGE_BITMAP,		//位图方式
													      0,//图形宽
													      0,//图形高
														  LR_LOADFROMFILE|LR_CREATEDIBSECTION//方式
														  );

	SelectObject(hdc,m_hbmp);

	BitBlt(pDC->m_hDC,0,0,800,600, hdc,0,0,SRCCOPY);
}


// CRightMapView 诊断

#ifdef _DEBUG
void CRightMapView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightMapView 消息处理程序
