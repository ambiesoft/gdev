#pragma once

class Helper
{
	Helper(void);
	~Helper(void);

public:
	static wxString GetIniFile();
	static wxString GetAppDir();
	static void Alert(const wxString& message)
	{
		wxMessageBox(message,
			APPNAME,
			wxOK | wxICON_ERROR);
	}
	static wxString RemoveTrailingSeparator(const wxString& t)
	{
		if (t.IsEmpty())
			return t;

		wxString ret(t);
		
		// should remove both separators.
		if (ret[ret.size() - 1] == wxT('/') ||
			ret[ret.size() - 1] == wxT('\\'))
		{
			ret.RemoveLast();
		}

		return ret;
	}

	static wxString QuotePath(const wxString& t)
	{
		if (t.IsEmpty())
			return t;
		if (t[0] == wxT('"'))
			return t;

		bool need = false;
		for (size_t i = 0; i < t.size(); ++i)
		{
			if (t[i] == wxT(' '))
			{
				need = true;
				break;
			}
		}

		return need ? wxT('"') + t + wxT('"') : t;
	}
};
