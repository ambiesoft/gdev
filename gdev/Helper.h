#pragma once

class Helper
{
	Helper(void);
	~Helper(void);

public:
	static wxString GetIniFile();
	static void Alert(const wxString& message)
	{
		wxMessageBox(message,
			APPNAME,
			wxOK | wxICON_ERROR);
	}

};
