
// MainFrm.h : CMainFrame ��Ľӿ�
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
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
};


