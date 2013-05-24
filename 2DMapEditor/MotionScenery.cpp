#include "stdafx.h"
#include "MotionScenery.h"

IMPLEMENT_SERIAL(MotionScenery,CObject,1)
MotionScenery::MotionScenery()
{

}

MotionScenery::~MotionScenery()
{

};

MotionScenery::MotionScenery( const string& moFile, const CPoint& pt,LPDIRECT3DDEVICE9 d3ddev ):
m_mofilename(moFile),m_lastTime(0),	m_frames(0),m_totalframe(0)
{
	string path = GetPath( moFile );
	char buffer[260];
	FILE* fp;
	fopen_s(&fp, moFile.c_str(), "r" );
	while ( fgets( buffer, 260, fp ) ) 
	{		
		size_t len = strlen(buffer);
		if (!isalpha(buffer[len-1])) {
			buffer[len-1] = '\0';
		}
		m_totalframe++;
		string path = GetPath( moFile );
		CString fullName = CString("") + path.c_str() + buffer;

		Scenery scenery( fullName.GetString(), pt,d3ddev );
		m_scenerys.push_back( scenery );
	}
	fclose( fp );
}

void MotionScenery::LoadTexture(LPDIRECT3DDEVICE9 d3ddev)
{
	for (int i=0;i<m_scenerys.size();i++)
	{
		m_scenerys[i].m_lpd3ddev=d3ddev;
		m_scenerys[i].LoadTexture();
	}
}

void MotionScenery::positon_update( const CPoint& moveV )
{
	for (size_t i=0;i<m_scenerys.size();i++)
	{
		m_scenerys[i].positon_update(moveV);
	}
}
void MotionScenery::frame_update()
{
	DWORD t = GetTickCount();

	// If time is up update time.
	if ( t>m_lastTime+30 ) 
	{
		m_lastTime = t;
		m_frames ++; 
		m_frames %= m_totalframe;
	}
}

void MotionScenery::Selete( bool state )
{
	for (size_t i=0;i<m_scenerys.size();i++)
	{
		m_scenerys[i].Selete(state);
	}
}

const CRect MotionScenery::GetRect(MapData & mapData)
{
	return m_scenerys[0].GetRect(mapData);
}

void MotionScenery::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar<<CString(m_mofilename.c_str())<<m_totalframe<<m_frames<<m_lastTime;
		ar<<m_scenerys.size();
		for (int i=0;i<m_scenerys.size();i++)
		{
			m_scenerys[i].Serialize(ar);
		}
	}else{
		CString cs;
		ar>>cs>>m_totalframe>>m_frames>>m_lastTime;
		m_mofilename=cs.GetString();
		int size;
		ar>>size;
		for(int i=0;i<size;i++)
		{
			Scenery scenery;
			scenery.Serialize(ar);
			m_scenerys.push_back(scenery);
		}
	}
}


