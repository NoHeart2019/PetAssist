#include "stdafx.h"
#include "C32Include.h"

VOID InitC32(HINSTANCE hInstance)
{
	InitC32Helper();
	InitC32Control(hInstance);
	InitC32Util();
	InitC32D2D1();

	InitC32ControlEx();
	InitC32ControlGdi();
	setlocale(LC_ALL, "chinese");
}