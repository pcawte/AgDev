setlocal

set ORIGDIR=%cd%
set BASEDIR=%cd%\build
set GITHUB=%BASEDIR%\github

if not exist %BASEDIR% mkdir %BASEDIR%
if not exist %GITHUB% mkdir %GITHUB%

if not exist %BASEDIR%\Cedev-Windows.zip powershell -Command "(New-Object Net.WebClient).DownloadFile('https://github.com/CE-Programming/toolchain/releases/latest/download/CEdev-Windows.zip', '%BASEDIR%\Cedev-Windows.zip')"
if not exist %BASEDIR%\Cedev-Windows.zip powershell -Command "Invoke-WebRequest https://github.com/CE-Programming/toolchain/releases/latest/download/CEdev-Windows.zip -OutFile %BASEDIR%\Cedev-Windows.zip"
set CEDEV_ZIP=%BASEDIR%\Cedev-Windows.zip

Rem this is where your AgDev build will end up
set AGDEV_FINAL=%BASEDIR%\AgDev_final

Rem before you start you must have the modified CEdev extracted and CEdev/bin in your path. this is so it can find the ez80-clang compiler
cd %BASEDIR%
Rem Either we use this Win10-and-up command, or tar (also Win10), or we embed a VB script... this seems best for now
powershell -Command "Expand-Archive -Force %CEDEV_ZIP% %BASEDIR%"
SET PATH=%PATH%;c:%BASEDIR%\CEdev\bin


Rem get latest AgDev code - Only do this if you want AgDev updates
cd %GITHUB%
if exist %GITHUB%\AgDev rd /s /q "\\?\%GITHUB%\AgDev"
git clone https://github.com/pcawte/AgDev.git

set AGDEV_GIT=%BASEDIR%\github\AgDev

Rem get latest CEdev code - Only do this if you want toolchain updates
cd %GITHUB%
if exist %GITHUB%\CEdev  rd /s /q "\\?\%GITHUB%\CEdev"
git clone https://github.com/CE-Programming/toolchain.git CEdev
cd CEdev
git submodule update --init --recursive

set CEDEV_GIT=%GITHUB%\CEdev


Rem ----------------------------------------
Rem Copy in AgDev code to CEdev toolchain code
Rem ----------------------------------------
robocopy "%AGDEV_GIT%\src " "%CEDEV_GIT%\src " /e
robocopy "%AGDEV_GIT%\include " "%CEDEV_GIT%\include " /e


Rem Remove the previous build directory and make
cd %CEDEV_GIT%
if exist %CEDEV_GIT%\CEdev rd /s /q "%CEDEV_GIT%\CEdev"
"%CEDEV_GIT%/resources/windows/make.exe" install



Rem will result in a install directory %CEDEV_GIT%/CEdev/CEdev because of the strange way the AgDev common.mk file sets up the install directories

Rem ----------------------------------------
Rem Install
Rem ----------------------------------------

Rem delete previous final directory
if exist %AGDEV_FINAL% rd /s /q %AGDEV_FINAL%

Rem Get the full version of CEdev from the ZIP file
mkdir tmp
cd tmp
if exist %cd%\CEdev rd /s /q "%cd%\CEdev"
powershell -Command "Expand-Archive -Force %CEDEV_ZIP% %cd%"
move %cd%\CEdev %AGDEV_FINAL%

Rem ... but now we can get our modified version
robocopy "%CEDEV_GIT%\CEdev\CEdev" "%AGDEV_FINAL%" /e

Rem Copy over the AgDev stuff - this includes the ez80_clang compiler and example code
robocopy "%AGDEV_GIT%" "%AGDEV_FINAL%"

Rem now copy over the built binaries and libraries
robocopy "%CEDEV_GIT%\CEdev\CEdev\bin" "%AGDEV_FINAL%\bin" /S
robocopy "%CEDEV_GIT%\CEdev\CEdev\lib\libc" "%AGDEV_FINAL%\lib\agon" vdp* /e

Rem finally copy the modified headers to the include directory
robocopy "%AGDEV_FINAL%\src\libc\include" "%AGDEV_FINAL%\include\agon" vdp*.h /e
robocopy "%CEDEV_GIT%\src\libc\include" "%AGDEV_FINAL%\include\agon" vdp*.h /e

cd %ORIGDIR%

endlocal
