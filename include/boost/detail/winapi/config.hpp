//  config.hpp  --------------------------------------------------------------//

//  Copyright 2013 Andrey Semashev
//  Copyright 2017 James E. King, III

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt


#ifndef BOOST_DETAIL_WINAPI_CONFIG_HPP_INCLUDED_
#define BOOST_DETAIL_WINAPI_CONFIG_HPP_INCLUDED_

#if defined __MINGW32__
#include <_mingw.h>
#endif

// BOOST_WINAPI_IS_MINGW indicates that the target Windows SDK is provided by MinGW (http://mingw.org/).
// BOOST_WINAPI_IS_MINGW_W64 indicates that the target Windows SDK is provided by MinGW-w64 (http://mingw-w64.org).
#if defined __MINGW32__
#if defined __MINGW64_VERSION_MAJOR
#define BOOST_WINAPI_IS_MINGW_W64
#else
#define BOOST_WINAPI_IS_MINGW
#endif
#endif

// These constants reflect _WIN32_WINNT_* macros from sdkddkver.h and will not change over time
// See also: http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745%28v=vs.85%29.aspx#setting_winver_or__win32_winnt
#define BOOST_WINAPI_VERSION_NT4 0x0400
#define BOOST_WINAPI_VERSION_WIN2K 0x0500
#define BOOST_WINAPI_VERSION_WINXP 0x0501
#define BOOST_WINAPI_VERSION_WS03 0x0502
#define BOOST_WINAPI_VERSION_WIN6 0x0600
#define BOOST_WINAPI_VERSION_VISTA 0x0600
#define BOOST_WINAPI_VERSION_WS08 0x0600
#define BOOST_WINAPI_VERSION_LONGHORN 0x0600
#define BOOST_WINAPI_VERSION_WIN7 0x0601
#define BOOST_WINAPI_VERSION_WIN8 0x0602
#define BOOST_WINAPI_VERSION_WINBLUE 0x0603
#define BOOST_WINAPI_VERSION_WINTHRESHOLD 0x0A00
#define BOOST_WINAPI_VERSION_WIN10 0x0A00

#if !defined(BOOST_USE_WINAPI_VERSION)
#if defined(_WIN32_WINNT)
#define BOOST_USE_WINAPI_VERSION _WIN32_WINNT
#elif defined(WINVER)
#define BOOST_USE_WINAPI_VERSION WINVER
#else
// By default use Windows Vista API on compilers that support it and XP on the others
#if (defined(_MSC_VER) && _MSC_VER < 1500) || defined(BOOST_WINAPI_IS_MINGW)
#define BOOST_USE_WINAPI_VERSION BOOST_WINAPI_VERSION_WINXP
#else
#define BOOST_USE_WINAPI_VERSION BOOST_WINAPI_VERSION_WIN6
#endif
#endif
#endif

//
// Detect the version of the Windows SDK in use
//

#if !defined(BOOST_WINAPI_IS_MINGW)
#include <ntverp.h>
#define BOOST_WINAPI_WINDOWS_SDK            VER_PRODUCTBUILD
#else
#define BOOST_WINAPI_WINDOWS_SDK            0
#endif

// These constants reflect known kit versions
#define BOOST_WINAPI_WINDOWS_SDK_MINGW_W64  3790    /* https://github.com/Alexpux/mingw-w64/blame/master/mingw-w64-headers/include/ntverp.h */
#define BOOST_WINAPI_WINDOWS_SDK_7          7600    /* covers 7.0, 7.1A */
#define BOOST_WINAPI_WINDOWS_SDK_8          9200
#define BOOST_WINAPI_WINDOWS_SDK_8_1        9600
#define BOOST_WINAPI_WINDOWS_SDK_10         10011   /* covers all 10.0.<buildnum> */

//
// Windows family partitions - support for Windows Store, Windows Phone,
// Windows Server, Windows Desktop differentiation in the API set.  They are only
// meaningful if the Windows SDK has support for the concept.  The headers provided
// are simple and do not pull in much, and they are quite different on certain SDKs.
// Not available in older MinGW or on Windows SDK 7.x or earlier, and Windows SDK
// 8.0 is quite different from 8.1 and later.
//

#if defined(BOOST_WINAPI_IS_MINGW_W64) || (BOOST_WINAPI_WINDOWS_SDK >= BOOST_WINAPI_WINDOWS_SDK_8)
#include <winapifamily.h>

#if !defined(BOOST_USE_WINAPI_FAMILY)
#if defined(WINAPI_FAMILY)
#define BOOST_USE_WINAPI_FAMILY WINAPI_FAMILY
#else
// If none is specified, default to a desktop application which is the most
// backwards compatible to previos ways of doing things.
#define BOOST_USE_WINAPI_FAMILY WINAPI_FAMILY_DESKTOP_APP
#endif
#endif
// Note that BOOST_USE_WINAPI_FAMILY may not have a definition, 
// for example with SDK 7, and we account for this below.
#endif

