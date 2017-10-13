#pragma once



enum
{
	ID_Hello = 1,
	ID_InstallDepotTools,
	ID_Outdir,
};

class GdevFrame: public wxFrame
{
public:
	GdevFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~GdevFrame();

private:
	void OnHello(wxCommandEvent& event);
	void OnInstallDepottools(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnOutdir(wxCommandEvent& event);
	
	wxTreeCtrl* CreateTreeCtrl();
	wxTextCtrl* m_logWindow;
	bool CreateMenu();

public:
	void updateTitle();
	void AddLog(const wxString& message);

private:
	wxAuiManager m_auiManager;

	wxDECLARE_EVENT_TABLE();
};

