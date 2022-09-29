/***************************************************************
 * Name:      PS2_pnach_converterMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matias Israelson (El_isra) (israelson-matias@hotmail.com)
 * Created:   2022-08-19
 * Copyright: Matias Israelson (El_isra) (www.github.com/israpps)
 * License:
 **************************************************************/

#include "PS2_pnach_converterMain.h"
#include "CheatConvert.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/file.h>
//(*InternalHeaders(PS2_pnach_converterFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(PS2_pnach_converterFrame)
const long PS2_pnach_converterFrame::ID_TEXTCTRL1 = wxNewId();
const long PS2_pnach_converterFrame::ID_TEXTCTRL2 = wxNewId();
const long PS2_pnach_converterFrame::ID_BUTTON1 = wxNewId();
const long PS2_pnach_converterFrame::ID_BUTTON2 = wxNewId();
const long PS2_pnach_converterFrame::idMenuQuit = wxNewId();
const long PS2_pnach_converterFrame::idMenuAbout = wxNewId();
const long PS2_pnach_converterFrame::ID_MENUITEM5 = wxNewId();
const long PS2_pnach_converterFrame::ID_MENUITEM3 = wxNewId();
const long PS2_pnach_converterFrame::ID_MENUITEM4 = wxNewId();
const long PS2_pnach_converterFrame::ID_MENUITEM2 = wxNewId();
const long PS2_pnach_converterFrame::ID_MENUITEM7 = wxNewId();
const long PS2_pnach_converterFrame::ID_MENUITEM8 = wxNewId();
const long PS2_pnach_converterFrame::ID_MENUITEM6 = wxNewId();
const long PS2_pnach_converterFrame::ID_MENUITEM1 = wxNewId();
const long PS2_pnach_converterFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PS2_pnach_converterFrame,wxFrame)
    //(*EventTable(PS2_pnach_converterFrame)
    //*)
END_EVENT_TABLE()

PS2_pnach_converterFrame::PS2_pnach_converterFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(PS2_pnach_converterFrame)
    wxBoxSizer* BoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxGridSizer* GridSizer1;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    GridSizer1 = new wxGridSizer(0, 2, 0, 0);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("PNACH Codes"));
    PNACHCODE = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(543,275), wxTE_MULTILINE|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    StaticBoxSizer1->Add(PNACHCODE, 1, wxALL|wxEXPAND, 5);
    GridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("RAW Codes"));
    RAWCODE = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    StaticBoxSizer2->Add(RAWCODE, 1, wxALL|wxEXPAND, 5);
    GridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer1->Add(GridSizer1, 1, wxALL|wxEXPAND, 5);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    ConvertCheats = new wxButton(this, ID_BUTTON1, _("Convert"), wxDefaultPosition, wxSize(120,28), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer1->Add(ConvertCheats, 1, wxALL|wxEXPAND, 5);
    SaveCheats = new wxButton(this, ID_BUTTON2, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer1->Add(SaveCheats, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    Menu3 = new wxMenu();
    MenuItem3 = new wxMenu();
    MenuItem4 = new wxMenu();
    MenuItem7 = new wxMenuItem(MenuItem4, ID_MENUITEM5, _("do nothing"), wxEmptyString, wxITEM_RADIO);
    MenuItem4->Append(MenuItem7);
    EnforceLowercase = new wxMenuItem(MenuItem4, ID_MENUITEM3, _("Lowercase"), wxEmptyString, wxITEM_RADIO);
    MenuItem4->Append(EnforceLowercase);
    EnforceUppercase = new wxMenuItem(MenuItem4, ID_MENUITEM4, _("Uppercase"), wxEmptyString, wxITEM_RADIO);
    MenuItem4->Append(EnforceUppercase);
    MenuItem3->Append(ID_MENUITEM2, _("output cheats case"), MenuItem4, wxEmptyString);
    MenuItem8 = new wxMenu();
    SkipGameTitle = new wxMenuItem(MenuItem8, ID_MENUITEM7, _("gametitle entry"), wxEmptyString, wxITEM_CHECK);
    MenuItem8->Append(SkipGameTitle);
    SkipBlankLine = new wxMenuItem(MenuItem8, ID_MENUITEM8, _("Blank Lines"), wxEmptyString, wxITEM_CHECK);
    MenuItem8->Append(SkipBlankLine);
    MenuItem3->Append(ID_MENUITEM6, _("Skip elements"), MenuItem8, wxEmptyString);
    Menu3->Append(ID_MENUITEM1, _("Convertion preferences"), MenuItem3, wxEmptyString);
    MenuBar1->Append(Menu3, _("Settings"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PS2_pnach_converterFrame::OnConvertCheatsClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PS2_pnach_converterFrame::OnSaveCheatsClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PS2_pnach_converterFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PS2_pnach_converterFrame::OnAbout);
    //*)
}

PS2_pnach_converterFrame::~PS2_pnach_converterFrame()
{
    //(*Destroy(PS2_pnach_converterFrame)
    //*)
}

void PS2_pnach_converterFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void PS2_pnach_converterFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _("Coded by Matias Israelson (aka: El_isra)\n\nSpecial thanks to daniel santos for providing the information needed to make this program\n\nSource code available at https://github.com/israpps/PS2-pnach-converter");
    wxMessageBox(msg, _("PS2 Pnach converter"));
}

void PS2_pnach_converterFrame::OnConvertCheatsClick(wxCommandEvent& event)
{
    int FLAGS = 0;
    if (PNACHCODE->IsEmpty())
    {
        wxMessageBox(_("There is no text on the PNACH code field"), "", wxICON_INFORMATION);
        return;
    }
    if (SkipGameTitle->IsChecked())
        FLAGS |= SKIP_GAMETITLE;

    if (SkipBlankLine->IsChecked())
        FLAGS |= SKIP_BLANK;

    if (EnforceLowercase->IsChecked())
        FLAGS |= MAKE_LOWERCASE_CHEATS;

    if (EnforceUppercase->IsChecked())
        FLAGS |= MAKE_UPPERCASE_CHEATS;

    wxString TMP = PNACHCODE->GetValue();
    CheatConvert* CHT = new CheatConvert(FLAGS);
    CHT->convert_cheats_on_buffstring(&TMP);
    RAWCODE->Clear();
    RAWCODE->SetValue(TMP);
    delete CHT;
}

void PS2_pnach_converterFrame::OnSaveCheatsClick(wxCommandEvent& event)
{
    wxFileDialog* FDLG = new wxFileDialog(this, _("Save the converted cheats into a file"), wxEmptyString, wxEmptyString, "OpenPs2Loader cheat codes(.cht)|*.cht|any|*.*",wxFD_SAVE);

    if (FDLG->ShowModal() == wxID_OK)
    {
        wxString PATH = FDLG->GetPath();
        wxFile FILEMAN;
        FILEMAN.Open(PATH, wxFile::write);
        if (!FILEMAN.IsOpened())
        {
            wxMessageBox(_("File could not be opened for writing"), _("An error ocurred while saving..."), wxICON_ERROR);
            delete FDLG;
            return;
        }
        FILEMAN.Write(RAWCODE->GetValue());
    }
    delete FDLG;
}
