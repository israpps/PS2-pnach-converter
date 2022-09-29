/***************************************************************
 * Name:      PS2_pnach_converterApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Matias Israelson (El_isra) (israelson-matias@hotmail.com)
 * Created:   2022-08-19
 * Copyright: Matias Israelson (El_isra) (www.github.com/israpps)
 * License:
 **************************************************************/

#include "PS2_pnach_converterApp.h"
#include "CheatConvert.h"
#include <wx/textfile.h>
//(*AppHeaders
#include "PS2_pnach_converterMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(PS2_pnach_converterApp);

bool PS2_pnach_converterApp::OnInit()
{
    if (wxTheApp->argc >= 2) //we have commands
    {
        int FLG = 0;
        if (wxTheApp->argc > 2)
            for (int x=2; x<wxTheApp->argc; x++)
            {
                wxString TMP = wxTheApp->argv[x];
                if (TMP == wxT("-g"))
                {
                    FLG |= SKIP_GAMETITLE;
                }

                if (TMP == wxT("-b"))
                    FLG |= SKIP_BLANK;

                if (TMP == wxT("-l"))
                    FLG |= MAKE_LOWERCASE_CHEATS;

                if (TMP == wxT("-u"))
                    FLG |= MAKE_UPPERCASE_CHEATS;
            }
        CheatConvert* CHT = new CheatConvert(FLG);
        wxString CHEAT = wxTheApp->argv[1];
        wxArrayString RESULT;
        CHT->convert_cheats_on_FILE(CHEAT, &RESULT);
        if (wxTheApp->argc >= 3) //appart of a file, we have an output command
        {
            wxString OUTFILE = wxTheApp->argv[2];
            if ((OUTFILE.StartsWith("-o=")) && (OUTFILE.length() > 3))
            {
                wxTextFile file( OUTFILE.substr(3) );
                file.Open();

                for (size_t x=0; x<RESULT.GetCount(); x++)
                    file.AddLine(RESULT[x]);

                file.Write();
                file.Close();
            }
            else
            {
                for (size_t x=0; x<RESULT.GetCount(); x++)
                    std::cout << RESULT[x]<<'\n';
            }
        }
        else
        {
            for (size_t x=0; x<RESULT.GetCount(); x++)
                std::cout << RESULT[x]<<'\n';
        }
        delete CHT;
        return false;
    }
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        PS2_pnach_converterFrame* Frame = new PS2_pnach_converterFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
