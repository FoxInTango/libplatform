#ifndef _LIBPLATFORM_EVENT_HANDLER_H_
#define _LIBPLATFORM_EVENT_HANDLER_H_
#include <libcpp/libcpp.h>
EXTERN_C_BEGIN
namespaceBegin(foxintango)
class foxintangoAPI PlatformEventHandler{
public:
    PlatformEventHandler();
    virtual ~PlatformEventHandler();
public:
    /** 
     * Default: Nothing To Do.
     * Session: Read by session type
     * Reactor: Accept new session.
     * */
    virtual void handlePlatformEvent();
};
namespaceEnd
EXTERN_C_END
#endif
