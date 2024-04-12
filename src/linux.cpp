#ifndef _LIB_PLATFORM_LINUX_H_
#define _LIB_PLATFORM_LINUX_H_

#include "libplatform.h"
using namespace foxintango;

#ifdef PLATFORM_LINUX
#ifdef PLATFORM_LINUX_API
PlatformEventReactor::PlatformEventReactor() {}
PlatformEventReactor::~PlatformEventReactor() {}
#endif

#ifdef PLATFORM_LINUX_KPI
PlatformEventReactor::PlatformEventReactor(){}
PlatformEventReactor::~PlatformEventReactor() {}
#endif
#endif //PLATFORM_LINUX

#endif //_LIB_PLATFORM_LINUX_H_