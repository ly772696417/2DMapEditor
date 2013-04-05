
// 2DMapEditorView.h : CMy2DMapEditorView 类的接口
//

#pragma once


class CMy2DMapEditorView : public CView
{
protected: // 仅从序列化创建
	CMy2DMapEditorView();
	DECLARE_DYNCREATE(CMy2DMapEditorView)

// 特性
public:
	CMy2DMapEditorDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy2DMapEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 2DMapEditorView.cpp 中的调试版本
inline CMy2DMapEditorDoc* CMy2DMapEditorView::GetDocument() const
   { return reinterpret_cast<CMy2DMapEditorDoc*>(m_pDocument); }
#endif

