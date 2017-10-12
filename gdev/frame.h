#pragma once



class GdevFrame: public wxFrame
{
public:
	GdevFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~GdevFrame();

private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnOutdir(wxCommandEvent& event);
	
public:
	void updateTitle();

private:
	wxAuiManager m_auiManager;

	wxDECLARE_EVENT_TABLE();
};