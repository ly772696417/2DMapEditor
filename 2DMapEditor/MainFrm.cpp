
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "2DMapEditor.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_UNDO, &CMainFrame::OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, &CMainFrame::OnEditRedo)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

/*	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));*/

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式


	cs.style |= WS_MAXIMIZE;
	cs.style &= ~FWS_ADDTOTITLE;
	cs.style &= ~WS_MAXIMIZEBOX;

	cs.lpszName = "2D地图编辑器";

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(!m_splitter.CreateStatic(this,1,2)){
		TRACE0("Failed to Create Static Splitter.");
		return FALSE;
	}

	CRect rect;
	GetWindowRect(&rect);

	if(!m_splitter.CreateView(0,0,RUNTIME_CLASS(CLeftTreeView),CSize(rect.Width() * 0.25,rect.Height()),pContext)){
		TRACE0("Failed to create left tree view.");
		return FALSE;
	}

	if(!m_splitter.CreateView(0,1,RUNTIME_CLASS(CRightMapView),CSize(rect.Width()* 0.75,rect.Height()),pContext)){
		TRACE0("Failed to create right tree view.");
		return FALSE;
	}

	m_leftTreeView = (CLeftTreeView*)m_splitter.GetPane(0,0);
	m_rightMapView = (CRightMapView *)m_splitter.GetPane(0,1);

	SetActiveView((CView *)m_splitter.GetPane(0,0));

	m_splitter.ShowWindow(SW_SHOW);
	m_splitter.UpdateWindow();

	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnEditUndo()
{
	// TODO: 在此添加命令处理程序代码
	MapEditorControllerSingleton::Instance().Undo();
}


void CMainFrame::OnEditRedo()
{
	// TODO: 在此添加命令处理程序代码
	MapEditorControllerSingleton::Instance().Redo();
}
