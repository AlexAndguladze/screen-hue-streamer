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
	void GetColors(std::vector<Color>& width, std::vector<Color>& height, int column_count, int row_count);
	
private:
	int screenWidth, screenHeight;

	BITMAPINFOHEADER bi;
	BYTE* pPixels;
	HBITMAP hBitmap;

};

