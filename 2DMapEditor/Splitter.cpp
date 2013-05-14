// Splitter.cpp : 实现文件
//

#include "stdafx.h"
#include "2DMapEditor.h"
#include "Splitter.h"


// CSplitter

IMPLEMENT_DYNAMIC(CSplitter, CSplitterWnd)

CSplitter::CSplitter()
{

}

CSplitter::~CSplitter()
{
}


BEGIN_MESSAGE_MAP(CSplitter, CSplitterWnd)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CSplitter 消息处理程序




void CSplitter::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CSplitterWnd::OnLButtonDown(nFlags, point);
}
