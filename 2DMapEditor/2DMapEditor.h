
// 2DMapEditor.h : 2DMapEditor Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include "RightMapView.h"
#include "MapEditorController.h"
// CMy2DMapEditorApp:
// �йش����ʵ�֣������ 2DMapEditor.cpp
//

class CMy2DMapEditorApp : public CWinAppEx
{
public:
	CMy2DMapEditorApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CMy2DMapEditorApp theApp;
