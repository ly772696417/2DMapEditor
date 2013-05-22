
#include "stdafx.h"
#include "CMyGame.h"
#include "MotionScenery.h"
#include "MapEditorController.h"
#include "list"

using namespace std;
double g_dscrollx=0;              //±³¾°»º´æX×ø±ê
double g_dscrolly=0;             //±³¾°»º´æY×ø±ê

const int MapSizeHeight=960;
const int MapSizeWidth=640;
const int MicMapSize=256;

bool  CMyGame::Game_Init(HWND window,CRect rect)
{
	CMyGame::myDirectx.Direct3D_Init(window,rect.Width(),rect.Height(),false);
	CMyGame::myDirectx.DirectInput_Init(window);
	m_winRect=rect;

	HRESULT result = 
		myDirectx.d3ddev->CreateOffscreenPlainSurface(
		rect.Width()*2,
		rect.Height()*2,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&background,
		NULL);
	if (result != D3D_OK) return false;

	Data_Init();
	m_Terrainename="gres\\terrain\\terrain_1.bmp";
	setTerrainFile();

	m_RectImage=myDirectx.LoadTexture("square.png",D3DCOLOR_XRGB(255,255,255));

	return true;

}

void CMyGame::Data_Init()
{
	m_isMouseDown=false;
	m_isTerrainChanged=true;
	m_isMouseLeave=false;
	m_lpfont = myDirectx.MakeFont("Arial Bold", 24);
	m_bisSel=false;
}

void CMyGame::Game_End()
{
	background->Release();
	m_RectImage->Release();
	myDirectx.DirectInput_Shutdown();
	myDirectx.Direct3D_Shutdown();

}

template <typename T>
std::string static ToString(T &t,T places=3)
{
	ostringstream oss;
	oss.precision(places);
	oss.setf(ios_base::fixed);
	oss<<t;
	return oss.str();
}



void CMyGame::Game_Run(bool isMouseDown,CPoint curMouse,CPoint downMouse)
{
	m_isMouseDown=isMouseDown;
	m_curMousePos=curMouse;
	m_downMousePos=downMouse;
	MapData * mapData=MapEditorControllerSingleton::Instance().GetMapData();
	m_mapOffest=mapData->GetOffest();
	myDirectx.d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
		D3DCOLOR_XRGB(255,255,255), 1.0f, 0);	
	myDirectx.DirectInput_Update();

	setTerrainFile();
	drawMap();	
	if(myDirectx.d3ddev->BeginScene())	
	{   
		myDirectx.spriteobj->Begin(D3DXSPRITE_ALPHABLEND);
		drawMode(1);
		drawMicMode();
		drawMicMap();
		drawTemMode();
		if (m_bisSel)
			drawRect();
		int x=m_curMousePos.x;
		int y=m_curMousePos.y;
		myDirectx.FontPrint(m_lpfont,0,10,ToString(x));
		myDirectx.FontPrint(m_lpfont,0,50,ToString(y));
		myDirectx.spriteobj->End();
		myDirectx.d3ddev->EndScene();
		myDirectx.d3ddev->Present(NULL,NULL,NULL,NULL);

	}

}

void CMyGame::setTerrainFile()
{

	if (m_isTerrainChanged=true)
	{

		LPDIRECT3DSURFACE9 image = NULL;
		m_Terrainename=MapEditorControllerSingleton::Instance().GetMapData()->GetTerrainFilePath();
		image = myDirectx.LoadSurface(m_Terrainename);

		int nscreenWid=m_winRect.Width()*2;

		for (int i=0;i<=(m_winRect.Width()*2/MapSizeWidth);i++)
		{		
			int nscreenHei=m_winRect.Height()*2;
			for (int j=0;j<=(m_winRect.Height()*2/MapSizeHeight);j++)
			{
				RECT source_rect={0,0,MapSizeWidth,MapSizeHeight};			
				RECT dest_ul={i*MapSizeWidth,j*MapSizeHeight,(i+1)*MapSizeWidth,(j+1)*MapSizeHeight};
				if (nscreenWid<MapSizeWidth)
				{				
					source_rect.right=nscreenWid;				
					dest_ul.right=i*MapSizeWidth+nscreenWid;
				}
				if (nscreenHei<MapSizeHeight)
				{
					source_rect.bottom=nscreenHei;
					dest_ul.bottom=j*MapSizeHeight+nscreenHei;
				}			

				myDirectx.d3ddev->StretchRect(
					image, 
					&source_rect, 
					background, 
					&dest_ul, 
					D3DTEXF_NONE);

				nscreenHei-=MapSizeHeight;
			}
			nscreenWid-=MapSizeWidth;
		}

		image->Release();
		m_isTerrainChanged=false;
	}
}

