#include "CheatConvert.h"
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/tokenzr.h>
CheatConvert::CheatConvert(int flags):
    FLAGS(flags)
{
}

CheatConvert::~CheatConvert()
{
    //dtor
}

int CheatConvert::convert_cheat(wxString* CHEAT)
{
    size_t POS = 0;
    POS = CHEAT->find(',', POS+1); // first ,
    POS = CHEAT->find(',', POS+1); // seccond ,
    wxString ADRESS = CHEAT->substr(POS+1, 8); //get the patch adress
    POS = CHEAT->find(',', POS+1); //find 3rd ,
    wxString TYPE = CHEAT->SubString(POS+1, CHEAT->find(',', POS+1)-1); //get type, so we can then change first number of ADRESS
    POS = CHEAT->find(',', POS+1); //find 4th
    wxString VAL = CHEAT->substr(POS+1, 8); //get the patch adress

    if (TYPE == "word")
        ADRESS[0] = '2';
    else if (TYPE == "half")
        ADRESS[0] = '1';
    else if (TYPE == "byte")
        ADRESS[0] = '0';

    if (FLAGS & MAKE_LOWERCASE_CHEATS)
    {
        VAL = VAL.Lower();
        ADRESS = ADRESS.Lower();
    } else if (FLAGS & MAKE_UPPERCASE_CHEATS)
    {
        VAL = VAL.Upper();
        ADRESS = ADRESS.Upper();
    }


    CHEAT->clear();
    CHEAT->Printf("%s %s", ADRESS, VAL);
    return 0;
}
int CheatConvert::convert_cheats_on_buff(wxArrayString* BUFF)
{
    wxRegEx PNACH_EE_CHEAT(wxString("patch=[0-9],EE,[0-9a-fA-F]{8},(extends|byte|half|word|extended),[0-9a-fA-F]{8}"));
    for (size_t x=0; x< BUFF->GetCount(); x++)
    {
        wxString CHEAT = BUFF->Item(x);
        /*if (CHEAT == wxEmptyString)
        {
        	std::cout << "skipping line ["<<x<<"] as it is a wxEmptyString\n";
        	continue;
        }*/
        if (CHEAT.StartsWith("gametitle="))
        {
            if (FLAGS & SKIP_GAMETITLE)
            {
                BUFF->Item(x) = wxEmptyString;
            }
            else
            {
                CHEAT.Replace("gametitle=", "//");
                BUFF->Item(x) = CHEAT;
            }
        }
        if (CHEAT.StartsWith("author="))
        {
            CHEAT.Replace("author=", "// author: ");
            BUFF->Item(x) = CHEAT;
        }
        if (CHEAT.StartsWith("comment="))
        {
            CHEAT.Replace("comment=", "//");
            BUFF->Item(x) = CHEAT;
        }
        if (CHEAT.StartsWith("gsaspectratio="))
        {
            BUFF->Item(x) = wxEmptyString; //gsaspectratio is PCSX2 specific. we always get rid of it
        }
        if (CHEAT.StartsWith("["))
        {
            BUFF->Item(x) = "//"+CHEAT;
        }

        if (PNACH_EE_CHEAT.Matches(CHEAT))
        {
            wxString TMPBUF = PNACH_EE_CHEAT.GetMatch(CHEAT);
            wxString ORIGINAL = TMPBUF;
            convert_cheat(&TMPBUF);
            CHEAT.Replace(ORIGINAL, TMPBUF, 0);
            BUFF->Item(x) = CHEAT;
        }
    }
    return 0;
}
int CheatConvert::convert_cheats_on_buffstring(wxString* BUFFSTRING)
{
    wxArrayString VAL;
    VAL = wxSplit(BUFFSTRING->ToStdString(),'\n', '!');

    convert_cheats_on_buff(&VAL);
    BUFFSTRING->clear();
    for (size_t x=0; x< VAL.GetCount(); x++)
    {
        if (VAL[x] == wxEmptyString)
        {
            if (FLAGS & SKIP_BLANK)
            {
                continue;
            }
            else
            {
                BUFFSTRING->append("\n");
            }
        }
        else
            BUFFSTRING->append(VAL[x]+'\n');
    }
    return 0;
}
int CheatConvert::convert_cheats_on_FILE(wxString PATH, wxArrayString* RESULT)
{
    if (!wxFileExists(PATH))
    {
        return -1;
        std::cerr << "FILE Does not exist\n";
    }
    wxFileInputStream input(PATH);
    if (!input.IsOk())
        return -1;
    wxTextInputStream text(input, wxT("\x09"), wxConvUTF8 );
    RESULT->clear();
    while(input.IsOk() && !input.Eof() )
    {
        RESULT->Add(text.ReadLine());
        // do something with the string
    }
    convert_cheats_on_buff(RESULT);
    return 0;
}
