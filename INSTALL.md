
Requirements
------------
 - Windows, Linux, Mac OS X, or POSIX compliant Unix-like OS
 - Qt Toolkit version 4.8 or later, 5.0 or later
 - C compiler and C++ compiler
 - make utility

 On Linux, you can install by 'apt-get' or 'yum'.
 Case of Ubuntu:
   Install Qt libraries and dev tools.
     $ sudo apt-get install -y qt5-default qt5-qmake libqt5sql5-mysql libqt5sql5-psql
         libqt5sql5-odbc libqt5sql5-sqlite libqt5core5a libqt5qml5 libqt5xml5
         gcc g++ make

   Install DB client libraries. (optional)
     $ sudo apt-get install -y libmysqlclient-dev libpq5 libodbc1

   For more understanding see http://doc.qt.io/qt-5/sql-driver.html


Installation
------------
1. Extract the downloaded tar.gz file.

2. Run build commands.
    Linux, Mac OS X, or Unix-like OS:
      Run the following commands.
       $ cd treefrog-x.x.x
       $ ./configure
       $ cd src
       $ make
       $ sudo make install
       $ cd ../tools
       $ make
       $ sudo make install

    Windows:
      Build binaries of two modes, release and debug.
      Run the following commands in Qt Command Prompt.
       MinGW:
         > cd (treefrog-x.x.x)
         > configure --enable-debug
         > cd src
         > mingw32-make install
         > cd ..\tools
         > mingw32-make install
         > cd ..
         > configure
         > cd src
         > mingw32-make install
         > cd ..\tools
         > mingw32-make install

       Visual Studio:
       Call vcvarsall.bat to complete environment setup in Qt Command Prompt.
        e.g.
         > cd "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\amd64"
         > vcvars64.bat

         > cd (treefrog-x.x.x)
         > configure --enable-debug
         > cd src
         > nmake install
         > cd ..\tools
         > nmake install
         > cd ..
         > configure
         > cd src
         > nmake install
         > cd ..\tools
         > nmake install

      Or, double-click to run the build.bat after editing it for your Qt
      environment.

3. Create a shortcut to TreeFrog Command Prompt (on Windows only).
   Locate the program:
     C:\Windows\System32\cmd.exe /K C:\TreeFrog\x.x.x\bin\tfenv.bat
     ("x.x.x" is version)

   * In the TreeFrog Command Prompt, build Web applications and run
     TreeFrog commands such as tspawn or treefrog.

 
 Enjoy!