/**
 * Wrap Layer of Platform Event such as EPOLL IOCP etc. 
 */

#ifndef _LIB_PLATFORM_REACTOR_H_
#define _LIB_PLATFORM_REACTOR_H_

#include "EventEndpoint.h"
#include <libcpp/libcpp.h>
#include <set>
namespaceBegin(foxintango)
EXTERN_C_BEGIN
#ifdef PLATFORM_LINUX
#ifdef PLATFORM_LINUX_API
#include <sys/epoll.h>
class foxintangoAPI PlatformEventReactorContext{
public:
 int    epoll;
 struct epoll_event  event;
 struct epoll_event* events;
 size_t bufferSize;
 size_t eventCount;
 size_t threadCount;
 char*  buffer;
 std::set<Thread*> threads;
public:
    PlatformEventReactorContext();
    virtual ~PlatformEventReactorContext();
public:
    int prepare();
};

#endif

#ifdef PLATFORM_LINUX_KPI
#endif
#endif
EXTERN_C_END
namespaceEnd
#endif
