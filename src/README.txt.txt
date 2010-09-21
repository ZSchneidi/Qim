
Qim - program hirarchy

start at main.cpp 					//this is the main function
core/coreendinge.cpp				//this is the main class of Qim here you find all other instances


Always remeber the dependences of applications.

The Qim is a Qt based application. So what you need to have in
the application home dir are some dynamic linked libraries.

You need:

QtGui4.dll 			- Qt library for graphical interfaces
QtCore4.dll 		- Qt core library for major functions
libgcc_s_dw2-1.dll	- is part of newer GCC versions and is necessary for exception handling
mingwm10.dll		- is needed when running an application which was compiled with MinGW

To find more missing libraries use the "dependencywalker"
your can find it on http://www.dependencywalker.com/ it's a really helpful tool.