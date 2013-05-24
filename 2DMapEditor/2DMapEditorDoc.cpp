
// 2DMapEditorDoc.cpp : CMy2DMapEditorDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "2DMapEditor.h"
#endif

#include "2DMapEditorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy2DMapEditorDoc

IMPLEMENT_DYNCREATE(CMy2DMapEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy2DMapEditorDoc, CDocument)
END_MESSAGE_MAP()


// CMy2DMapEditorDoc ����/����

CMy2DMapEditorDoc::CMy2DMapEditorDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMy2DMapEditorDoc::~CMy2DMapEditorDoc()
{
}

BOOL CMy2DMapEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	CPoint cp;
	MapEditorControllerSingleton::Instance().NewMap(cp);
	return TRUE;
}




// CMy2DMapEditorDoc ���л�

void CMy2DMapEditorDoc::Serialize(CArchive& ar)
{
	
	MapEditorControllerSingleton::Instance().Serialize(ar);
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMy2DMapEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMy2DMapEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMy2DMapEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy2DMapEditorDoc ���

#ifdef _DEBUG
void CMy2DMapEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy2DMapEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy2DMapEditorDoc ����
