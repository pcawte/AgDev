setlocal

set ORIGDIR="%cd%"
set BASEDIR=%cd%\_temp
set GITHUB=%BASEDIR%\github

if not exist %BASEDIR% mkdir %BASEDIR%
if not exist %GITHUB% mkdir %GITHUB%

Rem I don't feel guilty about requiring a recent version of Powershell... see below
if not exist %BASEDIR%\Cedev_zip powershell -Command "(New-Object Net.WebClient).DownloadFile('https://github.com/CE-Programming/toolchain/releases/latest/download/CEdev-Windows.zip', '%BASEDIR%\Cedev-Windows.zip')"
if not exist %BASEDIR%\Cedev_zip powershell -Command "Invoke-WebRequest https://github.com/CE-Programming/toolchain/releases/latest/download/CEdev-Windows.zip -OutFile %BASEDIR%\Cedev-Windows.zip"

cd "%BASEDIR%"
Rem Either we use this Win10-and-up command, or tar (also Win10), or we embed VBScript... this seems best for now
if not exist %BASEDIR%\Cedev_zip powershell -Command "Expand-Archive -Force %BASEDIR%\Cedev-Windows.zip %BASEDIR%"
if not exist %BASEDIR%\Cedev_zip rename %BASEDIR%\CEdev CEdev_zip
del %BASEDIR%\Cedev-Windows.zip

Rem get AgDev code
cd %GITHUB%
if exist %GITHUB%\AgDev_git rmdir /s /q \\?\%GITHUB%\AgDev_git
Rem was a local location for AgDev code passed to us?
if not "%1"=="" (
    robocopy "%1" "%GITHUB%\AgDev_git" /e
) else (
    git clone https://github.com/pcawte/AgDev.git AgDev_git
)

set AGDEV_GIT=%GITHUB%\AgDev_git

Rem get CEdev code - using a recent stable release
cd %GITHUB%
set CEDEV_GIT=%GITHUB%\CEdev_git
if not exist %CEDEV_GIT%  (
    mkdir %CEDEV_GIT%
    git clone https://github.com/CE-Programming/toolchain.git CEdev_git --branch v11.2
    cd %CEDEV_GIT%
    git switch -c tmp
    git switch master
    git merge tmp
    git submodule update --init --recursive
)

Rem Duplicate CEdev repo - this will become the basis for the final build
if exist %BASEDIR%\CEDEV_PLUS_AGDEV rmdir /s /q \\?\%BASEDIR%\CEDEV_PLUS_AGDEV
mkdir %BASEDIR%\CEDEV_PLUS_AGDEV
set CEDEV_PLUS_AGDEV=%BASEDIR%\CEDEV_PLUS_AGDEV
robocopy "%CEDEV_GIT% " "%CEDEV_PLUS_AGDEV% " /e

Rem Move some stuff around in /src
Rem the /agon folder in AgDev is based on the /ce folder in CEdev, but with CE-specific stuff removed and Agon-specific stuff added
mkdir %CEDEV_PLUS_AGDEV%\src\agon
robocopy %CEDEV_PLUS_AGDEV%\src\ce %CEDEV_PLUS_AGDEV%\src\agon
cd %CEDEV_PLUS_AGDEV%\src\agon
del eval.src
del getstringinput.src
del gettokeninput.src
del intce.src
del tice.src
del os_textbuffer.src
del runprgm.src

Rem now that we've copied its contents, we don't need /ce anymore
rmdir /s /q  %CEDEV_PLUS_AGDEV%\src\ce

Rem delete CEdev allocator code, since AgDev uses its own
del "%CEDEV_PLUS_AGDEV%\src\libc\allocator.src"
del "%CEDEV_PLUS_AGDEV%\src\libc\allocator_simple.src"
del "%CEDEV_PLUS_AGDEV%\src\libc\allocator_standard.c"

Rem delete misc .c files which had handmade asm edits made for AgDev - we will copy over these prebuilt .src files in the next step
del "%CEDEV_PLUS_AGDEV%\src\libc\time.c"
del "%CEDEV_PLUS_AGDEV%\src\libc\strftime.c"

Rem copy over AgDev source files and build instructions
robocopy "%AGDEV_GIT%" "%CEDEV_PLUS_AGDEV%" makefile
robocopy "%AGDEV_GIT%\src " "%CEDEV_PLUS_AGDEV%\src" /e

Rem vdp headers need to be in 2 places for some reason
robocopy "%AGDEV_GIT%\src\agon\include\agon" "%CEDEV_PLUS_AGDEV%\src\include\agon"

Rem Remove the previous build directory and make
cd %CEDEV_PLUS_AGDEV%
if exist %CEDEV_PLUS_AGDEV%\CEdev rmdir /s /q "%CEDEV_PLUS_AGDEV%\CEdev"
mkdir "%CEDEV_PLUS_AGDEV%\CEdev"
SET PATH=%PATH%;c:%BASEDIR%\CEdev_zip\bin

"%CEDEV_PLUS_AGDEV%/resources/windows/make.exe" -d install

Rem copy over .exe's from CEdev release - CEdev GitHub actions pull each .exe's repo and build, but we shouldn't need to do that.
robocopy "%BASEDIR%\CEdev_zip\bin" "%CEDEV_PLUS_AGDEV%\CEdev\bin" /e

Rem copy over AgDev example folders
robocopy "%GITHUB%\AgDev_git\AgExamples" "%CEDEV_PLUS_AGDEV%\CEdev\AgExamples" /e
robocopy "%GITHUB%\AgDev_git\sprite-demos" "%CEDEV_PLUS_AGDEV%\CEdev\sprite-demos" /e
robocopy "%GITHUB%\AgDev_git\tests" "%CEDEV_PLUS_AGDEV%\CEdev\tests" /e

Rem copy resulting build to base directory
robocopy "%CEDEV_PLUS_AGDEV%\CEdev" "%ORIGDIR%" /e

Rem clean folders up at the end - TODO make optional
cd "%ORIGDIR%"
Rem rmdir "%BASEDIR%" /s /q

endlocal
