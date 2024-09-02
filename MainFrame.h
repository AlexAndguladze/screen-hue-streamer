#pragma once
#include <wx/wx.h>
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <vector>
#include "ScreenColorSampler.h"
#include "Color.h"
#include <list>

class MainFrame:public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void OnLedsCtrlChange(wxSpinEvent& event);
	void OnLedsTextChange(wxCommandEvent& event);
	void DrawLeds(int, int);
	void DrawTop(wxCommandEvent&);

	wxPanel* led_display_panel;

	wxSpinCtrl* spin_ctrl_width;
	wxSpinCtrl* spin_ctrl_height;

	int led_width_count;
	int led_height_count;

	wxRadioBox* mode_radio_box;
	wxRadioBox* color_radio_box;

	std::vector <wxPanel*> leds_on_width;
	std::vector <wxPanel*> leds_on_height;

	ScreenColorSampler screen_color_sampler;
};

