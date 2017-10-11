#include "stdafx.h"

#include "app.h"
#include "frame.h"
#include "Helper.h"
#include "Config.h"

enum
{
	ID_Hello = 1,
	ID_Outdir,
};


wxBEGIN_EVENT_TABLE(GdevFrame, wxFrame)
EVT_MENU(ID_Hello,   GdevFrame::OnHello)
EVT_MENU(wxID_EXIT,  GdevFrame::OnExit)
EVT_MENU(wxID_ABOUT, GdevFrame::OnAbout)
EVT_MENU(ID_Outdir,  GdevFrame::OnOutdir)
wxEND_EVENT_TABLE()


GdevFrame::GdevFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);


	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);


	wxMenu *menuOption = new wxMenu;
	menuOption->Append(ID_Outdir,"&Outdir...\tCtrl-O",
		"Set Outdir for gn");


	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, "&File" );
	menuBar->Append(menuOption,"&Option");
	menuBar->Append( menuHelp, "&Help" );
	

	SetMenuBar( menuBar );
	
	CreateStatusBar();
	
	SetStatusText( "Welcome to wxWidgets!" );
}

void GdevFrame::OnExit(wxCommandEvent& event)
{
	Close( true );
}
void GdevFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox( "This is a wxWidgets' Hello world sample",
		"About Hello World", wxOK | wxICON_INFORMATION );
}
void GdevFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}
void GdevFrame::OnOutdir(wxCommandEvent& event)
{
	wxTextEntryDialog dlg(this,
		"Outdir",
		"Enter Outdir",
		Config::GetOutdir());
	if(wxID_OK != dlg.ShowModal())
		return;

	Config::SetOutdir(dlg.GetValue());

	updateTitle();
}

void GdevFrame::updateTitle()
{
	wxString title=wxString::Format("%s | %s",Config::GetOutdir(), APPNAME);
	SetTitle(title);
}