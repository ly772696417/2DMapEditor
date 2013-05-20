// RightMapView.cpp : 实现文件
//

#include "stdafx.h"
#include "2DMapEditor.h"
#include "RightMapView.h"
#include "MapEditorController.h"


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
	ON_WM_TIMER()
//	ON_WM_KEYDOWN()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
//ON_WM_MOUSELEAVE()
//ON_WM_MOUSEHOVER()
ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CRightMapView 绘图

void CRightMapView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
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


void CRightMapView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	
	m_isMouseDown = false;
	m_isSelcted = false;
	CRect rect;
	GetClientRect(rect);
	m_curMousePos = CPoint(rect.Width() * 0.5,rect.Height() * 0.5);
	m_downMousePos = CPoint(0,0);
	SetCursorPos(rect.Width() * 0.5,rect.Height() * 0.5);
	MapEditorControllerSingleton::Instance().m_myGame->Game_Init(this->GetSafeHwnd(),rect);
	
	m_micMapRect=CRect(rect.left,rect.bottom-MicMapSize-4,rect.left+MicMapSize,rect.bottom-4);
	this->SetTimer(1,40,NULL);
}


void CRightMapView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(rect);
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient( &point );
	if ( !PtInRect( &rect, point) ) 
	{
		m_isMouseLeave=true;
		MapEditorControllerSingleton::Instance().m_myGame->m_isMouseLeave=true;
		
	}else{
		m_isMouseLeave=false;
		MapEditorControllerSingleton::Instance().m_myGame->m_isMouseLeave=false;
		scrollScreen();
	}
	MapEditorControllerSingleton::Instance().m_myGame->Game_Run(m_isMouseDown,m_curMousePos,m_downMousePos);
	
	CView::OnTimer(nIDEvent);
}


void CRightMapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_downMousePos = point;
	m_isMouseDown = true;
	
	CRect rect;
	GetClientRect(rect);
	if (point.x>0 && point.x<MicMapSize && point.y>(rect.Height()-MicMapSize) && point.y<rect.bottom)
	{	
		MapEditorControllerSingleton::Instance().m_myGame->moveCameraTo(point-m_micMapRect.TopLeft());
	}
	//draw
	MapEditorController::EditorMode mode = MapEditorControllerSingleton::Instance().GetEditorMode();
	if (mode == MapEditorController::ModeBrush)
	{
		if (point.x>0 && point.x<MicMapSize && point.y>(rect.Height()-MicMapSize) && point.y<rect.bottom)
		{
			;
		}else
		MapEditorControllerSingleton::Instance().drawModel(point);
	}
	if (mode == MapEditorController::ModeSelection)
	{
		m_selRect.SetRect(point,point);
		m_isSelcted=true;	
		if (MapEditorControllerSingleton::Instance().CheackIsMove(point))
		{
			MapEditorControllerSingleton::Instance().SetModeMove();
			m_isSelcted=false;
		}
	}else{
		m_isSelcted=false;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CRightMapView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_isMouseDown = false;
	MapEditorControllerSingleton::Instance().m_myGame->setSelRect(false,m_selRect);
	if (m_isSelcted)
	{
		m_selRect.SetRect(m_selRect.TopLeft(),point);
		MapEditorControllerSingleton::Instance().CheackIsSel(m_selRect);
		m_isSelcted=false;
	}else{
		
	}
	CView::OnLButtonUp(nFlags, point);
}


void CRightMapView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_curMousePos = point;
	if (m_isMouseDown)
	{
		CRect rect;
		GetClientRect(rect);
		if (point.x>0 && point.x<MicMapSize && point.y>(rect.Height()-MicMapSize) && point.y<rect.bottom)
		{			
			MapEditorControllerSingleton::Instance().m_myGame->moveCameraTo(point-m_micMapRect.TopLeft());
		}
	}
	if (m_isMouseDown && m_isSelcted)
	{
		m_selRect.SetRect(m_selRect.TopLeft(),point);
		MapEditorControllerSingleton::Instance().m_myGame->setSelRect(true,m_selRect);
	}else{
		MapEditorControllerSingleton::Instance().m_myGame->setSelRect(false,m_selRect);
	}

	MapEditorController::EditorMode mode=MapEditorControllerSingleton::Instance().GetEditorMode();
	if (mode=MapEditorController::ModeMove)
	{

	}
	CView::OnMouseMove(nFlags, point);
}

bool CRightMapView::scrollScreen()
{
	MapData * mapData=MapEditorControllerSingleton::Instance().GetMapData();
	CPoint mapOffest=mapData->GetOffest();
	CRect m_winRect;
	GetClientRect(m_winRect);
	if (m_curMousePos.x>m_winRect.Width()-50 && m_curMousePos.x<m_winRect.Width()
		&& m_curMousePos.y>10 && m_curMousePos.y<m_winRect.Height()-10 
		&& mapOffest.x<BlockSize*mapData->getWidth()-m_winRect.Width())
	{
		g_dscrollx+=10.0;
		if(g_dscrollx>m_winRect.Width())
			g_dscrollx=0;
		mapOffest.x+=10.0;

	}
	if (m_curMousePos.y>m_winRect.Height()-70 && m_curMousePos.y<m_winRect.Height()-10 
		&& m_curMousePos.x>MicMapSize && mapOffest.y<BlockSize*mapData->getHeight()-m_winRect.Height())
	{
		g_dscrolly+=10.0;
		if(g_dscrolly>m_winRect.Height())
			g_dscrolly=0;
		mapOffest.y+=10;
	}
	if (m_curMousePos.x>10 && m_curMousePos.x<50 && m_curMousePos.y>m_winRect.top 
		&& m_curMousePos.y<m_winRect.Height()-MicMapSize && mapOffest.x>0)
	{
		g_dscrollx-=10.0;
		if(g_dscrollx<0)
			g_dscrollx=m_winRect.Width();
		mapOffest.x-=10;
	}
	if (m_curMousePos.x>10 && m_curMousePos.x<m_winRect.Width()
		&& m_curMousePos.y>10 && m_curMousePos.y <50 && mapOffest.y>0)
	{
		g_dscrolly-=10.0;
		if(g_dscrolly<0)
			g_dscrolly=m_winRect.Height();
		mapOffest.y-=10;
	}

	mapData->SetOffest(mapOffest,m_winRect);
	return true;
}




void CRightMapView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MapEditorController::EditorMode mode = MapEditorControllerSingleton::Instance().GetEditorMode();
	if (mode==MapEditorController::ModeBrush)
	{
		MapEditorControllerSingleton::Instance().SetModeSelection();
	}

	CView::OnRButtonDown(nFlags, point);
}
