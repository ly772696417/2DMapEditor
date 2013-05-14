#pragma once

#include "Scenery.h"
#include <iostream>
#include <vector>

using namespace std;
class MotionScenery : public Scenery
{
public:
	MotionScenery(); 
	MotionScenery( const string& moFile, const CPoint& pt ,LPDIRECT3DDEVICE9 d3ddev);
	virtual ~MotionScenery(void);

	
	virtual const int GetWidth() { return m_ImageWidth; }
	virtual const int GetHeight() { return m_ImageHeight; }
	virtual const CPoint& GetPos() const { return m_pos; }

	virtual bool IsSeleted() const { return m_isSelect; };
	virtual void Selete( bool state ) { m_isSelect = state; };
	virtual void positon_update( const CPoint& moveV ) { m_pos += moveV; m_bpos += moveV; };
	virtual void frame_update();
public:
	int				m_frames;
	vector<Scenery>	m_scenerys;
private:
	string			m_mofilename;	
	DWORD			m_lastTime;
	int				m_totalframe;

};