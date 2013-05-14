#pragma once


// CRightMapView ��ͼ

#include "CMyGame.h"

class CRightMapView : public CView
{
	DECLARE_DYNCREATE(CRightMapView)

public:
	

	bool m_isMouseDown;
	CPoint m_curMousePos,m_downMousePos;

public:
	static CRightMapView *Singleton() { return m_pSingleton;}

private:
	static CRightMapView *m_pSingleton;

protected:
	CRightMapView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CRightMapView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	CRect m_micMapRect;
	bool  m_isMouseLeave;
	bool  scrollScreen();
};


