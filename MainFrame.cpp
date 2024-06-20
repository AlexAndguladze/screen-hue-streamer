#include "MainFrame.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	wxPanel* side_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 300));
	side_panel->SetBackgroundColour(wxColour(100, 100, 200));
	wxPanel* side_bottom_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 80));
	side_bottom_panel->SetBackgroundColour(wxColour(100, 100, 50));

	wxPanel* led_display_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 300));
	led_display_panel->SetBackgroundColour(wxColour(100, 0, 10));

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	

	wxBoxSizer* sizer_side = new wxBoxSizer(wxVERTICAL);
	sizer_side->Add(side_panel, 1,  wxLEFT | wxTOP | wxBOTTOM, 5);
	sizer_side->Add(side_bottom_panel, 0, wxLEFT | wxBOTTOM , 5);
	sizer->Add(sizer_side, 0, wxEXPAND);
	sizer->Add(led_display_panel, 1, wxEXPAND | wxALL, 5);

	this->SetSizerAndFit(sizer);
}