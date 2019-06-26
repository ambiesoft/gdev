#include "stdafx.h"

#include "app.h"
#include "frame.h"
#include "Helper.h"
#include "Config.h"


wxBEGIN_EVENT_TABLE(GdevFrame, wxFrame)
EVT_MENU(ID_Hello,   GdevFrame::OnHello)
EVT_MENU(ID_InstallDepotTools,   GdevFrame::OnInstallDepottools)
EVT_MENU(wxID_EXIT,  GdevFrame::OnExit)
EVT_MENU(wxID_ABOUT, GdevFrame::OnAbout)
EVT_MENU(ID_Outdir,  GdevFrame::OnOutdir)
wxEND_EVENT_TABLE()


GdevFrame::~GdevFrame()
{
	m_auiManager.UnInit();
}

void GdevFrame::AddLog(const wxString& message)
{
	m_logWindow->AppendText(message);
	m_logWindow->AppendText("\n");
}

void GdevFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}
void GdevFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox( 
		theApp->GetAppName() + " " + "v1.0.1",
		theApp->GetAppName(),
		wxOK | wxICON_INFORMATION );
}
void GdevFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}
void GdevFrame::OnInstallDepottools(wxCommandEvent& event)
{
	wxLogMessage("OnInstallDepottools!");
}

void GdevFrame::OnOutdir(wxCommandEvent& event)
{
	theApp->SetOutDir(this);

	updateTitle();
}

void GdevFrame::updateTitle()
{
	wxString title=wxString::Format("%s | %s",theConfig.GetOutdir(), APPNAME);
	SetTitle(title);
}