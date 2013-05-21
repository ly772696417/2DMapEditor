
// stdafx.cpp : 只包括标准包含文件的源文件
// 2DMapEditor.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
using namespace std;

void ErrorExit() 
{ 
	TCHAR szBuf[80]; 
	LPVOID lpMsgBuf;
	DWORD dw = GetLastError(); 

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	wsprintf(szBuf, 
		"Failed with error %d: %s", dw, lpMsgBuf); 

	MessageBox(NULL, szBuf, "Error", MB_OK); 
	exit(0); 
}

const string GetPath( const string& fileName )
{
	size_t o = fileName.length();

	for ( ; o>=0; o-- ) {

		if ( fileName[o]=='\\' ) break;
	}
	return fileName.substr( 0, o+1 );
}

const string GetExt( const string& fileName )
{
	size_t t=fileName.length();
	for ( ; t>=0; t-- ) {
		if ( fileName[t]=='.' ) break;
	}
	return fileName.substr( t, fileName.length()-t );
}


bool RectIntersect( const CRect& a, const CRect& b )
{
	CRect o;
	if ( b.PtInRect(a.TopLeft()) ) return true;
	if ( a.PtInRect(b.TopLeft()) ) return true;
	if ( o.IntersectRect( &a, &b ) ) return true;
	else return false;
}
