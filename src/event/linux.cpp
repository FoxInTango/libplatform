#ifndef _LIB_PLATFORM_LINUX_H_
#define _LIB_PLATFORM_LINUX_H_
#include "EventSession.h"
#include "EventEndpoint.h"
#include "EventReactor.h"
#include <libcpp/libcpp.h>
using namespace foxintango;
#include <vector>
#include <sys/epoll.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#ifdef PLATFORM_LINUX
#ifdef PLATFORM_LINUX_API
/** Handler
 * */
PlatformEventHandler::PlatformEventHandler(){}
PlatformEventHandler::~PlatformEventHandler(){}
void PlatformEventHandler::handlePlatformEvent(){}
/** Session
 *
 * */
PlatformEventSessionContext::PlatformEventSessionContext():handler(0),endpoint(0){}
PlatformEventSessionContext::~PlatformEventSessionContext(){
    // remove from endpoint
}

const char* PlatformEventSessionContext::getAttribute(const char* const name){
    if( 0 == strcmp(name,"protocol")){
        switch(type){
            case PEST_UNKNOWN:               { return "unknow";  }break;
            case PEST_UNIX_SOCKET_LISTEN:    { return "unix";    }break;
            case PEST_UNIX_SOCKET_CONNECT:   { return "unix";    }break;
            case PEST_NETLINK_SOCKET_LISTEN: { return "netlink"; }break;
            case PEST_NETLINK_SOCKET_CONNECT:{ return "netlink"; }break;
            case PEST_TCP_SOCKET_LISTEN:     { return "tcp";     }break;
            case PEST_TCP_SOCKET_CONNECT:    { return "tcp";     }break;
            case PEST_UDP_SOCKET_LISTEN:     { return "udp";     }break;
            case PEST_UDP_SOCKET_CONNECT:    { return "udp";     }break;
            default:                         { return "unknow";  }break;
	}
    }

    return 0;
}
int PlatformEventSessionContext::receive(){
        Event event;
        switch(type){
            case PEST_UNKNOWN:               { return 0;}break;
            case PEST_UNIX_SOCKET_LISTEN:    { return 1;}break;
            case PEST_UNIX_SOCKET_CONNECT:   { return 1;}break;
            case PEST_NETLINK_SOCKET_LISTEN: { return 1;}break;
            case PEST_NETLINK_SOCKET_CONNECT:{ return 1;}break;
            case PEST_TCP_SOCKET_LISTEN:     { return 1;}break;
            case PEST_TCP_SOCKET_CONNECT:    { return 1;}break;
            case PEST_UDP_SOCKET_LISTEN:     { return 1;}break;
            case PEST_UDP_SOCKET_CONNECT:    { return 1;}break;
            default:                         { return 1;}break;
        }

        return handler ? handler->handleEvent(&event) : 0;
}

int PlatformEventSessionContext::send(const char* const data,size_t size){
        switch(type){
            case PEST_UNKNOWN:               { return 0;}break;
            case PEST_UNIX_SOCKET_LISTEN:    { return 1;}break;
            case PEST_UNIX_SOCKET_CONNECT:   { return 1;}break;
            case PEST_NETLINK_SOCKET_LISTEN: { return 1;}break;
            case PEST_NETLINK_SOCKET_CONNECT:{ return 1;}break;
            case PEST_TCP_SOCKET_LISTEN:     { return 1;}break;
            case PEST_TCP_SOCKET_CONNECT:    { return 1;}break;
            case PEST_UDP_SOCKET_LISTEN:     { return 1;}break;
            case PEST_UDP_SOCKET_CONNECT:    { return 1;}break;
            default:                         { return 1;}break;
        }

	return 0;
}
/*
inline Event* platform_event_fetch_event(const PlatformEventReactorContext* r,const PlatformEventEndpointContext* e){
	    assert(r);
	    assert(e);

            size_t r_size = 0;//       Readed Size
            Event* event = new Event();
	    if(!event){
                printf("platform_event_fetch_event Event* e = new Event Failed.%s:%s\n",__FILE__,__func__);
		assert(event);
	    }
	    while((r_size = read(e->fd,r->buffer,r->bufferSize))){
                event->buffer.append(r->buffer);
            }
	    return event;

}
*/
/** Endpoint
 *
 * */
PlatformEventEndpointContext::PlatformEventEndpointContext():reactor(0){}
PlatformEventEndpointContext::~PlatformEventEndpointContext(){}
/*
int PlatformEventEndpointContext::fetchEvent(){
    switch(type){
        case PEET_UNKNOWN:{
            return PlatformEventHandler::UNTOUCHED;
        }break;
	case PEET_UNIX_SOCKET_LISTEN:{
             Event* e = platform_event_fetch_event(this->reactor,this);
	}break;
	case PEET_UNIX_SOCKET_CONNECT:{}break;
	case PEET_NETLINK_SOCKET_LISTEN:{}break;
	case PEET_NETLINK_SOCKET_CONNECT:{}break;
        case PEET_TCP_SOCKET_LISTEN:{}break;
	case PEET_TCP_SOCKET_CONNECT:{}break;
	case PEET_UDP_SOCKET_LISTEN:{}break;
	case PEET_UDP_SOCKET_CONNECT:{}break;
        default:break;
    }
   
    return PlatformEventHandler::UNTOUCHED;  
}
*/
/** Reactor
 *
 * */
void event_reactor_wait(PlatformEventReactorContext* context){

}
void event_reactor_process(PlatformEventReactorContext* context){
    if(!context) {
        printf("event_reactor_process exit with context == null\n");
	return;
    }
    while(true){
        int ew_count = epoll_wait(context->epoll,context->events,context->eventCount,-1);
        if (ew_count == -1) {
            printf("event_reactor_process EXIT with epoll_wait return -1 %s:%s\n",__FILE__,__func__);
            return;
	}
        for (int n = 0; n < ew_count; ++ n) {
           PlatformEventHandler* handler = (PlatformEventHandler*)context->events[n].data.ptr;
	   if(handler){
               handler->handlePlatformEvent();
	   }
        }
    }
}

PlatformEventReactorContext::PlatformEventReactorContext(){
    epoll = epoll_create1(0);
    if (epoll == -1) {
    }
}

PlatformEventReactorContext::~PlatformEventReactorContext(){
    if(events) delete[] events;
    if(buffer) delete[] buffer;
}

int PlatformEventReactorContext::prepare(){
    events = new epoll_event[eventCount];
    buffer = new char[bufferSize];
    std::thread t(event_reactor_process,this);
    return events ? 1 : 0;
}

#endif

#ifdef PLATFORM_LINUX_KPI
#endif
#endif //PLATFORM_LINUX

#endif //_LIB_PLATFORM_LINUX_H_
