#pragma once
#include <wx/wx.h>
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <vector>
#include "ScreenColorSampler.h"
#include "Color.h"
#include <list>
#include <thread>
#include <atomic>
#include <chrono>
#include<wx/timer.h>
#include "ColorData.h"

class MainFrame:public wxFrame
{
public:
	MainFrame(const wxString& title);
	~MainFrame();
private:
	void OnLedsCtrlChange(wxSpinEvent& event);
	void OnLedsTextChange(wxCommandEvent& event);
	void DrawLeds(int, int);
	void SetLedColors();
	void OnRunButton(wxCommandEvent& event);
	void OnTimer(wxTimerEvent& event);
	void WorkerFunction();
	void OnThreadUpdate(wxThreadEvent& event);

	std::thread workerThread;
	std::atomic<bool> isRunning;

	wxTimer* timer;

	wxPanel* led_display_panel;

	wxSpinCtrl* spin_ctrl_width;
	wxSpinCtrl* spin_ctrl_height;

	int led_width_count;
	int led_height_count;

	wxRadioBox* mode_radio_box;
	wxRadioBox* color_radio_box;

	std::vector <wxPanel*> leds_on_width;
	std::vector <wxPanel*> leds_on_height;

	std::vector<Color> colors_on_width;
	std::vector<Color> colors_on_height;

	ScreenColorSampler screen_color_sampler;
};
enum {
	ID_TIMER = 1,
	ID_THREAD_UPDATE
};