/*void CMyGame::scrollScreen()
{
	MapData * mapData=MapEditorControllerSingleton::Instance().GetMapData();
	CPoint mapOffest=mapData->GetOffest();
	if (m_curMousePos.x>m_winRect.Width()-50 && m_curMousePos.x<m_winRect.Width()
		&& m_curMousePos.y>10 && m_curMousePos.y<m_winRect.Height()-10 
		&& mapOffest.x<BlockSize*mapData->getWidth()-m_winRect.Width())
	{
		g_dscrollx+=25.0;
		if(g_dscrollx>m_winRect.Width())
			g_dscrollx=0;
		mapOffest.x+=25.0;
		
	}
	if (m_curMousePos.y>m_winRect.Height()-70 && m_curMousePos.y<m_winRect.Height()-10 
		&& m_curMousePos.x>MicMapSize && mapOffest.y<BlockSize*mapData->getHeight()-m_winRect.Height())
	{
		g_dscrolly+=25.0;
		if(g_dscrolly>m_winRect.Height())
			g_dscrolly=0;
		mapOffest.y+=25;
	}
	if (m_curMousePos.x>10 && m_curMousePos.x<50 && m_curMousePos.y>m_winRect.top 
		&& m_curMousePos.y<m_winRect.Height()-MicMapSize && mapOffest.x>0)
	{
		g_dscrollx-=25.0;
		if(g_dscrollx<0)
			g_dscrollx=m_winRect.Width();
		mapOffest.x-=25;
	}
	if (m_curMousePos.x>10 && m_curMousePos.x<m_winRect.Width()
		&& m_curMousePos.y>10 && m_curMousePos.y <50 && mapOffest.y>0)
	{
		g_dscrolly-=25.0;
		if(g_dscrolly<0)
			g_dscrolly=m_winRect.Height();
		mapOffest.y-=25;
	}
	
	mapData->SetOffest(mapOffest,m_winRect);
	
}*/

void CMyGame::drawMap()
{
	RECT source_rect = {(long)g_dscrollx, (long)g_dscrolly, g_dscrollx+m_winRect.Width(), g_dscrolly+m_winRect.Height()	};
	RECT dest_rect = { 0, 0, m_winRect.Width(), m_winRect.Height()};

	myDirectx.d3ddev->StretchRect(background, &source_rect, myDirectx.backbuffer, 
		&dest_rect, D3DTEXF_NONE);


}

void CMyGame::drawMicMap()
{
	RECT rect={0,m_winRect.bottom-MicMapSize-8,MicMapSize+8,m_winRect.bottom}; 
	myDirectx.d3ddev->ColorFill(myDirectx.backbuffer,&rect,D3DCOLOR_XRGB(200,200,10) );
	RECT source_rect = { 0, 0, m_winRect.Width(), m_winRect.Height()};
	RECT dest_rect={4,m_winRect.bottom-MicMapSize-4,MicMapSize+4,m_winRect.bottom-4}; 
	myDirectx.d3ddev->StretchRect(background, &source_rect, myDirectx.backbuffer, 
		&dest_rect, D3DTEXF_NONE);	
	moveMicMap();	
}

void CMyGame::setSpriteFile(string filename)
{
	m_SpriteName=filename;
	m_PlayerImage=myDirectx.LoadTexture(filename,D3DCOLOR_XRGB(255,255,255));
}

void CMyGame::drawMode(float scale)
{
	MapData * mapData=MapEditorControllerSingleton::Instance().GetMapData();
	for (list<Scenery *>::iterator it=mapData->m_sceneryList.begin(); it!=mapData->m_sceneryList.end() ; it++)
	{
		CRect rect=(*it)->GetRect(*mapData);
		if ( typeid(**it)==typeid(Scenery) )
		{
			myDirectx.Sprite_Transform_Draw((*it)->GetImage(),(*it)->GetPos().x-m_mapOffest.x,
				(*it)->GetPos().y-m_mapOffest.y,(*it)->GetWidth(),(*it)->GetHeight(),0,1,0.0,scale,scale);		
			
		}else
		{
			MotionScenery * ms=dynamic_cast<MotionScenery *>( (*it) );
			(*it)->frame_update();
			myDirectx.Sprite_Transform_Draw(ms->m_scenerys[ms->m_frames].GetImage(),
				ms->m_scenerys[ms->m_frames].GetPos().x-m_mapOffest.x,ms->m_scenerys[ms->m_frames].GetPos().y-m_mapOffest.y,
				ms->m_scenerys[ms->m_frames].GetWidth(),ms->m_scenerys[ms->m_frames].GetHeight(),0,1,0.0,scale,scale);

		}
		if ((*it)->IsSeleted())
		{				
			myDirectx.Sprite_Transform_Draw(m_RectImage,rect.left,rect.top,32,32,
				0,1,0.0,(float)rect.Width()/32.0,(float)rect.Height()/32.0);
		}
	}
}

