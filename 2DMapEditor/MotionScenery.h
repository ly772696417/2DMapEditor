#pragma once

#include "Scenery.h"
#include <iostream>
#include <vector>

using namespace std;
class MotionScenery : public Scenery
{
	DECLARE_SERIAL(MotionScenery)
public:
	MotionScenery(); 
	MotionScenery( const string& moFile, const CPoint& pt ,LPDIRECT3DDEVICE9 d3ddev);
	virtual ~MotionScenery(void);

   void LoadTexture(LPDIRECT3DDEVICE9 d3ddev); 
	virtual const int GetWidth() { return m_ImageWidth; }
	virtual const int GetHeight() { return m_ImageHeight; }
	virtual const CPoint& GetPos() const { return m_pos; }

	virtual bool IsSeleted() const { return m_scenerys[0].IsSeleted(); };
	virtual void Selete( bool state );
	virtual const CRect GetRect(MapData & mapData);
	virtual void positon_update( const CPoint& moveV );
	virtual void frame_update();

	void	Serialize(CArchive& ar);
	void    Release();
public:
	int				m_frames;
	vector<Scenery>	m_scenerys;
private:
	string			m_mofilename;	
	DWORD			m_lastTime;
	int				m_totalframe;

};