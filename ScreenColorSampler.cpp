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
void ScreenColorSampler::GetColors(std::vector<Color>& colorsTop, std::vector<Color>& colorsBottom, std::vector<Color>& colorsLeft, std::vector<Color>& colorsRight) {

}