#pragma once

#include <Windows.h>
//--D3D用的头文件
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <xinput.h>
//--D3D用的lib库
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")


#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)