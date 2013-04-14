QtrSed
======

A GUI for running sed stream editor.  Written in C++ using Qt lib.

Conveniently edit and test sed scripts with this editor that runs sed as
you type - shortening your feedback loop. This app takes text input and 
runs it through sed with the given options and command, displaying it in the output field.

![Image](http://qt-apps.org/CONTENT/content-pre2/158186-2.png)

Features
======
- Autorun (run sed on every keystroke)
- Extended regexp (-E)
- Surpress output (-n)
- Export sed command to bash script
- Read input from file
- Save input and output fields


Getting Started
======
Get the source using git or [download](https://github.com/jadeatucker/qtrsed/archive/master.zip)
```bash
git clone https://github.com/jadeatucker/qtrsed.git
```

Build from source
```bash
cd qtrsed/
mkdir build
cd build/
qmake ../
make
```

Run (OS X)
```bash
open qtrsed.app/
```

QtrSed has only been tested on Mac OS X 10.8.3 and Qt 5.0.2


References
======
- [sed manpage](http://unixhelp.ed.ac.uk/CGI/man-cgi?sed)
- [sed tutorial](http://www.grymoire.com/Unix/Sed.html)
