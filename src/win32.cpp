#ifndef _LIB_PLATFORM_WIN32_H_
#define _LIB_PLATFORM_WIN32_H_
#include "libplatform.h"
using namespace foxintango;

#ifdef PLATFORM_WIN
#ifdef PLATFORM_WIN32_API
PlatformEventReactor::PlatformEventReactor() {}
PlatformEventReactor::~PlatformEventReactor() {}
#endif

#ifdef PLATFORM_WIN32_KPI
PlatformEventReactor::PlatformEventReactor() {}
PlatformEventReactor::~PlatformEventReactor() {}
#endif
#endif // PLATFORM_WIN

#endif //_LIB_PLATFORM_WIN32_H_