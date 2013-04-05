// RightMapView.cpp : ʵ���ļ�
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


// CRightMapView ��ͼ

void CRightMapView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
	HDC      hdc    ;
	HBITMAP  m_hbmp  ;
	hdc    =  CreateCompatibleDC(pDC->m_hDC);
	m_hbmp =  (HBITMAP)LoadImage(::AfxGetInstanceHandle(),//
														  m_ImagePath, // m_ImagePath.GetBuffer(10), // m_ImagePath,//�ļ���
													      IMAGE_BITMAP,		//λͼ��ʽ
													      0,//ͼ�ο�
													      0,//ͼ�θ�
														  LR_LOADFROMFILE|LR_CREATEDIBSECTION//��ʽ
														  );

	SelectObject(hdc,m_hbmp);

	BitBlt(pDC->m_hDC,0,0,800,600, hdc,0,0,SRCCOPY);
}


// CRightMapView ���

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


// CRightMapView ��Ϣ�������
