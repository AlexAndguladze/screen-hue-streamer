#include "App.h"
#include <wx/wx.h>
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("Screen Hue Streamer");
	mainFrame->SetClientSize(600, 400);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}