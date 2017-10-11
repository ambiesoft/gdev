#include "stdafx.h"
#include "Helper.h"



wxString Helper::GetIniFile()
{
	wxString fullpath, volume, path, name, ext;
	wxFileName::SplitPath(wxStandardPaths::Get().GetExecutablePath(),
		&volume,&path,&name,&ext);

	wxFileName fn;
	fn.Assign(volume,path,name,"ini",true);
	return fn.GetFullPath();
}
