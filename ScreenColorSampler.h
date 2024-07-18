#pragma once
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <vector>
#include "Color.h"
#include <list>

class ScreenColorSampler
{
public:
	ScreenColorSampler();
	~ScreenColorSampler();

	void GetDesktopResolution(int&,int&);
	void GetColors(std::list<Color>&, std::list<Color>&, std::list<Color>&, std::list<Color>&, int, int);
	
private:
	int screenWidth, screenHeight;
	HDC screenDC;
	HDC memoryDC;

	BITMAPINFOHEADER bi;
	BYTE* pPixels;
	HBITMAP hBitmap;

};

