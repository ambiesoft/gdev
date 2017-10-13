#include "stdafx.h"

#include "app.h"
#include "frame.h"
#include "config.h"
#include "helper.h"


bool GdevApp::OnInit()
{
	if(!wxApp::OnInit())
		return false;

	if(!theConfig.Load())
	{
		Helper::Alert("Load failed.");
	}

	GdevFrame *frame = new GdevFrame(APPNAME, wxPoint(50, 50), wxSize(450, 340) );
	frame->Show( true );
	frame->updateTitle();

	frame->AddLog(_("gdev root = \"" + theConfig.GetGdevrootRT() +"\""));
	//if(!.IsEmpty())
	//	frame->AddLog(theConfig.GetGdevroot());
	//else
	//{
	//	frame->AddLog(wxString::Format(_("--gdev-root not specified. Using current directory (%s) as gdevroot."),
	//		theConfig.GetGdevrootRT()));
	//}

	frame->AddLog(_("Finding depottools..."));
	wxFileName depotDir = wxFileName::DirName(theConfig.GetGdevrootRT());
	depotDir.AppendDir("depottools");
	if(depotDir.DirExists())
	{
		frame->AddLog(wxString::Format(_("depottolls found (%s)."), depotDir.FileName));
	}
	else
	{
		frame->AddLog(_("depottools not found."));
	}
	return true;
}

static const wxCmdLineEntryDesc g_cmdLineDesc [] =
{
	//{ wxCMD_LINE_SWITCH, ("h"), ("help"), ("displays help on the command line parameters"),
	//wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },

	//{ wxCMD_LINE_SWITCH, ("t"), ("test"), ("test switch"),
	//wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_MANDATORY  },

	//{ wxCMD_LINE_SWITCH, ("s"), ("silent"), ("disables the GUI") },


	{ wxCMD_LINE_OPTION, ("g"), ("gdev-root"), ("gdev root"),
	wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL | wxCMD_LINE_NEEDS_SEPARATOR  },

	{ wxCMD_LINE_NONE }
};

void GdevApp::OnInitCmdLine(wxCmdLineParser& parser)
{
	parser.SetDesc (g_cmdLineDesc);
	// must refuse '/' as parameter starter or cannot use "/path" style paths
	parser.SetSwitchChars (wxT("-"));
}

bool GdevApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
	// first load config and overwrite with commnad line.
	theConfig.Load();

	wxString value;
	parser.Found("gdev-root", &value);
	theConfig.SetGdevrootRT(value);
	

	// to get at your unnamed parameters use
	wxArrayString files;
	for (unsigned int i = 0; i < parser.GetParamCount(); i++)
	{
		files.Add(parser.GetParam(i));
	}

	// and other command line parameters

	// then do what you need with them.

	return true;
}
int GdevApp::OnExit()
{
	if(!theConfig.Save())
	{
		Helper::Alert("Save failed.");
	}

	return wxApp::OnExit();
}