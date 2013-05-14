/*
DirectX�࣬�������е�Directx��ش������ͱ���
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
const int SCREENW=1024;                       //��Ϸ��Ļ���
const int SCREENH=768;						  //��Ϸ��Ļ�߶�

class CMyDirectx
{
private:
	//Direct3D ����
	 LPDIRECT3D9 d3d; 	
	 //�����豸 ����	
	 LPDIRECTINPUT8 dinput;
	 LPDIRECTINPUTDEVICE8 dimouse ;
	 LPDIRECTINPUTDEVICE8 dikeyboard ;
	 DIMOUSESTATE mouse_state;
	 char cKeys[256];
	 XINPUT_GAMEPAD controllers[4];
	 //����
	 LPD3DXFONT g_lpfont;
public:
	 LPDIRECT3DDEVICE9 d3ddev; 
	 LPDIRECT3DSURFACE9 backbuffer;
	 LPD3DXSPRITE spriteobj;
	 CMyDirectx();
	 ~CMyDirectx();
	//D3D�������豸�ĳ�ʼ�����ͷ�
	bool Direct3D_Init(HWND hwnd, int width, int height, bool fullscreen);                     //��ʼ��D3D
	void Direct3D_Shutdown();																   //�ͷ�D3D
	bool DirectInput_Init(HWND);																//�����豸��ʼ��
	void DirectInput_Update();																	//�����豸״̬����
	void DirectInput_Shutdown();																//�ͷ������豸
	//������	
	int Mouse_X();
	int Mouse_Y();
	bool Key_Down(int);	
	int Mouse_Button(int);
	//���غͻ��Ʊ���
	LPDIRECT3DSURFACE9 LoadSurface(string filename);
	void DrawSurface(LPDIRECT3DSURFACE9 dest, float x, float y, LPDIRECT3DSURFACE9 source);
	//���غͻ�������
	LPDIRECT3DTEXTURE9 LoadTexture(string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(0,0,0));
	void Sprite_Draw_Frame(LPDIRECT3DTEXTURE9 texture, int destx, int desty, 
							int framenum, int framew, int frameh, int columns);
	void Sprite_Animate(int &frame, int startframe, int endframe, int direction, int &starttime, int delay);
	// ����任���غ���
    void Sprite_Transform_Draw(LPDIRECT3DTEXTURE9 image, int x, int y, int width, int height, 
							 int frame = 0, int columns = 1, float rotation = 0.0f, 
							 float scaleW = 1.0f, float scaleH = 1.0f, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));

    void Sprite_Transform2_Draw(LPDIRECT3DTEXTURE9 image, int x, int y,int width, int height,int imageX=0,int imageY =0,
							float rotation = 0.0f, float scaleW = 1.0f,float scaleH=1.0f,D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));
	//�������úʹ�ӡ
	LPD3DXFONT MakeFont(string name, int size);
	void FontPrint(LPD3DXFONT font, int x, int y, string text, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));
	//��ײ���
	//��Ⱦ
	void Render();


};
