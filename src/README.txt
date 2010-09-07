Basic Information for Qim Image viewer
---------------------------------------

core/ 		- CoreEngine source
manager/ 	- Theme, plug-in manager source
plugin/ 	- plug-in sources
theme/  	- theme descriptor sources
theme/lang/ - language files for app translation and internationalization

debug/  	- debug version compiled source
debug/theme/lang/qim_lang_de_DE.qm 
			- is required for translation in debug mode
release/ 	- release version compiled source
release/imageformats/
			- is required to display different image files
			  each fileformat needs the according format plugin
release/theme/lang/qim_lang_de_DE.qm 
			- is required for translation in release mode
libs/ 		- external libraries 

Additional notes
----------------------------------------

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