#include "stdafx.h"
#include "Scenery.h"
#include "MapData.h"

Scenery::Scenery():m_lpImage(NULL),m_fileName("")
{
	
}

Scenery::Scenery( const Scenery& o ):
	m_pos( o.m_pos ),
	m_bpos( o.m_bpos ),
	m_fileName( o.m_fileName ),
	m_guid( o.m_guid ),
	m_isSelect( o.m_isSelect ),
	m_lpd3ddev(o.m_lpd3ddev)
{	
	m_lpImage=LoadTexture();
}

Scenery::Scenery( const char* bmpName, const CPoint& pt ,LPDIRECT3DDEVICE9 d3ddev):
m_pos(pt),m_isSelect(false),m_fileName(bmpName),m_lpd3ddev(d3ddev)
{
	m_lpImage=LoadTexture();
	m_pos.x-=m_ImageWidth/2;
	m_pos.y-=m_ImageHeight/2;
}

Scenery::~Scenery(void)
{
	m_lpd3ddev=NULL;
	m_lpImage->Release();
}

const Scenery& 	Scenery::operator=( const Scenery& o )
{	
	m_pos=o.m_pos;
	m_bpos=o.m_bpos;
	m_fileName=o.m_fileName;
	m_guid=o.m_guid;
	m_isSelect=o.m_isSelect;
	m_lpd3ddev=o.m_lpd3ddev;
	m_lpImage=LoadTexture();

	return *this;
}

LPDIRECT3DTEXTURE9 Scenery::LoadTexture()
{
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(m_fileName.GetString(), &info);

	m_ImageWidth=info.Width;
	m_ImageHeight=info.Height;
	//create the new texture by loading a bitmap image file
	D3DXCreateTextureFromFileEx( 
		m_lpd3ddev,                //Direct3D device object
		m_fileName.GetString(),      //bitmap filename
		info.Width,            //bitmap image width
		info.Height,           //bitmap image height
		1,                     //mip-map levels (1 for no chain)
		D3DPOOL_DEFAULT,       //the type of surface (standard)
		D3DFMT_UNKNOWN,        //surface format (default)
		D3DPOOL_DEFAULT,       //memory class for the texture
		D3DX_DEFAULT,          //image filter
		D3DX_DEFAULT,          //mip filter
		D3DCOLOR_XRGB(255,255,255),            //color key for transparency
		&info,                 //bitmap file info (from loaded file)
		NULL,                  //color palette
		&texture );            //destination texture

	return texture;
}

const CRect Scenery::GetRect( MapData & mapData)
{
	CRect rect;
	CPoint cp=m_pos-mapData.GetOffest();
	rect.SetRect(cp.x,cp.y,cp.x+m_ImageWidth,cp.y+m_ImageHeight);
	return rect;
}

void Scenery::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{

	}else{

	}
}
