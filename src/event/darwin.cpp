#ifndef _LIB_PLATFORM_DARWIN_H_
#define _LIB_PLATFORM_DARWIN_H_
#include "../libplatform.h"
using namespace foxintango;

#ifdef PLATFORM_DARWIN
#ifdef PLATFORM_DARWIN_API
PlatformEventReactor::PlatformEventReactor() {}
PlatformEventReactor::~PlatformEventReactor() {}
#endif

#ifdef PLATFORM_DARWIN_KPI
PlatformEventReactor::PlatformEventReactor() {}
PlatformEventReactor::~PlatformEventReactor() {}
#endif
#endif //PLATFORM_DARWIN

#endif //_LIB_PLATFORM_DARWIN_H_