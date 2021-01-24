# FBLAQuiz
Submission for 2020 FBLA Coding and Programming by Aaron Perrotta

## Dependencies
### Qt5
#### Installation (Windows)
[Use the Qt installer](https://www.qt.io/download-qt-installer)
#### Installation (Linux)
Check your distro's documentation for the best way to install (most likely using your distros package manager). Qt5 can be installed on Arch Linux for example via the command `sudo pacman -S qt5-base`. Your distro's package manager may not contain everything needed (such at qbs, a Qt tool used for building) so check to make sure that's also installed.

You can also use the Qt installer on Linux, though I haven't tried it.

## Building
### Windows
Open the FBLAQuiz.qbs file in the QtCreator IDE and build/run the project through that.
### Linux
To build, run the command `qbs` in the root directory of the project (same directory as the FBLAQuiz.qbs file).

To build & run, run the command `qbs run` in the root directory of the project.

To clean, run the command `qbs clean` in the root directory of the project.
