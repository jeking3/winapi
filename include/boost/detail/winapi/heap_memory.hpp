//  heap_memory.hpp  --------------------------------------------------------------//

//  Copyright 2010 Vicente J. Botet Escriba
//  Copyright 2015, 2017 Andrey Semashev

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt


#ifndef BOOST_DETAIL_WINAPI_HEAP_MEMORY_HPP_
#define BOOST_DETAIL_WINAPI_HEAP_MEMORY_HPP_

#include <boost/detail/winapi/basic_types.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined( BOOST_USE_WINDOWS_H )
#undef HeapAlloc
extern "C" {

#if BOOST_WINAPI_PARTITION_DESKTOP_SYSTEM
BOOST_SYMBOL_IMPORT boost::detail::winapi::DWORD_ WINAPI
GetProcessHeaps(boost::detail::winapi::DWORD_ NumberOfHeaps, boost::detail::winapi::PHANDLE_ ProcessHeaps);
#endif // BOOST_WINAPI_PARTITION_DESKTOP_SYSTEM

BOOST_SYMBOL_IMPORT boost::detail::winapi::HANDLE_ WINAPI
GetProcessHeap(BOOST_DETAIL_WINAPI_VOID);

BOOST_SYMBOL_IMPORT boost::detail::winapi::LPVOID_ WINAPI
HeapAlloc(
    boost::detail::winapi::HANDLE_ hHeap,
    boost::detail::winapi::DWORD_ dwFlags,
    boost::detail::winapi::SIZE_T_ dwBytes);

BOOST_SYMBOL_IMPORT boost::detail::winapi::BOOL_ WINAPI
HeapFree(
    boost::detail::winapi::HANDLE_ hHeap,
    boost::detail::winapi::DWORD_ dwFlags,
    boost::detail::winapi::LPVOID_ lpMem);

BOOST_SYMBOL_IMPORT boost::detail::winapi::LPVOID_ WINAPI
HeapReAlloc(
    boost::detail::winapi::HANDLE_ hHeap,
    boost::detail::winapi::DWORD_ dwFlags,
    boost::detail::winapi::LPVOID_ lpMem,
    boost::detail::winapi::SIZE_T_ dwBytes);

#if BOOST_WINAPI_PARTITION_APP_SYSTEM
BOOST_SYMBOL_IMPORT boost::detail::winapi::HANDLE_ WINAPI
HeapCreate(
    boost::detail::winapi::DWORD_ flOptions,
    boost::detail::winapi::SIZE_T_ dwInitialSize,
    boost::detail::winapi::SIZE_T_ dwMaximumSize);

BOOST_SYMBOL_IMPORT boost::detail::winapi::BOOL_ WINAPI
HeapDestroy(boost::detail::winapi::HANDLE_ hHeap);
#endif // BOOST_WINAPI_PARTITION_APP_SYSTEM

} // extern "C"
#endif // !defined( BOOST_USE_WINDOWS_H )

namespace boost {
namespace detail {
namespace winapi {

#if BOOST_WINAPI_PARTITION_DESKTOP_SYSTEM
using ::GetProcessHeaps;
#endif

using ::GetProcessHeap;
using ::HeapAlloc;
using ::HeapFree;
using ::HeapReAlloc;

#if BOOST_WINAPI_PARTITION_APP_SYSTEM
using ::HeapCreate;
using ::HeapDestroy;
#endif

}
}
}

#endif // BOOST_DETAIL_WINAPI_HEAP_MEMORY_HPP_
