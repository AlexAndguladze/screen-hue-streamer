#include "ScreenColorSampler.h"

ScreenColorSampler::ScreenColorSampler() {
	GetDesktopResolution(screenWidth, screenHeight);
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

}
void ScreenColorSampler::GetColors(std::vector<Color>& colors_width, std::vector<Color>& colors_height, int column_count, int row_count) {
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = screenWidth;
	bi.biHeight = -screenHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biCompression = BI_RGB;

	HDC screenDC = GetDC(NULL);
	HDC memoryDC = CreateCompatibleDC(screenDC);


	BYTE* pPixels;
	HBITMAP hBitmap = CreateDIBSection(memoryDC, (BITMAPINFO*)&bi, DIB_RGB_COLORS, (void**)&pPixels, NULL, 0);

	if (hBitmap == NULL || pPixels == NULL) {
		// Handle error
		return;
	}
	if (pPixels == NULL) {
		// Handle error
		return;
	}

	SelectObject(memoryDC, hBitmap);

	BitBlt(memoryDC, 0, 0, screenWidth, screenHeight, screenDC, 0, 0, SRCCOPY);


	int column_width = screenWidth / column_count;
	int column_remainder = screenWidth % column_count;
	int screen_height_divider = 3;//to calculate average color of only top n-th pixels of full height
	

	//calculate top led colors
	for (int k = 0; k < column_count; k++) 
	{
		unsigned long Rsum = 0;
		unsigned long Gsum = 0;
		unsigned long Bsum = 0;

		if (k + 1 == column_count) {//if its a last column and screen width was not divided evenly. 
			column_width += column_remainder;
		}
		for (int y = 0; y < screenHeight / screen_height_divider; y++)
		{
			for (int x = 0; x < column_width; x++)
			{
				BYTE* pixel = pPixels + y * screenWidth * 3 + x * 3 + k * column_width * 3;
				Rsum += pixel[2];
				Gsum += pixel[1];
				Bsum += pixel[0];
			}
		}
		int red = (Rsum / (column_width * screenHeight / screen_height_divider));
		int green = (Gsum / (column_width * screenHeight / screen_height_divider));
		int blue = (Bsum / (column_width * screenHeight / screen_height_divider));

		Color color = Color(red, green, blue);
		colors_width.push_back(color);
	}

	column_width = screenWidth / column_count;
	//calculate bottom led colors
	for (int k = 0; k < column_count; k++) {
		unsigned long Rsum = 0;
		unsigned long Gsum = 0;
		unsigned long Bsum = 0;

		if (k + 1 == column_count) {
			column_width += column_remainder;
		}
		for (int y = screenHeight-1; y > screenHeight - (screenHeight / screen_height_divider); y--) 
		{
			for (int x = 0; x < column_width; x++)
			{
				BYTE* pixel = pPixels + y * screenWidth * 3 + x * 3 + k * column_width * 3;
				Rsum += pixel[2];
				Gsum += pixel[1];
				Bsum += pixel[0];
			}
		}
		int red = (Rsum / (column_width * screenHeight / screen_height_divider));
		int green = (Gsum / (column_width * screenHeight / screen_height_divider));
		int blue = (Bsum / (column_width * screenHeight / screen_height_divider));

		Color color = Color(red, green, blue);
 		colors_width.push_back(color);
	}

	int row_height = screenHeight / row_count;
	int row_reminder = screenHeight % row_count;
	int screen_width_divider = 15;

	//calculate left side led colors
	for (int k = 0; k < row_count; k++)
	{
		unsigned long Rsum = 0;
		unsigned long Gsum = 0;
		unsigned long Bsum = 0;
		
		int led_offset = k * row_height * screenWidth * 3;//makes it go to next led area

		if (k + 1 == row_count) {
			row_height += row_reminder;
		}
		for (int y = 0; y < row_height; y++)
		{
			for (int x = 0; x < screenWidth / screen_width_divider; x++)
			{
				BYTE* pixel = pPixels + y * screenWidth * 3 + x * 3 + led_offset;
				Rsum += pixel[2];
				Gsum += pixel[1];
				Bsum += pixel[0];
			}
		}
		int red = (Rsum / (row_height * screenWidth / screen_width_divider));
		int green = (Gsum / (row_height * screenWidth / screen_width_divider));
		int blue = (Bsum / (row_height * screenWidth / screen_width_divider));

		Color color = Color(red, green, blue);
		colors_height.push_back(color);
	}

	row_height = screenHeight / row_count;

	//calculate right side led colors
	for (int k = 0; k < row_count; k++) {
		unsigned long Rsum = 0;
		unsigned long Gsum = 0;
		unsigned long Bsum = 0;

		int led_offset = k * row_height * screenWidth * 3;
		int width_offset = (screenWidth - (screenWidth / screen_width_divider)) * 3;
		if (k + 1 == row_count) {
			row_height += row_reminder;
		}
		for (int y = 0; y < row_height; y++)
		{
			for (int x = 0; x < screenWidth / screen_width_divider; x++)
			{
				BYTE* pixel = pPixels + width_offset + y * screenWidth * 3 + x * 3 + led_offset;
				Rsum += pixel[2];
				Gsum += pixel[1];
				Bsum += pixel[0];
			}
		}
		int red = (Rsum / (row_height * screenWidth / screen_width_divider));
		int green = (Gsum / (row_height * screenWidth / screen_width_divider));
		int blue = (Bsum / (row_height * screenWidth / screen_width_divider));
		Color color = Color(red, green, blue);
		colors_height.push_back(color);
	}

	DeleteDC(memoryDC);
	ReleaseDC(NULL, screenDC);
}