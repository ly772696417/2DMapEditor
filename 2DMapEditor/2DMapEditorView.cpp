
// 2DMapEditorView.cpp : CMy2DMapEditorView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "2DMapEditor.h"
#endif

#include "2DMapEditorDoc.h"
#include "2DMapEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2DMapEditorView

IMPLEMENT_DYNCREATE(CMy2DMapEditorView, CView)

BEGIN_MESSAGE_MAP(CMy2DMapEditorView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy2DMapEditorView 构造/析构

CMy2DMapEditorView::CMy2DMapEditorView()
{
	// TODO: 在此处添加构造代码

}

CMy2DMapEditorView::~CMy2DMapEditorView()
{
}

BOOL CMy2DMapEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy2DMapEditorView 绘制

void CMy2DMapEditorView::OnDraw(CDC* /*pDC*/)
{
	CMy2DMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy2DMapEditorView 打印

BOOL CMy2DMapEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy2DMapEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy2DMapEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy2DMapEditorView 诊断

#ifdef _DEBUG
void CMy2DMapEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CMy2DMapEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2DMapEditorDoc* CMy2DMapEditorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2DMapEditorDoc)));
	return (CMy2DMapEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy2DMapEditorView 消息处理程序
