#pragma once



class GdevApp: public wxApp
{
public:
	virtual bool OnInit();
	virtual int OnExit();
	virtual void OnInitCmdLine(wxCmdLineParser& parser);
    virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

	wxString FindGNRoot();
	wxString GetOutDir();
	bool SetOutDir(wxFrame* pParent);
};

#define theApp static_cast<GdevApp*>(GdevApp::GetInstance())