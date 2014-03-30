FREPenTablet
============

This AIR Native Extension allows you to read pressure sensitivity data from a pen tablet. It’s only been tested on Windows 7 with a Wacom Intuos 4.

Contents:

- `FREPenTablet` - A Visual C++ 2010 Express project which contains the native code.
- `PenTabletLib` - A Flash Builder project for exposing an API to the native code in ActionScript.
- `PenTabletDemo` - A sample Flash Builder project which uses the extension to draw with pressure.
- Batch files, so you don’t have to use the command line
- All intermediate files, so you don't have to compile everything yourself.

Requirements:

- Visual C++ 2010 Express
- AIR 3 SDK from Adobe Labs
- Flash Builder 4

The project contains some placeholder files that I cannot include in the repository because they are copyrighted by Adobe. After checking out the project, you need to:

- Replace `FREPenTablet/FREPenTablet/FlashRuntimeExtensions.h` with `AIR_SDK/include/FlashRuntimeExtensions.h`
- Replace `FREPenTablet/FREPenTablet/FlashRuntimeExtensions.lib` with `AIR_SDK/lib/win/FlashRuntimeExtensions.lib`

Now that everything is setup, you can try compiling everything yourself.

1. Open `FREPenTablet/FREPenTablet.sln` in Visual C++ 2010
1. Build the .dll (F7)
1. Import `PenTabletLib` into Flash Builder
1. Build the .swc (Ctrl + B)
1. Open the .swc with a .zip editor, and extract library.swf to the same folder as the .swc
1. Build the .ane (run `PenTabletLib/bin/package.bat`)
1. Import `PenTabletDemo` into Flash Builder
1. Build the .swf (Ctrl + B)
1. Build the .exe (run `PenTabletLib/bin-debug/package.bat`)
1. If everything was successful, you can draw on the stage with pressure sensitivity!
