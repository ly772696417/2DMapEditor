#pragma once


// CSplitter

class CSplitter : public CSplitterWnd
{
	DECLARE_DYNAMIC(CSplitter)

public:
	CSplitter();
	virtual ~CSplitter();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


