
// 2DMapEditorView.h : CMy2DMapEditorView ��Ľӿ�
//

#pragma once


class CMy2DMapEditorView : public CView
{
protected: // �������л�����
	CMy2DMapEditorView();
	DECLARE_DYNCREATE(CMy2DMapEditorView)

// ����
public:
	CMy2DMapEditorDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMy2DMapEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 2DMapEditorView.cpp �еĵ��԰汾
inline CMy2DMapEditorDoc* CMy2DMapEditorView::GetDocument() const
   { return reinterpret_cast<CMy2DMapEditorDoc*>(m_pDocument); }
#endif

