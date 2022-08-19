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
		CheatConvert* CHT = new CheatConvert();
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

				for (size_t x=0; x<RESULT.GetCount();x++)
					file.AddLine(RESULT[x]);

				file.Write();
				file.Close();
			} else {
				for (size_t x=0; x<RESULT.GetCount();x++)
					std::cout << RESULT[x]<<'\n';
			}
		} else {
			std::cout <<"-----------------------------------------------------------------------\n";
			for (size_t x=0; x<RESULT.GetCount();x++)
				std::cout << RESULT[x]<<'\n';
			std::cout <<"-----------------------------------------------------------------------\nPress any key to continue\n";
			std::cin.get();
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
