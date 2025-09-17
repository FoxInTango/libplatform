/**
 * Wrap Layer of Platform Event such as EPOLL IOCP etc. 
 */

#ifndef _LIB_PLATFORM_ENDPOINT_H_
#define _LIB_PLATFORM_ENDPOINT_H_

#include "EventEndpoint.h"
#include <libcpp/libcpp.h>
namespaceBegin(foxintango)
EXTERN_C_BEGIN
#ifdef PLATFORM_LINUX
#ifdef PLATFORM_LINUX_API
#include <sys/epoll.h>
class PlatformEventEndpoint;
class PlatformEventReactor;
class PlatformEvent{
public:
    PlatformEventEndpoint* endpoint;
    size_t size;
    char*  data;
public:
    PlatformEvent();
    PlatformEvent(size_t buffer_size);
   ~PlatformEvent();
};

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
class foxintangoAPI PlatformEventEndpointContext {
public:
    PlatformEventEndpointContext();
    virtual ~PlatformEventEndpointContext();
};

#endif

#ifdef PLATFORM_LINUX_KPI
#endif
#endif

typedef struct _PlatformEventEndpointInfo{
char* location;
int   port;
int   protocol;
}PlatformEventEndpointInfo;
class foxintangoAPI PlatformEventEndpoint :public PlatformEventEndpointContext,PlatformEventHandler{
friend class PlatformEventReactor;
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
protected:
    PlatformEventReactor* reactor;
public:
    Type type;
public:
    PlatformEventEndpoint();
   ~PlatformEventEndpoint();
public:
    virtual EventStatus handleEvent();
};
EXTERN_C_END
namespaceEnd
#endif