//
// UWP Support
// These convenience macros work under any SDK whether it has family support
// or not.  They will:
//
// A) check if family support exists
// B) check the specific partition is selected
//
// On platforms without windows family partition support it is assumed one 
// has desktop APIs.
//

// Preprocessor behavior is undefined if a defined() is inside a macro, so:
#if defined(_INC_WINAPIFAMILY)
#define BOOST_WINAPI_UWP_AWARE 1
#else
#define BOOST_WINAPI_UWP_AWARE 0
#endif

#if (!BOOST_WINAPI_UWP_AWARE)

// Lack of any family support means all APIs are controlled by _WIN32_WINNT and other
// similar controls.

#define BOOST_WINAPI_PARTITION_APP           (1)
#define BOOST_WINAPI_PARTITION_PC            (1)
#define BOOST_WINAPI_PARTITION_PHONE         (0)
#define BOOST_WINAPI_PARTITION_SYSTEM        (1)
#define BOOST_WINAPI_PARTITION_DESKTOP       (1)
#define BOOST_WINAPI_PARTITION_DESKTOP_STORE (1)

#else

// Desktop Win32 apps (but not store apps) - this is the least restrictive partition and
// is essentially the same as SDKs before families were introduced.
#define BOOST_WINAPI_PARTITION_DESKTOP   (WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP))

// Windows Universal store apps
#define BOOST_WINAPI_PARTITION_APP       (WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP))

// Desktop-only store apps
#if !defined(WINAPI_PARTITION_PC_APP)
#define BOOST_WINAPI_PARTITION_PC        (0)
#else
#define BOOST_WINAPI_PARTITION_PC        (WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_PC_APP))
#endif

// Phone-only store apps
#if !defined(WINAPI_PARTITION_PHONE_APP)
#define BOOST_WINAPI_PARTITION_PHONE     (0)
#else
#define BOOST_WINAPI_PARTITION_PHONE     (WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_PHONE_APP))
#endif

// System apps
#if !defined(WINAPI_PARTITION_SYSTEM)
#define BOOST_WINAPI_PARTITION_SYSTEM    (0)
#else
#define BOOST_WINAPI_PARTITION_SYSTEM    (WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_SYSTEM))
#endif

//
// Windows 8.x SDK defines some items in the DESKTOP and then Windows SDK 10.0 defines the same
// items to be in APP or SYSTEM, and APP expands to DESKTOP or PC or PHONE.  The definition of
// BOOST_WINAPI_PARTITION_DESKTOP_STORE provides a universal way to get this right as it is
// seen in a number of places in the SDK.
//

#define BOOST_WINAPI_PARTITION_DESKTOP_STORE ( \
        ((BOOST_WINAPI_WINDOWS_SDK >= BOOST_WINAPI_WINDOWS_SDK_10) && (BOOST_WINAPI_PARTITION_APP || BOOST_WINAPI_PARTITION_SYSTEM)) || \
        ((BOOST_WINAPI_WINDOWS_SDK < BOOST_WINAPI_WINDOWS_SDK_10) && BOOST_WINAPI_PARTITION_DESKTOP) \
    )

#endif // (!BOOST_WINAPI_UWP_AWARE)


#define BOOST_DETAIL_WINAPI_MAKE_NTDDI_VERSION2(x) x##0000
#define BOOST_DETAIL_WINAPI_MAKE_NTDDI_VERSION(x) BOOST_DETAIL_WINAPI_MAKE_NTDDI_VERSION2(x)

#if defined(BOOST_USE_WINDOWS_H) || defined(BOOST_WINAPI_DEFINE_VERSION_MACROS)
// We have to define the version macros so that windows.h provides the necessary symbols
#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT BOOST_USE_WINAPI_VERSION
#endif
#if !defined(WINVER)
#define WINVER BOOST_USE_WINAPI_VERSION
#endif
#if !defined(NTDDI_VERSION)
// Default to respective Windows version with the latest Service Pack
#if BOOST_USE_WINAPI_VERSION == BOOST_WINAPI_VERSION_WIN2K
#define NTDDI_VERSION 0x05000400
#elif BOOST_USE_WINAPI_VERSION == BOOST_WINAPI_VERSION_WINXP
#define NTDDI_VERSION 0x05010300
#elif BOOST_USE_WINAPI_VERSION == BOOST_WINAPI_VERSION_WS03
#define NTDDI_VERSION 0x05020200
#elif BOOST_USE_WINAPI_VERSION == BOOST_WINAPI_VERSION_WIN6
#define NTDDI_VERSION 0x06000200
#elif BOOST_USE_WINAPI_VERSION == BOOST_WINAPI_VERSION_WIN7
#define NTDDI_VERSION 0x06010100
#else
#define NTDDI_VERSION BOOST_DETAIL_WINAPI_MAKE_NTDDI_VERSION(BOOST_USE_WINAPI_VERSION)
#endif
#if !defined(WINAPI_FAMILY) && defined(BOOST_USE_WINAPI_FAMILY)
#define WINAPI_FAMILY BOOST_USE_WINAPI_FAMILY
#endif
#endif
#endif

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_DETAIL_WINAPI_CONFIG_HPP_INCLUDED_
