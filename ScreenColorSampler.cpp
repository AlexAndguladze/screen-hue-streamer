#include "ScreenColorSampler.h"

ScreenColorSampler::ScreenColorSampler() {
	GetDesktopResolution(screenWidth, screenHeight);
	screenDC = GetDC(NULL);
	memoryDC = CreateCompatibleDC(screenDC);
}

void ScreenColorSampler::GetDesktopResolution(int& horizontal, int& vertical) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;


}
ScreenColorSampler::~ScreenColorSampler() {
	DeleteObject(hBitmap);
	DeleteDC(memoryDC);
	ReleaseDC(NULL, screenDC);
}
void ScreenColorSampler::GetColors(std::list<Color>& colorsTop, std::list<Color>& colorsBottom, std::list<Color>& colorsLeft, std::list<Color>& colorsRight, int columnWidth, int rowSize) {
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = screenWidth;
	bi.biHeight = screenHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biCompression = BI_RGB;

	BYTE* pPixels;
	hBitmap = CreateDIBSection(memoryDC, (BITMAPINFO*)&bi, DIB_RGB_COLORS, (void**)&pPixels, NULL, 0);
	SelectObject(memoryDC, hBitmap);

	BitBlt(memoryDC, 0, 0, screenWidth, screenHeight, screenDC, 0, 0, SRCCOPY);


	long long Rsum = 0;
	long long Gsum = 0;
	long long Bsum = 0;

	for (int y = 0; y < screenHeight/2; y++)
	{
		for (int x = 0; x < columnWidth; x++)
		{
			BYTE* pixel = pPixels + y * screenWidth * 3 + x * 3;
			Rsum += pixel[2];
			Gsum += pixel[1];
			Bsum += pixel[0];
		}
	}
	int red = Rsum / (columnWidth * screenHeight / 2);
	int green = Rsum / (columnWidth * screenHeight / 2);
	int blue = Rsum / (columnWidth * screenHeight / 2);

	Color color = Color(red, green, blue);
	colorsTop.push_back(color);

}