/**
 * Wrap Layer of Platform Event such as EPOLL IOCP etc. 
 */

#ifndef _LIB_PLATFORM_ENDPOINT_H_
#define _LIB_PLATFORM_ENDPOINT_H_

#include <libcpp/libcpp.h>
EXTERN_C_BEGIN
namespaceBegin(foxintango)
#ifdef PLATFORM_LINUX
#ifdef PLATFORM_LINUX_API
#include <sys/epoll.h>
class PlatformEventEndpointContext;
class PlatformEventReactorContext;
/*
class PlatformEvent{
public:
    PlatformEventEndpointContext* endpoint;
    size_t size;
    char*  data;
public:
    PlatformEvent();
    PlatformEvent(size_t buffer_size);
   ~PlatformEvent();
};
*/
class foxintangoAPI PlatformEventHandler{
public:
    enum EventStatus{
        UNTOUCHED,
	DILLED
    };
public:
    PlatformEventHandler();
    virtual ~PlatformEventHandler();
public:
    virtual EventStatus handleEvent();
};
class foxintangoAPI PlatformEventEndpointContext :public PlatformEventHandler{
public:
    enum Type{
              PEET_UNKNOWN,
	      PEET_UNIX_SOCKET_LISTEN,
              PEET_UNIX_SOCKET_CONNECT,
              PEET_NETLINK_SOCKET_LISTEN,
              PEET_NETLINK_SOCKET_CONNECT,
              PEET_TCP_SOCKET_LISTEN,
              PEET_TCP_SOCKET_CONNECT,
              PEET_UDP_SOCKET_LISTEN,
	      PEET_UDP_SOCKET_CONNECT
              };
public:
    int  fd;
    Type type;
    PlatformEventReactorContext* reactor;
public:
    PlatformEventEndpointContext();
    virtual ~PlatformEventEndpointContext();
public:
    virtual EventStatus handleEvent();
};

#endif

#ifdef PLATFORM_LINUX_KPI
#endif
#endif
namespaceEnd
EXTERN_C_END
#endif
