#pragma once

#include "CMyDirectx.h"
#include <afxwin.h>

enum MODE_STATES
{
	NoOpretion,ModeSelection, ModeBrush, ModeMove
};

class CMyGame
{
private:
	//背景图片
	LPDIRECT3DSURFACE9 background;
	LPDIRECT3DTEXTURE9 m_PlayerImage;
	LPDIRECT3DTEXTURE9 m_RectImage;
public:
	//	bool bGameOver;
	CMyDirectx myDirectx;
	//初始化游戏
	bool Game_Init(HWND window,CRect rect);	
	void Data_Init();
	void setTerrainFile();
	void setSpriteFile(string filename);
//	void scrollScreen();
	//游戏运行
	void Game_Run(bool m_isMouseDown,CPoint curMouse,CPoint downMouse);
	void drawMap();
	void drawMicMap();
	void drawMode(float scale);
	void drawMicMode();
	void drawTemMode();
	void drawRect();
	void moveMicMap();
	void moveCameraTo(CPoint point);
	//游戏结束
	void setSelRect(bool state,CRect rect);
	void Game_End();	
private:
	CRect m_winRect;
	CRect m_selRect;
	bool  m_bisSel;
	//字体
	LPD3DXFONT m_lpfont;
public:
	CPoint m_curMousePos;
	CPoint m_downMousePos;	
	CPoint m_mapOffest;
	bool   m_isMouseDown;
	bool   m_isTerrainChanged;
	bool   m_isMouseLeave;
	string  m_Terrainename;
	string  m_SpriteName;
	
};