void CMyGame::drawMicMode()
{
	MapData * mapData=MapEditorControllerSingleton::Instance().GetMapData();
	float scaleW=(float)MicMapSize/(float)(mapData->getWidth()*BlockSize);
	float scaleH=(float)MicMapSize/(float)(mapData->getHeight()*BlockSize);
	for (list<Scenery *>::iterator it=mapData->m_sceneryList.begin(); it!=mapData->m_sceneryList.end() ; it++)
	{
		if ( typeid(**it)==typeid(Scenery) )
		{
			myDirectx.Sprite_Transform_Draw((*it)->GetImage(),(*it)->GetPos().x*scaleW,(*it)->GetPos().y*scaleH+(m_winRect.Height()-MicMapSize),
				(*it)->GetWidth(),(*it)->GetHeight(),0,1,0,scaleW,scaleH);
		}else
		{
			MotionScenery * ms=dynamic_cast<MotionScenery *>( (*it) );
			(*it)->frame_update();
			myDirectx.Sprite_Transform_Draw(ms->m_scenerys[ms->m_frames].GetImage(),
				ms->m_scenerys[ms->m_frames].GetPos().x*scaleW,ms->m_scenerys[ms->m_frames].GetPos().y*scaleH+(m_winRect.Height()-MicMapSize),
				ms->m_scenerys[ms->m_frames].GetWidth(),ms->m_scenerys[ms->m_frames].GetHeight(),0,1,0.0,scaleW,scaleH);
		}
	}
}

void CMyGame::setSelRect(bool state,CRect rect)
{
	m_bisSel=state;
	m_selRect=rect;
}

void CMyGame::drawRect()
{
	if (m_selRect.left>m_winRect.left && m_selRect.right<MicMapSize 
		&& m_selRect.top>(m_winRect.bottom-MicMapSize) && m_selRect.bottom<m_winRect.bottom)
	{
	}else
	{
		myDirectx.Sprite_Transform_Draw(m_RectImage,m_selRect.left,m_selRect.top,32.0,32.0,
		0,1,0.0,(float)m_selRect.Width()/32.0,(float)m_selRect.Height()/32.0);	
	}
}

void CMyGame::moveMicMap()
{
	CPoint rectPos,rectSize;
	MapData * mapData=MapEditorControllerSingleton::Instance().GetMapData();
	rectPos.x = m_mapOffest.x*((float)MicMapSize/(BlockSize*mapData->getWidth()))+4;
	rectPos.y = m_mapOffest.y*((float)MicMapSize/(BlockSize*mapData->getHeight()))+m_winRect.Height()-MicMapSize;
	rectSize.x = (float)m_winRect.Width()/(BlockSize*mapData->getWidth())*MicMapSize;
	rectSize.y = (float)m_winRect.Height()/(BlockSize*mapData->getHeight())*MicMapSize;
	myDirectx.Sprite_Transform_Draw(m_RectImage,rectPos.x,rectPos.y,32,32,0,1,0,(float)rectSize.x/32.0,(float)rectSize.y/32.0);

}

void CMyGame::moveCameraTo(CPoint point)
{
	MapData * mapData=MapEditorControllerSingleton::Instance().GetMapData();
	CPoint offest=CPoint(
		(float)(point.x-4)/(float)MicMapSize*mapData->getWidth()*BlockSize-m_winRect.Width()/2,
		(float)(point.y+4)/(float)MicMapSize*mapData->getHeight()*BlockSize-m_winRect.Height()/2
		);
	
	mapData->SetOffest(offest,m_winRect);
	m_mapOffest=mapData->GetOffest();
	g_dscrollx=m_mapOffest.x%m_winRect.Width();
	g_dscrolly=m_mapOffest.y%m_winRect.Height();

}

void CMyGame::drawTemMode()
{
	MapEditorController::EditorMode mode = MapEditorControllerSingleton::Instance().GetEditorMode();
	string modepath=MapEditorControllerSingleton::Instance().GetModePath();
	if ( mode==MapEditorController::ModeBrush )
	{
		char buffer[260];
		string ext = GetExt( modepath );
		if ( ext==".mo" ) {
			string path = GetPath( modepath );
			FILE* fp;
			fopen_s(&fp, modepath.c_str(), "r" );
			if ( fp!=NULL ) {
				fgets( buffer, 260, fp );
				int len = strlen( buffer );
				if ( !isalpha(buffer[len-1]) ) buffer[len-1]='\0';
				modepath = CString("") + path.c_str() + buffer;

			}
			fclose( fp );
		}
		D3DXIMAGE_INFO info;
		HRESULT result = D3DXGetImageInfoFromFile(modepath.c_str(), &info);
		m_PlayerImage=myDirectx.LoadTexture(modepath,D3DCOLOR_XRGB(255,255,255));
		myDirectx.Sprite_Transform_Draw(m_PlayerImage,m_curMousePos.x-info.Width/2,m_curMousePos.y-info.Height/2,
			info.Width,info.Height,0,1,0,1,1,D3DCOLOR_ARGB(200,255,255,255));
	}
}