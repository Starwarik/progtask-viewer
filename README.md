# This is programming task viewer
It is written in C. Now (v1.0.0) it can run tasks, that were precompiled earlier.
# How to run it?
To run it, you don't need to compile source code, just download "bin.zip" from the latest release.
## I want to compile it from scratch!
Fuck you.
But if be serious:
1. Install MSYS2
2. Install gtk dev package in UCRT64 shell (find it in official tutorial for GTK in MSYS2)
3. Use `$(pkg-config --cflags gtk4)` with compiler for include and etc.
4. Use `$(pkg-config --libs gtk4)` with compiler for libs
5. (on windows) Use `-mwindows` if you want to disable gtk debug console.
If you want more info, see [here](https://discourse.gnome.org/t/fail-to-compile-gtk3-both-in-msys2-and-cmd/8470) and [here](https://www.gtk.org/docs/installations/windows)
# How to use it?
1. Organise your progtasks in the tree structure. Progtask folder must have following format:
   ```
   progtask
   |--{at least one .c file as direct child}
   |--build
      |--Debug (FROM CAPITAL LETTER)
         |-- {your exe}
   ```
   (by using .c file in the root of progtask app can recognise it as task folder)
2. Open the app
3. Specify root folder and scan depth (scan depth = ({path from root to farest task folder} + 2) < 15)
   (there is no localization, everything is in RUSSIAN :))
5. Press folder buttons or back button (wow, Explorer.exe immersive sim!)
6. If next opened folder is the task, app will run it. Your task must take data in the interactive session, not as args in cmd.

Enjoy :3
