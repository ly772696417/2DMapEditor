#include "stdafx.h"
#include "MotionScenery.h"


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


void MotionScenery::frame_update()
{
	DWORD t = GetTickCount();

	// If time is up update time.
	if ( t>m_lastTime+40 ) 
	{
		m_lastTime = t;
		m_frames ++; 
		m_frames %= m_totalframe;
	}
}


