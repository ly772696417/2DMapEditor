#pragma once

#include "header.h"
class Scenery
{
public:
	// copy constructor
	Scenery( const Scenery& scenery );
	Scenery();
	Scenery( const char* bmpName, const CPoint& pt,LPDIRECT3DDEVICE9 d3ddev );
	~Scenery(void);
	LPDIRECT3DTEXTURE9 LoadTexture();
	// copy operation.
	const Scenery& operator=( const Scenery& rhs );
	virtual LPDIRECT3DTEXTURE9 GetImage() { return m_lpImage; }
	virtual const int GetWidth() { return m_ImageWidth; }
	virtual const int GetHeight() { return m_ImageHeight; }
	virtual const CPoint& GetPos() const { return m_pos; }

	virtual bool IsSeleted() const { return m_isSelect; };
	virtual void Selete( bool state ) { m_isSelect = state; };
	virtual void positon_update( const CPoint& moveV ) { m_pos += moveV; m_bpos += moveV; };
	virtual void frame_update(){};
protected:
	LPDIRECT3DDEVICE9 m_lpd3ddev;
	long			  m_guid;	
	
	CPoint			  m_pos, m_bpos;
	bool			m_isSelect;
	CString			m_fileName;
	int				m_ImageWidth;
	int				m_ImageHeight;
private:
	LPDIRECT3DTEXTURE9  m_lpImage;
	
};