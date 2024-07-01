#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	wxPanel* side_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 300));
	side_panel->SetBackgroundColour(wxColour(100, 100, 200));
	wxPanel* side_bottom_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 80));
	side_bottom_panel->SetBackgroundColour(wxColour(100, 100, 50));

	led_display_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 300));
	led_display_panel->SetBackgroundColour(wxColour(100, 0, 10));

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	

	wxBoxSizer* sizer_side = new wxBoxSizer(wxVERTICAL);
	sizer_side->Add(side_panel, 1,  wxLEFT | wxTOP | wxBOTTOM, 5);
	sizer_side->Add(side_bottom_panel, 0, wxLEFT | wxBOTTOM , 5);
	sizer->Add(sizer_side, 0, wxEXPAND);
	sizer->Add(led_display_panel, 1, wxEXPAND | wxALL, 5);

	this->SetSizerAndFit(sizer);
	wxStaticText* text_led_width = new wxStaticText(side_panel, wxID_ANY, "Number of LEDs (Width)", wxPoint(10, 30));
	spin_ctrl_width = new wxSpinCtrl(side_panel, wxID_ANY, "", wxPoint(10, 50), wxSize(130, -1),16384L,5,100);
	spin_ctrl_width->Bind(wxEVT_SPINCTRL, &MainFrame::OnLedsCtrlChange, this);
	spin_ctrl_width->Bind(wxEVT_TEXT, &MainFrame::OnLedsTextChange, this);

	wxStaticText* text_led_height = new wxStaticText(side_panel, wxID_ANY, "Number of LEDs (Height)", wxPoint(10, 80));
	spin_ctrl_height = new wxSpinCtrl(side_panel, wxID_ANY, "", wxPoint(10, 100), wxSize(130, -1), 16384L, 5, 100);
	spin_ctrl_height->Bind(wxEVT_SPINCTRL, &MainFrame::OnLedsCtrlChange, this);
	spin_ctrl_height->Bind(wxEVT_TEXT, &MainFrame::OnLedsTextChange, this);
	wxButton* btn_apply = new wxButton(side_bottom_panel, wxID_ANY, "APPLY", wxPoint(47, 25), wxSize(100, 30));



	//draw leds initially
	int led_width_count = spin_ctrl_width->GetValue();
	int led_height_count = spin_ctrl_height->GetValue();
	DrawLeds(led_width_count, led_height_count);
}

void MainFrame::OnLedsTextChange(wxCommandEvent& event) {
	int led_width_count = spin_ctrl_width->GetValue();
	int led_height_count = spin_ctrl_height->GetValue();
	DrawLeds(led_width_count, led_height_count);
}

void MainFrame::OnLedsCtrlChange(wxSpinEvent& event) {
	int led_width_count = spin_ctrl_width->GetValue();
	int led_height_count = spin_ctrl_height->GetValue();
	DrawLeds(led_width_count, led_height_count);
}

void MainFrame::DrawLeds(int width_count, int height_count) {
	for (wxPanel* leds : leds_on_width) {
		leds->Destroy();
	}
	for (wxPanel* leds : leds_on_height) {
		leds->Destroy();
	}
	leds_on_width.clear();
	leds_on_height.clear();

	//draw leds of top and bottom side
	for (int i = 0; i < width_count; i++) {
		wxPanel* led = new wxPanel(led_display_panel, wxID_ANY, wxPoint(22 + i * 12, 10), wxSize(10, 10));
		led->SetBackgroundColour(wxColour(0, 0, 240));
		leds_on_width.push_back(led);
	}
	int led_row_offset = height_count*12 + 12;
	for (int i = 0; i < width_count; i++) {
		wxPanel* led = new wxPanel(led_display_panel, wxID_ANY, wxPoint(22 + i * 12, 10 + led_row_offset), wxSize(10, 10));
		led->SetBackgroundColour(wxColour(0, 0, 240));
		leds_on_width.push_back(led);
	}
	//draw leds of left and right side
	for (int i = 0; i < height_count; i++) {
		wxPanel* led = new wxPanel(led_display_panel, wxID_ANY, wxPoint(10, 22 + i * 12), wxSize(10, 10));
		led->SetBackgroundColour(wxColour(0, 240, 0));
		leds_on_height.push_back(led);
	}
	int led_column_offset = width_count * 12 + 12;
	for (int i = 0; i < height_count; i++) {
		wxPanel* led = new wxPanel(led_display_panel, wxID_ANY, wxPoint(10 + led_column_offset, 22 + i * 12), wxSize(10, 10));
		led->SetBackgroundColour(wxColour(0, 240, 0));
		leds_on_height.push_back(led);
	}

	led_display_panel->Layout();
	led_display_panel->Refresh();
}