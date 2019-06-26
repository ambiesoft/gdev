#include "stdafx.h"

#include "app.h"
#include "frame.h"
#include "config.h"
#include "helper.h"

wxString GdevApp::FindGNRoot()
{
	wxString strOutDir = GetOutDir();
	if (strOutDir.IsEmpty())
		return wxString();

	if (!wxDirExists(strOutDir))
		return wxString();

	wxString testDir = strOutDir;
	if (testDir.Last() != L'/' || testDir.Last() != L'\\')
		testDir += '/';
	do
	{
		if (wxFileExists(testDir + ".gn"))
			return testDir;

		wxFileName t(testDir);
		t.MakeAbsolute();
		t.AppendDir("..");
		t.Normalize();
		if (testDir == t.GetFullPath())
			break;
		testDir = t.GetFullPath();
	} while (true);

	return wxString();
}

wxString GdevApp::GetOutDir()
{
	wxString ret = theConfig.GetOutdir();
	if(!ret.IsEmpty() && wxDirExists(ret))
		return ret;

	if (!SetOutDir(nullptr))
	{
		return wxString();
	}
	return theConfig.GetOutdir();
}

bool GdevApp::SetOutDir(wxFrame* pParent)
{
	wxTextEntryDialog dlg(pParent,
		"Outdir",
		"Enter Outdir",
		theConfig.GetOutdir());
	if (wxID_OK != dlg.ShowModal())
		return false;

	theConfig.SetOutdir(dlg.GetValue());
	return true;
}

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

	// Get OutDir
	wxString strOutDir = GetOutDir();
	wxASSERT(!strOutDir.IsEmpty());
	frame->AddLog(_("outdir = \"" + strOutDir + "\""));

	// Find .gn
	wxString gdevroot = theConfig.GetGdevrootRT();
	if (gdevroot.IsEmpty())
	{
		gdevroot = FindGNRoot();
	}

	// log gdev root
	frame->AddLog(_("gdev root = \"" + gdevroot +"\""));

	// log depot_tools
	wxFileName depotDir = wxFileName::DirName(gdevroot);
	depotDir.AppendDir("depot_tools");

	frame->AddLog(wxString::Format(_("depot_tools = \"%s\"%s"), 
		depotDir.GetFullPath(),
		(depotDir.DirExists() ? "" : " " + _("(not fould)"))));



	wxString strT = _("Is depot_tools in PATH?");
	bool isDepotInPath = false;
	wxPathList pathList;
	pathList.AddEnvList(wxT("PATH"));
	if (wxNOT_FOUND != pathList.Index(depotDir.GetFullPath(), wxFileName::IsCaseSensitive()))
	{
		isDepotInPath = true;
	}


	frame->AddLog(wxString::Format(_("Is depot_tools in PATH?%s"),
		isDepotInPath ? " (Yes)" : " (No)"));
	if (!isDepotInPath)
	{
		wxString current;
		wxCHECK(wxGetEnv(wxT("PATH"), &current), true);
		wxASSERT(!current.IsEmpty());

		current = Helper::QuotePath(Helper::RemoveTrailingSeparator(depotDir.GetFullPath())) + wxPATH_SEP + current;
		wxCHECK(wxSetEnv(wxT("PATH"), current), true);
		frame->AddLog(_("-- depot_tools has been added to PATH"));
	}
	
	wxString value;
	bool isdefined = wxGetEnv(wxT("DEPOT_TOOLS_WIN_TOOLCHAIN"), &value);
	frame->AddLog(wxString::Format(_("Is DEPOT_TOOLS_WIN_TOOLCHAIN defined?%s"),
		 isdefined ? " (Yes)" : " (No)"));
	if (!isdefined)
	{
		wxCHECK(wxSetEnv(wxT("DEPOT_TOOLS_WIN_TOOLCHAIN"), "0"), true);
		frame->AddLog(_("-- DEPOT_TOOLS_WIN_TOOLCHAIN has been set to 0"));
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