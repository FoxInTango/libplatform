/**
 * Wrap Layer of Platform Event such as EPOLL IOCP etc. 
 */

#ifndef _LIB_PLATFORM_REACTOR_H_
#define _LIB_PLATFORM_REACTOR_H_

#include <libcpp/libcpp.h>

namespaceBegin(foxintango)
EXTERN_C_BEGIN

class foxintangoAPI PlatformEventReactor{
public:
    PlatformEventReactor();
    ~PlatformEventReactor();
public:
};
EXTERN_C_END
namespaceEnd
#endif