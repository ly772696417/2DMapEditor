// Splitter.cpp : ʵ���ļ�
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



// CSplitter ��Ϣ�������




void CSplitter::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CSplitterWnd::OnLButtonDown(nFlags, point);
}
