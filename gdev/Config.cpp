#include "stdafx.h"
#include "Config.h"
#include "Helper.h"

wxString Config::outdir_;
wxString Config::gdevroot_;

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
	wxFileConfig* pConfig=NULL;
	freer<wxFileConfig> ftt(&pConfig);
	
	bool failed = false;
	if(wxFile::Exists(inifile))
	{
		wxFileInputStream isRead(inifile);
		if(!isRead.Ok())
			return false;

		pConfig = new wxFileConfig(isRead);
		
		if(bLoad)
		{
			failed |= !pConfig->Read(KEY_OUTDIR, &outdir_);
			return !failed;
		}
	}
	else
	{
		// not file exist
		if(bLoad)
			return true;
	}

	if(pConfig==NULL)
		pConfig=new wxFileConfig();


	// save phase
	if(failed)
	{
		// if load failed, do not continue;
		return false;
	}

	wxFileOutputStream fsWrite(inifile);
	if(!fsWrite.Ok())
		return false;

	failed |= !pConfig->Write(KEY_OUTDIR, outdir_);
	
	failed |= !pConfig->Save(fsWrite);
	fsWrite.Close();
	
	return !failed;

}

bool Config::Load()
{
	return LoadSave(true);
}

bool Config::Save()
{
	return LoadSave(false);
}