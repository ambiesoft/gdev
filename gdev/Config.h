#pragma once

class Config
{
	Config(void){}
	~Config(void){}

private:

	wxString gdevroot_;
	wxString outdir_;


	bool LoadSave(const bool bLoad);
public:
	static Config& GetInstance()
	{
		static Config conf;
		return conf;
	}
	wxString GetOutdir() const
	{
		return outdir_;
	}
	void SetOutdir(const wxString& value)
	{
		outdir_=value;
	}

	wxString GetGdevroot() const
	{
		return gdevroot_;
	}
	void SetGdevroot(const wxString& value)
	{
		gdevroot_=value;
	}
	wxString GetGdevrootRT() const;

	bool Load();
	bool Save();
};

#define theConfig (Config::GetInstance())