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
void ScreenColorSampler::GetColors(std::vector<Color>& colorsTop, std::vector<Color>& colorsBottom, std::vector<Color>& colorsLeft, std::vector<Color>& colorsRight, int columnWidth, int rowSize) {
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



	for (int y = 0; y < screenHeight/2; y++)
	{
		for (int x = 0; x < columnWidth; x++)
		{
			//BYTE* pixel = pPixels + y * columnWidth * 3 + x * 3;

		}
	}

}