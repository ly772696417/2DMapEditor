/*
DirectX类，包含所有的Directx相关处理函数和变量
*/

#pragma once

#define WIN32_EXTRA_LEAN
#define DIRECTINPUT_VERSION 0x0800

#include "header.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <io.h>
#include <algorithm>

#include "header.h"


using namespace std;


//libraries

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"dxguid.lib")


//program values
//extern bool bGameOver;
const int SCREENW=1024;                       //游戏屏幕宽度
const int SCREENH=768;						  //游戏屏幕高度

class CMyDirectx
{
private:
	//Direct3D 变量
	 LPDIRECT3D9 d3d; 	
	 //输入设备 变量	
	 LPDIRECTINPUT8 dinput;
	 LPDIRECTINPUTDEVICE8 dimouse ;
	 LPDIRECTINPUTDEVICE8 dikeyboard ;
	 DIMOUSESTATE mouse_state;
	 char cKeys[256];
	 XINPUT_GAMEPAD controllers[4];
	 //字体
	 LPD3DXFONT g_lpfont;
public:
	 LPDIRECT3DDEVICE9 d3ddev; 
	 LPDIRECT3DSURFACE9 backbuffer;
	 LPD3DXSPRITE spriteobj;
	 CMyDirectx();
	 ~CMyDirectx();
	//D3D及其与设备的初始化与释放
	bool Direct3D_Init(HWND hwnd, int width, int height, bool fullscreen);                     //初始化D3D
	void Direct3D_Shutdown();																   //释放D3D
	bool DirectInput_Init(HWND);																//输入设备初始化
	void DirectInput_Update();																	//输入设备状态更新
	void DirectInput_Shutdown();																//释放输入设备
	//输入检测	
	int Mouse_X();
	int Mouse_Y();
	bool Key_Down(int);	
	int Mouse_Button(int);
	//加载和绘制表面
	LPDIRECT3DSURFACE9 LoadSurface(string filename);
	void DrawSurface(LPDIRECT3DSURFACE9 dest, float x, float y, LPDIRECT3DSURFACE9 source);
	//加载和绘制纹理
	LPDIRECT3DTEXTURE9 LoadTexture(string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(0,0,0));
	void Sprite_Draw_Frame(LPDIRECT3DTEXTURE9 texture, int destx, int desty, 
							int framenum, int framew, int frameh, int columns);
	void Sprite_Animate(int &frame, int startframe, int endframe, int direction, int &starttime, int delay);
	// 精灵变换重载函数
    void Sprite_Transform_Draw(LPDIRECT3DTEXTURE9 image, int x, int y, int width, int height, 
							 int frame = 0, int columns = 1, float rotation = 0.0f, 
							 float scaleW = 1.0f, float scaleH = 1.0f, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));

    void Sprite_Transform2_Draw(LPDIRECT3DTEXTURE9 image, int x, int y,int width, int height,int imageX=0,int imageY =0,
							float rotation = 0.0f, float scaleW = 1.0f,float scaleH=1.0f,D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));
	//字体设置和打印
	LPD3DXFONT MakeFont(string name, int size);
	void FontPrint(LPD3DXFONT font, int x, int y, string text, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));
	//碰撞检测
	//渲染
	void Render();


};
