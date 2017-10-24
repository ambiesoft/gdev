#pragma once

class Config
{
	Config(void)
	{
		isLoaded_ = false;
	}
	~Config(void){}

private:

	wxString gdevroot_;

	// specified by command line, not save to ini
	wxString gdevrootRT_;

	wxString outdir_;

	bool isLoaded_;
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
	void SetGdevrootRT(const wxString& value)
	{
		gdevrootRT_=value;
	}
	bool Load();
	bool Save();

	bool IsLoaded() const
	{
		return isLoaded_;
	}
};

#define theConfig (Config::GetInstance())