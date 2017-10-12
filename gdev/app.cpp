#include "stdafx.h"

#include "app.h"
#include "frame.h"
#include "config.h"
#include "helper.h"


bool GdevApp::OnInit()
{
	if(!theConfig.Load())
	{
		Helper::Alert("Load failed.");
	}

	GdevFrame *frame = new GdevFrame(APPNAME, wxPoint(50, 50), wxSize(450, 340) );
	frame->Show( true );
	frame->updateTitle();
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