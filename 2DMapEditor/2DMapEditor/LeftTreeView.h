#pragma once

// CLeftTreeView 视图
#include "stdafx.h"
#include <iostream>

using namespace std;

class CLeftTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CLeftTreeView)

public:
	static CLeftTreeView *Singleton() { return m_pSingleton;}

private:
	static CLeftTreeView *m_pSingleton;

private:
	HTREEITEM m_res;
	CString m_path;
	void ReadResource( CTreeCtrl* ctlTree, HTREEITEM parent, const string& path, const string& ext="bmp" );

protected:
	CLeftTreeView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLeftTreeView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};


