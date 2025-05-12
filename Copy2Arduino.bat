@echo off
::
::C:\Users\gustav.wiberg\Documents\GitHub\ECi\MassFlow_Sensiron_SFC6xxxx\Copy2Arduino.bat
set Folder=MassFlow_Sensirion_SFC6xxxx

echo %Folder%
set GitHub=%UserProfile%\Documents\GitHub
set SRCPath=%UserProfile%\Documents\GitHub\ECi\%Folder%
set SRCPath_SRC=%SRCPath%\src
set SRCPath_EXA=%SRCPath%\examples
set ArduinoLibPath=%UserProfile%\Documents\Arduino\libraries\%Folder%
set ArduinoLibPath_SRC=%ArduinoLibPath%\src
set ArduinoLibPath_EXA=%ArduinoLibPath%\examples

::
echo %SRCPath%
::
mkdir %ArduinoLibPath%
mkdir %ArduinoLibPath_SRC%
::mkdir %ArduinoLibPath_SRC%\server
mkdir %ArduinoLibPath_SRC%\util
::mkdir %ArduinoLibPath_SRC%\com
::mkdir %ArduinoLibPath_SRC%\base
mkdir %ArduinoLibPath_EXA%
::
echo %ArduinoLibPath_SRC%
echo %SRCPath%
:: %ArduinoLibPath_SRC%\*.*
::
echo "copying: %SRCPath%\lib*.*"
copy "%SRCPath%\lib*.*" "%ArduinoLibPath%"
copy "%SRCPath_SRC%\*.*" "%ArduinoLibPath_SRC%"
::copy "%SRCPath_SRC%\server\*.*" "%ArduinoLibPath_SRC%\server"
::copy "%SRCPath_SRC%\util\*.*" "%ArduinoLibPath_SRC%\util"
::copy "%SRCPath_SRC%\com\*.*" "%ArduinoLibPath_SRC%\com"
::copy "%SRCPath_SRC%\base\*.*" "%ArduinoLibPath_SRC%\base"


::@ECHO OFF
echo /////////////////////////////////////Copy other files
cmd /c "%GitHub%\Virtual_Instrument\Copy2Arduino.bat"
