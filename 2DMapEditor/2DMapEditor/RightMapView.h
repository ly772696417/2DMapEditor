#pragma once


// CRightMapView ��ͼ

class CRightMapView : public CView
{
	DECLARE_DYNCREATE(CRightMapView)

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
};


