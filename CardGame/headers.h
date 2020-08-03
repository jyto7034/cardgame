#pragma once
#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include<optional>

#pragma comment(lib, "winmm.lib")

//#define LOWORD(l) ((WORD)(l))
//#define HIWORD(l) ((WORD)((DWORD)(l)>>16)&&0xFFFF)
//#define LOWBYTE(w) ((BYTE)(w))
//#define HIBYTE(w) ((BYTE)(((WORD)(w)>>8)&0xFF))
//
//#define MAKEWORD(a,b) ((WORD)(((BYTE)(a))|((WORD)((BYTE)(b)))<<8))
//#define MAKELONG(a,b)  ((LONG)(((WORD)(a)|((DWORD)((WORD)(b)))<<16))