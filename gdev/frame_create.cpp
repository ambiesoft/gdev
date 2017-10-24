#include "stdafx.h"

#include "app.h"
#include "frame.h"
#include "Helper.h"
#include "Config.h"





GdevFrame::GdevFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	m_auiManager.SetManagedWindow(this);


	wxTextCtrl* text1 = new wxTextCtrl(
		this, 
		-1,
		_("Pane 1 - sample text"),
		wxDefaultPosition,
		wxSize(200,150),
		wxNO_BORDER | wxTE_MULTILINE);
	m_auiManager.AddPane(text1, 
		wxLEFT,
		wxT("Pane Number One"));

    m_auiManager.AddPane(
		CreateTreeCtrl(),
		wxAuiPaneInfo().
		Name(wxT("test8")).Caption(wxT("Tree Pane")).Left().Layer(1).Position(1).CloseButton(true).MaximizeButton(true)
		);

	m_logWindow = new wxTextCtrl(
		this,
		-1,
		_(""),
		wxDefaultPosition,
		wxSize(10,120),
		wxTE_MULTILINE|wxTE_READONLY);



	m_auiManager.AddPane(
		m_logWindow,
		wxBOTTOM,
		_("Log"));

	CreateMenu();

	CreateStatusBar();
	SetStatusText(_("Ready"));


	m_auiManager.Update();
}

bool GdevFrame::CreateMenu()
{

	wxMenu *menuFile = new wxMenu;
	menuFile->Append(
		ID_Hello,
		"&Hello...\tCtrl-H",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);


	wxMenu *menuInstall = new wxMenu;
	menuInstall->Append(
		ID_InstallDepotTools,
		"&depottools...",
		"Install depottools");

	wxMenu *menuOption = new wxMenu;
	menuOption->Append(
		ID_Outdir,
		"&Outdir...\tCtrl-O",
		"Set Outdir for gn");

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);


	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuInstall, "&Install");
	menuBar->Append(menuOption, "&Option");
	menuBar->Append(menuHelp, "&Help");


	SetMenuBar(menuBar);
	return true;
}
wxTreeCtrl* GdevFrame::CreateTreeCtrl()
{
    wxTreeCtrl* tree = new wxTreeCtrl(this, wxID_ANY,
                                      wxPoint(0,0), wxSize(160,250),
                                      wxTR_DEFAULT_STYLE | wxNO_BORDER);

    wxImageList* imglist = new wxImageList(16, 16, true, 2);
    imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16)));
    imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16)));
    tree->AssignImageList(imglist);

    wxTreeItemId root = tree->AddRoot(wxT("wxAUI Project"), 0);
    wxArrayTreeItemIds items;



    items.Add(tree->AppendItem(root, wxT("Item 1"), 0));
    items.Add(tree->AppendItem(root, wxT("Item 2"), 0));
    items.Add(tree->AppendItem(root, wxT("Item 3"), 0));
    items.Add(tree->AppendItem(root, wxT("Item 4"), 0));
    items.Add(tree->AppendItem(root, wxT("Item 5"), 0));


    int i, count;
    for (i = 0, count = items.Count(); i < count; ++i)
    {
        wxTreeItemId id = items.Item(i);
        tree->AppendItem(id, wxT("Subitem 1"), 1);
        tree->AppendItem(id, wxT("Subitem 2"), 1);
        tree->AppendItem(id, wxT("Subitem 3"), 1);
        tree->AppendItem(id, wxT("Subitem 4"), 1);
        tree->AppendItem(id, wxT("Subitem 5"), 1);
    }


    tree->Expand(root);

    return tree;
}