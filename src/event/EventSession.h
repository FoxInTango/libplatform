#ifndef _LIB_PLATFORM_SESSION_H_
#define _LIB_PLATFORM_SESSION_H_

#include <libcpp/libcpp.h>
EXTERN_C_BEGIN
namespaceBegin(foxintango)
#ifdef PLATFORM_LINUX
#ifdef PLATFORM_LINUX_API
class PlatformEventEndpointContext;
class foxintangoAPI PlatformDeviceInfo{
public:
    char* name;
    char* node;
    char* vendor;
    char* product;
};
class foxintangoAPI PlatformSocketInfo{
public:
    int port;
    char* address;
};
class foxintangoAPI PlatformSocketPeerInfo{
public:
    PlatformSocketInfo local;
    PlatformSocketInfo remote;
};
class foxintangoAPI PlatformFilesystemInfo{
public:
    char* node;
};
class foxintangoAPI PlatformSessionInfo{
public:
union {
    PlatformDeviceInfo     hardware;
    PlatformSocketPeerInfo socketpeer;
    PlatformFilesystemInfo filesystem;
};
};
class foxintangoAPI PlatformEventSessionContext:public EventSessionInterface{
public:
    enum Type{
              PEST_UNKNOWN,
	      PEST_UNIX_SOCKET_LISTEN,
              PEST_UNIX_SOCKET_CONNECT,
              PEST_NETLINK_SOCKET_LISTEN,
              PEST_NETLINK_SOCKET_CONNECT,
              PEST_TCP_SOCKET_LISTEN,
              PEST_TCP_SOCKET_CONNECT,
              PEST_UDP_SOCKET_LISTEN,
	      PEST_UDP_SOCKET_CONNECT
              };
private:
    int fd;
    Type type;
    PlatformSessionInfo info;
    EventHandler* handler;
    PlatformEventEndpointContext* endpoint;
public:
    PlatformEventSessionContext();
    virtual ~PlatformEventSessionContext();
public:
    virtual const char* getAttribute(const char* const name);
public:
    virtual int receive();
    virtual int send(const char* const data,size_t size);
};

#endif

#ifdef PLATFORM_LINUX_KPI
#endif
#endif
namespaceEnd
EXTERN_C_END
#endif
