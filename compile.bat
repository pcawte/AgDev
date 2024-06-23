setlocal

set ORIGDIR=%cd%
set BASEDIR=%cd%\_temp
set GITHUB=%BASEDIR%\github

if not exist %BASEDIR% mkdir %BASEDIR%
if not exist %GITHUB% mkdir %GITHUB%

Rem I don't feel guilty about requiring a recent version of Powershell... see below
if not exist %BASEDIR%\Cedev-Windows.zip powershell -Command "(New-Object Net.WebClient).DownloadFile('https://github.com/CE-Programming/toolchain/releases/latest/download/CEdev-Windows.zip', '%BASEDIR%\Cedev-Windows.zip')"
if not exist %BASEDIR%\Cedev-Windows.zip powershell -Command "Invoke-WebRequest https://github.com/CE-Programming/toolchain/releases/latest/download/CEdev-Windows.zip -OutFile %BASEDIR%\Cedev-Windows.zip"

Rem this is where your AgDev build will end up
set AGDEV_FINAL=%BASEDIR%\AgDev_final

cd %BASEDIR%
Rem Either we use this Win10-and-up command, or tar (also Win10), or we embed VBScript... this seems best for now
powershell -Command "Expand-Archive -Force %BASEDIR%\Cedev-Windows.zip %BASEDIR%"
rename "%BASEDIR%\CEdev" CEdev_zip
del %BASEDIR%\Cedev-Windows.zip

Rem get AgDev code
cd %GITHUB%
if exist %GITHUB%\AgDev_git rmdir /s /q "\\?\%GITHUB%\AgDev_git"
Rem was a local location for AgDev code passed to us?
if not "%1"=="" (
    robocopy "%1" "%GITHUB%\AgDev_git" /e
) else (
    git clone https://github.com/pcawte/AgDev.git AgDev_git
)

set AGDEV_GIT=%BASEDIR%\github\AgDev_git

Rem get CEdev code - using a recent stable release
cd %GITHUB%
set CEDEV_GIT=%GITHUB%\CEdev_git
if exist %CEDEV_GIT%  rmdir /s /q "\\?\%CEDEV_GIT%"
git clone https://github.com/CE-Programming/toolchain.git CEdev_git --branch v11.2
cd %CEDEV_GIT%
git switch -c tmp
git switch master
git merge tmp
git submodule update --init --recursive

Rem Duplicate CEdev repo - this will become the basis for the final build
if exist %BASEDIR%\CEDEV_PLUS_AGDEV rmdir /s /q "\\?\%BASEDIR%\CEDEV_PLUS_AGDEV"
mkdir "%BASEDIR%\CEDEV_PLUS_AGDEV"
set CEDEV_PLUS_AGDEV=%BASEDIR%\CEDEV_PLUS_AGDEV
robocopy "%CEDEV_GIT% " "%CEDEV_PLUS_AGDEV% " /e

Rem Move some stuff around in /src
Rem the /agon folder in AgDev is based on the /ce folder in CEdev, but with CE-specific stuff removed and Agon-specific stuff added
Rem however, other CEdev files not in /ce link against /ce, so we need to keep it around... at least at build time
mkdir "%CEDEV_PLUS_AGDEV%\src\agon"
robocopy "%CEDEV_PLUS_AGDEV%\src\ce" "%CEDEV_PLUS_AGDEV%\src\agon"
cd "%CEDEV_PLUS_AGDEV%\src\agon"
del eval.src
del getstringinput.src
del gettokeninput.src
del intce.src
del tice.src
del os_textbuffer.src
del runprgm.src

Rem delete printf.src since it's been superceded by nanoprintf and it causes a linker error if we leave it
del "%CEDEV_PLUS_AGDEV%\src\libc\printf.src"

Rem copy over AgDev source files and build instructions
robocopy "%AGDEV_GIT%" "%CEDEV_PLUS_AGDEV%" makefile
robocopy "%AGDEV_GIT%\src " "%CEDEV_PLUS_AGDEV%\src" /e
Rem vdp headers seem like they need to be in 2 places. TODO can this be avoided?
robocopy "%AGDEV_GIT%\src\agon\include\agon" "%CEDEV_PLUS_AGDEV%\src\include\agon"

Rem Remove the previous build directory and make
cd %CEDEV_PLUS_AGDEV%
if exist %CEDEV_PLUS_AGDEV%\CEdev rmdir /s /q "%CEDEV_PLUS_AGDEV%\CEdev"
mkdir "%CEDEV_PLUS_AGDEV%\CEdev"
SET PATH=%PATH%;c:%BASEDIR%\CEdev_zip\bin

"%CEDEV_PLUS_AGDEV%/resources/windows/make.exe" install

Rem copy over .exe's from CEdev release - TODO investigate why they don't show up automatically
robocopy "%BASEDIR%\CEdev_zip\bin" "%CEDEV_PLUS_AGDEV%\CEdev\bin" /e

Rem copy resulting build to root directory
robocopy "%CEDEV_PLUS_AGDEV%\CEdev" "%ORIGDIR%" /e

Rem clean folders up at the end
Rem rmdir "%BASEDIR%" /s /q

endlocal
