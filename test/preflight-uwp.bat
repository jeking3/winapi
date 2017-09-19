REM Batch script to locally qualify winapi changes.
REM You need Visual Studio 2010, 2012, 2013, 2017
REM Run from winapi\test
REM This is essentially what part of the appveyor script does in CI

:: no UWP support in SDK 7.0A
..\..\..\b2 toolset=msvc-10.0 clean || EXIT /B
..\..\..\b2 toolset=msvc-10.0 -j5 -q || EXIT /B

:: SDK 8.0 has early UWP support
..\..\..\b2 toolset=msvc-11.0 define="_WIN32_WINNT=0x0602" define="WINAPI_FAMILY=WINAPI_FAMILY_APP" clean || EXIT /B
..\..\..\b2 toolset=msvc-11.0 define="_WIN32_WINNT=0x0602" define="WINAPI_FAMILY=WINAPI_FAMILY_APP" -j5 -q || EXIT /B
..\..\..\b2 toolset=msvc-11.0 define="_WIN32_WINNT=0x0602" define="WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP" clean || EXIT /B
..\..\..\b2 toolset=msvc-11.0 define="_WIN32_WINNT=0x0602" define="WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP" -j5 -q || EXIT /B

:: SDK 8.1 adds phone
..\..\..\b2 toolset=msvc-12.0 define="_WIN32_WINNT=0x0603" define="WINAPI_FAMILY=WINAPI_FAMILY_PC_APP" clean || EXIT /B
..\..\..\b2 toolset=msvc-12.0 define="_WIN32_WINNT=0x0603" define="WINAPI_FAMILY=WINAPI_FAMILY_PC_APP" -j5 -q || EXIT /B
..\..\..\b2 toolset=msvc-12.0 define="_WIN32_WINNT=0x0603" define="WINAPI_FAMILY=WINAPI_FAMILY_PHONE_APP" clean || EXIT /B
..\..\..\b2 toolset=msvc-12.0 define="_WIN32_WINNT=0x0603" define="WINAPI_FAMILY=WINAPI_FAMILY_PHONE_APP" -j5 -q || EXIT /B
..\..\..\b2 toolset=msvc-12.0 define="_WIN32_WINNT=0x0603" define="WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP" clean || EXIT /B
..\..\..\b2 toolset=msvc-12.0 define="_WIN32_WINNT=0x0603" define="WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP" -j5 -q || EXIT /B

:: SDK 10
..\..\..\b2 toolset=msvc-14.1 define="_WIN32_WINNT=0x0A00" define="WINAPI_FAMILY=WINAPI_FAMILY_PC_APP" clean || EXIT /B
..\..\..\b2 toolset=msvc-14.1 define="_WIN32_WINNT=0x0A00" define="WINAPI_FAMILY=WINAPI_FAMILY_PC_APP" -j5 -q || EXIT /B
..\..\..\b2 toolset=msvc-14.1 define="_WIN32_WINNT=0x0A00" define="WINAPI_FAMILY=WINAPI_FAMILY_PHONE_APP" clean || EXIT /B
..\..\..\b2 toolset=msvc-14.1 define="_WIN32_WINNT=0x0A00" define="WINAPI_FAMILY=WINAPI_FAMILY_PHONE_APP" -j5 -q || EXIT /B
..\..\..\b2 toolset=msvc-14.1 define="_WIN32_WINNT=0x0A00" define="WINAPI_FAMILY=WINAPI_FAMILY_SYSTEM" clean || EXIT /B
..\..\..\b2 toolset=msvc-14.1 define="_WIN32_WINNT=0x0A00" define="WINAPI_FAMILY=WINAPI_FAMILY_SYSTEM" -j5 -q || EXIT /B
..\..\..\b2 toolset=msvc-14.1 define="_WIN32_WINNT=0x0A00" define="WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP" clean || EXIT /B
..\..\..\b2 toolset=msvc-14.1 define="_WIN32_WINNT=0x0A00" define="WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP" -j5 -q || EXIT /B

