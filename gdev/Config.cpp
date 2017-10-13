#include "stdafx.h"
#include "Config.h"
#include "Helper.h"



#define KEY_OUTDIR	"KEY_OUTDIR"

template<class T>
struct freer
{
	T** p_;
	freer(T** p)
	{
		p_=p;
	}
	~freer()
	{
		delete *p_;
	}
};

bool Config::LoadSave(const bool bLoad)
{
	// in which case, load first
	wxString inifile = Helper::GetIniFile();
	wxFileConfig* pwxConfig=NULL;
	freer<wxFileConfig> ftt(&pwxConfig);
	
	bool failed = false;
	if(wxFile::Exists(inifile))
	{
		wxFileInputStream isRead(inifile);
		if(!isRead.Ok())
			return false;

		pwxConfig = new wxFileConfig(isRead);
		
		if(bLoad)
		{
			failed |= !pwxConfig->Read(KEY_OUTDIR, &outdir_);
			return !failed;
		}
	}
	else
	{
		// not file exist
		if(bLoad)
			return true;
	}

	if(pwxConfig==NULL)
		pwxConfig=new wxFileConfig();


	// save phase
	if(failed)
	{
		// if load failed, do not continue;
		return false;
	}

	wxFileOutputStream fsWrite(inifile);
	if(!fsWrite.Ok())
		return false;

	failed |= !pwxConfig->Write(KEY_OUTDIR, outdir_);
	
	failed |= !pwxConfig->Save(fsWrite);
	fsWrite.Close();
	
	return !failed;

}

bool Config::Load()
{
	isLoaded_ = true;
	return LoadSave(true);
}

bool Config::Save()
{
	return LoadSave(false);
}

wxString Config::GetGdevrootRT()  const
{
	if(!gdevrootRT_.IsEmpty())
		return gdevrootRT_;

	if(!gdevroot_.IsEmpty())
		return gdevroot_;
	
	return Helper::GetAppDir();
}
