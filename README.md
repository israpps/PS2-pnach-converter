# Introduction

PlayStation 2 PNACH Converter is a tool (Both command line and GUI), wich can convert PCSX2 cheat engine patches into raw cheats for PS2Rd or [Open PS2 Loader](https://github.com/ps2homebrew/Open-PS2-Loader) cheat engine.

therefore, this tool __only converts patches for the EE memory__. __IOP Patches are ignored__, as PS2Rd or OPL can't patch IOP memory on their current state.

This tool is slightly superior to the pnach converter made by pelvic trustman, since this tool converts ANY cheat, even if they´re inside a comment, also, it can work as command line tool, becomming the best tool available for automated batch cheat convertion.

This program is built on top of wxwidgets, and it´s compiled and deployed for: Linux, MacOS, Windows (x86), Windows (x64)

Pull requests to enhance this program are gladly accepted!

This tool is also the heart of the recent updates into [the largest PS2 widescreen hacks convertion effort](https://github.com/PS2-Widescreen/OPL-Widescreen-Cheats)

## Command line tool

The program supports the following arguments

- `-g`: skip the `gametitle` entry
- `-b`: skip blank lines
- `-l`: make generated cheats lowercase (has priority)
- `-u`: make generated cheats uppercase ( `-l` has priority)

- `-o=FILE`: `FILE` is used as output

__Argumment one will ALWAYS be the input file!__

## Credits

Tool made entirely by me (El_Isra, AKA: Matias Israelson)

Special thanks to daniel santos, wich explained a few things about the different patch types that PCSX2 has.
