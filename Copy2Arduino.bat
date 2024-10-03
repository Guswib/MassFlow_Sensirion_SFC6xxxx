@echo off
::
::
set Folder=ECi_SystemLogger
echo %Folder%
set SRCPath=%UserProfile%\Documents\GitHub\%Folder%
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
mkdir %ArduinoLibPath_SRC%\server
mkdir %ArduinoLibPath_SRC%\util
mkdir %ArduinoLibPath_SRC%\com
mkdir %ArduinoLibPath_SRC%\base
mkdir %ArduinoLibPath_EXA%
::
echo %ArduinoLibPath_SRC%
echo %SRCPath%
:: %ArduinoLibPath_SRC%\*.*
::
copy "%SRCPath%\lib*.*" "%ArduinoLibPath%"
copy "%SRCPath_SRC%\*.*" "%ArduinoLibPath_SRC%"
copy "%SRCPath_SRC%\server\*.*" "%ArduinoLibPath_SRC%\server"
copy "%SRCPath_SRC%\util\*.*" "%ArduinoLibPath_SRC%\util"
copy "%SRCPath_SRC%\com\*.*" "%ArduinoLibPath_SRC%\com"
copy "%SRCPath_SRC%\base\*.*" "%ArduinoLibPath_SRC%\base"


set GitHub=%UserProfile%\Documents\GitHub
::@ECHO OFF
echo /////////////////////////////////////Copy other files
cmd /c "%GitHub%\Virtual_Instrument\Copy2Arduino.bat"
 echo /////////////////////////////////////Pressure_Transducer_M3200
cmd /c "%GitHub%\Pressure_Transducer_M3200\Copy2Arduino.bat"
 echo /////////////////////////////////////Temperature-Ctrl_DTB
cmd /c "%GitHub%\Temperature-Ctrl_DTB\Copy2Arduino.bat"
 echo /////////////////////////////////////HMM170
cmd /c "%GitHub%\HMM170\Copy2Arduino.bat"
 echo /////////////////////////////////////Temperature_Transducer_MAX31865

cmd /c "%GitHub%\Temperature_Transducer_MAX31865\Copy2Arduino.bat"

::copy "%SRCPath_EXA%\Virtual*.*" "%ArduinoLibPath_SRC%"
::copy "C:\Users\Gustav\Documents\GitHub\Virtual_Potentiostat\src\Virtual*" "C:\Users\Gustav\Documents\Arduino\libraries\Virtual_Potentiostat\src" /Y
::copy "C:\Users\Gustav\Documents\GitHub\Virtual_Potentiostat\library.*" "C:\Users\Gustav\Documents\Arduino\libraries\Virtual_Potentiostat" /Y
::copy "C:\Users\Gustav\Documents\GitHub\Virtual_Potentiostat\examples\Virtual_Potentiostat\*" "C:\Users\Gustav\Documents\Arduino\libraries\Virtual_Potentiostat\examples\Virtual_Potentiostat" /Y
    
::copy "C:\Users\gustav.wiberg\Documents\GitHub\Virtual_Potentiostat\src\Virtual*" "C:\Users\gustav.wiberg\Documents\Arduino\libraries\Virtual_Potentiostat\src" /Y
::copy "C:\Users\gustav.wiberg\Documents\GitHub\Virtual_Potentiostat\library.*" "C:\Users\gustav.wiberg\Documents\Arduino\libraries\Virtual_Potentiostat" /Y
::copy "C:\Users\gustav.wiberg\Documents\GitHub\Virtual_Potentiostat\examples\Virtual_Potentiostat\*" "C:\Users\gustav.wiberg\Documents\Arduino\libraries\Virtual_Potentiostat\examples\Virtual_Potentiostat" /Y
    