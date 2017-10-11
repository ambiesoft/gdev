#pragma once

class Config
{
	Config(void){}
	~Config(void){}

private:
	static wxString outdir_;
	static wxString gdevroot_;

	static bool LoadSave(const bool bLoad);
public:
	static wxString GetOutdir()
	{
		return outdir_;
	}
	static void SetOutdir(const wxString& value)
	{
		outdir_=value;
	}

	static wxString GetGdevroot() 
	{
		return gdevroot_;
	}
	static void SetGdevroot(const wxString& value)
	{
		gdevroot_=value;
	}
	static bool Load();
	static bool Save();
};
