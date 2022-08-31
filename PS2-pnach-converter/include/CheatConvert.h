#ifndef CHEATCONVERT_H
#define CHEATCONVERT_H
#include <wx/string.h>
#include <wx/arrstr.h>
#include <wx/regex.h>
#include <string>
#include <iostream>
#define SETBIT(x) (1 << x)
	enum FLAGSVAL
	{
		SKIP_GAMETITLE = SETBIT(1),
		SKIP_BLANK = SETBIT(2)
		//CONVERT_GAMETITLE_INTO_PS2RDHEADING = SETBIT(10),
	};

class CheatConvert
{
	public:
		CheatConvert(int flags);
		virtual ~CheatConvert();
		int convert_cheat(wxString* CHEAT);
		int convert_cheats_on_buff(wxArrayString* BUFF);
		int convert_cheats_on_FILE(wxString PATH, wxArrayString* RESULT);
		int convert_cheats_on_buffstring(wxString* BUFFSTRING);
	protected:

	private:
	int FLAGS;
};

#endif // CHEATCONVERT_H
