#pragma once
#include <wx/wx.h>
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <vector>

class MainFrame:public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void OnLedsCtrlChange(wxSpinEvent& event);
	void OnLedsTextChange(wxCommandEvent& event);
	void DrawLeds(int, int);

	wxPanel* led_display_panel;

	wxSpinCtrl* spin_ctrl_width;
	wxSpinCtrl* spin_ctrl_height;
	std::vector <wxPanel*> leds_on_width;
	std::vector <wxPanel*> leds_on_height;
};

