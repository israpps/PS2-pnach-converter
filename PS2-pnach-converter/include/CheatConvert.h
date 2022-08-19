#ifndef CHEATCONVERT_H
#define CHEATCONVERT_H
#include <wx/string.h>
#include <wx/arrstr.h>
#include <wx/regex.h>
#include <string>
#include <iostream>
class CheatConvert
{
	public:
		CheatConvert();
		virtual ~CheatConvert();
		int convert_cheat(wxString* CHEAT);
		int convert_cheats_on_buff(wxArrayString* BUFF);
		int convert_cheats_on_FILE(wxString PATH, wxArrayString* RESULT);
		int convert_cheats_on_buffstring(wxString* BUFFSTRING);
	protected:

	private:

};

#endif // CHEATCONVERT_H
