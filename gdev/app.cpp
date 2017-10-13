#include "stdafx.h"

#include "app.h"
#include "frame.h"
#include "config.h"
#include "helper.h"


bool GdevApp::OnInit()
{
	if (!theConfig.Load())
	{
		Helper::Alert("Load failed.");
	}

	if(!wxApp::OnInit())
		return false;



	GdevFrame *frame = new GdevFrame(APPNAME, wxDefaultPosition, wxSize(800,640));
	frame->Show( true );
	frame->updateTitle();

	// log gdev root
	frame->AddLog(_("gdev root = \"" + theConfig.GetGdevrootRT() +"\""));

	// log depot_tools
	wxFileName depotDir = wxFileName::DirName(theConfig.GetGdevrootRT());
	depotDir.AppendDir("depot_tools");

	frame->AddLog(wxString::Format(_("depot_tolls = \"%s\"%s"), depotDir.GetFullPath(),
		(depotDir.DirExists() ? "" : " " + _("(not fould)"))));


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
	wxASSERT(theConfig.IsLoaded());

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