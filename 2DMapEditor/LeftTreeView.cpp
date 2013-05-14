// LeftTreeView.cpp : 实现文件
//

#include "stdafx.h"
#include "2DMapEditor.h"
#include "LeftTreeView.h"
#include "RightMapView.h"

#include <iostream>
#include <string>

using namespace std;


// CLeftTreeView

CLeftTreeView * CLeftTreeView::m_pSingleton = NULL;

extern CString m_ImagePath;

IMPLEMENT_DYNCREATE(CLeftTreeView, CTreeView)

CLeftTreeView::CLeftTreeView()
{
	m_pSingleton = this;
}

CLeftTreeView::~CLeftTreeView()
{
}

BEGIN_MESSAGE_MAP(CLeftTreeView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CLeftTreeView::OnTvnSelchanged)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CLeftTreeView::OnNMDblclk)
END_MESSAGE_MAP()


// CLeftTreeView 诊断

#ifdef _DEBUG
void CLeftTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftTreeView 消息处理程序


void CLeftTreeView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CTreeCtrl* pTreeCtrl = &GetTreeCtrl();
	HTREEITEM item = pTreeCtrl->GetSelectedItem();
	char *p[TREENODENUM] = {"gres\\terrain\\", "gres\\scenery\\", "gres\\motion\\"};

	if ( !pTreeCtrl->ItemHasChildren(item) ) 
	{
		HTREEITEM parent = pTreeCtrl->GetParentItem( item );

		if (pTreeCtrl->GetItemText(parent) == "地形")
		{
			m_ImagePath = m_path + p[0] + pTreeCtrl->GetItemText(item);
			MapEditorControllerSingleton::Instance().ChangeTerrain(m_ImagePath.GetString());
			CRightMapView::Singleton()->Invalidate(TRUE);
		}

		if ( pTreeCtrl->GetItemText(parent) == "景物" ) 
		{

			// turn to full path nam
			m_ImagePath = m_path + p[1] + pTreeCtrl->GetItemText(item);
			MapEditorControllerSingleton::Instance().SetModeBrush(m_ImagePath);

		} 

		if (pTreeCtrl->GetItemText(parent) == "生物")
		{
			// turn to full path nam
			m_ImagePath = m_path + p[2] + pTreeCtrl->GetItemText(item);
			MapEditorControllerSingleton::Instance().SetModeBrush(m_ImagePath);
		}
	}

	*pResult = 0;
}


int CLeftTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES 
		|TVS_HASBUTTONS
		|TVS_LINESATROOT 
		|TVS_HASLINES
		|TVS_DISABLEDRAGDROP
		|TVS_SHOWSELALWAYS;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CTreeCtrl* ctlTree = &GetTreeCtrl();
	ctlTree->DeleteAllItems();         

	// 地图元素
	//m_res = ctlTree->InsertItem("景物",0,0);
	//ReadResource(ctlTree,m_res,"scenery\\");
	m_res[0] = ctlTree->InsertItem("地形",0,0);
	ReadResource(ctlTree,m_res[0],"gres\\terrain\\");
	m_res[1] = ctlTree->InsertItem("景物",0,0);
	ReadResource(ctlTree,m_res[1],"gres\\scenery\\");
	m_res[2] = ctlTree->InsertItem("生物",0,0);
	ReadResource(ctlTree,m_res[2],"gres\\motion\\","mo");

}

void CLeftTreeView::ReadResource( CTreeCtrl* ctlTree, HTREEITEM parent, const string& path, const string& ext/* ="bmp" */ )
{
	HANDLE  hFindFile;
	WIN32_FIND_DATA  FileData;

	hFindFile = FindFirstFile((path+"*."+ext.c_str()).c_str(), &FileData);

	if ( hFindFile==INVALID_HANDLE_VALUE ) 
		return ;
	do
	{
		ctlTree->InsertItem(FileData.cFileName, 1, 1, parent);
	}while (FindNextFile(hFindFile, &FileData));
}


void CLeftTreeView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	*pResult = 0;
}
