#pragma once



class GdevApp: public wxApp
{
public:
	virtual bool OnInit();
	virtual int OnExit();
	virtual void OnInitCmdLine(wxCmdLineParser& parser);
    virtual bool OnCmdLineParsed(wxCmdLineParser& parser);
};

