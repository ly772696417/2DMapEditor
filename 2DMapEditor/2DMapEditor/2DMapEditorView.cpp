
// 2DMapEditorView.cpp : CMy2DMapEditorView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy2DMapEditorView ����/����

CMy2DMapEditorView::CMy2DMapEditorView()
{
	// TODO: �ڴ˴���ӹ������

}

CMy2DMapEditorView::~CMy2DMapEditorView()
{
}

BOOL CMy2DMapEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy2DMapEditorView ����

void CMy2DMapEditorView::OnDraw(CDC* /*pDC*/)
{
	CMy2DMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy2DMapEditorView ��ӡ

BOOL CMy2DMapEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy2DMapEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy2DMapEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMy2DMapEditorView ���

#ifdef _DEBUG
void CMy2DMapEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CMy2DMapEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2DMapEditorDoc* CMy2DMapEditorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2DMapEditorDoc)));
	return (CMy2DMapEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy2DMapEditorView ��Ϣ�������
