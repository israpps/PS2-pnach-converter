/***************************************************************
 * Name:      PS2_pnach_converterMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matias Israelson (El_isra) (israelson-matias@hotmail.com)
 * Created:   2022-08-19
 * Copyright: Matias Israelson (El_isra) (www.github.com/israpps)
 * License:
 **************************************************************/

#ifndef PS2_PNACH_CONVERTERMAIN_H
#define PS2_PNACH_CONVERTERMAIN_H

//(*Headers(PS2_pnach_converterFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)

class PS2_pnach_converterFrame: public wxFrame
{
public:

    PS2_pnach_converterFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~PS2_pnach_converterFrame();

private:

    //(*Handlers(PS2_pnach_converterFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnConvertCheatsClick(wxCommandEvent& event);
    void OnSaveCheatsClick(wxCommandEvent& event);
    //*)

    //(*Identifiers(PS2_pnach_converterFrame)
    static const long ID_TEXTCTRL1;
    static const long ID_TEXTCTRL2;
    static const long ID_BUTTON1;
    static const long ID_BUTTON2;
    static const long idMenuQuit;
    static const long idMenuAbout;
    static const long ID_MENUITEM5;
    static const long ID_MENUITEM3;
    static const long ID_MENUITEM4;
    static const long ID_MENUITEM2;
    static const long ID_MENUITEM7;
    static const long ID_MENUITEM8;
    static const long ID_MENUITEM6;
    static const long ID_MENUITEM1;
    static const long ID_STATUSBAR1;
    //*)

    //(*Declarations(PS2_pnach_converterFrame)
    wxButton* ConvertCheats;
    wxButton* SaveCheats;
    wxMenu* Menu3;
    wxMenu* MenuItem3;
    wxMenu* MenuItem4;
    wxMenu* MenuItem8;
    wxMenuItem* EnforceLowercase;
    wxMenuItem* EnforceUppercase;
    wxMenuItem* MenuItem7;
    wxMenuItem* SkipBlankLine;
    wxMenuItem* SkipGameTitle;
    wxStatusBar* StatusBar1;
    wxTextCtrl* PNACHCODE;
    wxTextCtrl* RAWCODE;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // PS2_PNACH_CONVERTERMAIN_H
