
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

#include "LeftTreeView.h"
#include "RightMapView.h"
#include "Splitter.h"

class CMainFrame : public CFrameWnd
{
private:
	CSplitter m_splitter;

public:
	CLeftTreeView *m_leftTreeView;
	CRightMapView *m_rightMapView;
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
};


