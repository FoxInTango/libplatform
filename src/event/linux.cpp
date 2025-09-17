#ifndef _LIB_PLATFORM_LINUX_H_
#define _LIB_PLATFORM_LINUX_H_

#include "EventEndpoint.h"
#include "EventReactor.h"
using namespace foxintango;
#include <vector>
#include <sys/epoll.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
extern size_t PLATFORM_EVENT_BUFFER_SIZE;

#ifdef PLATFORM_LINUX
#ifdef PLATFORM_LINUX_API
/** Event
 *
 * */
PlatformEvent::PlatformEvent(){}
PlatformEvent::PlatformEvent(size_t _size){
    data = new char[_size];

    assert(data);
    size = _size;
}
PlatformEvent::~PlatformEvent(){
    if(data) delete[] data;
}
/** Endpoint
 * 
 * */
PlatformEventHandler::PlatformEventHandler(){}
PlatformEventHandler::~PlatformEventHandler(){}
PlatformEventHandler::EventStatus PlatformEventHandler::handleEvent(){
    return UNTOUCHED;
}

PlatformEventEndpointContext::PlatformEventEndpointContext(){}
PlatformEventEndpointContext::~PlatformEventEndpointContext(){}

typedef struct _PlatformEventEndpointInfo{
char* location;
int   port;
int   protocol;
}PlatformEventEndpointInfo;

PlatformEventEndpoint::PlatformEventEndpoint(){}
PlatformEventEndpoint::~PlatformEventEndpoint(){}

class PlatformEventBuffer{
public:
    size_t size;
    char*  data;
public:
    PlatformEventBuffer(size_t _size){
        data = new char[_size];
	assert(data);
	size = _size;
    }
   ~PlatformEventBuffer(){
       if(data) delete[] data;
   }
};
inline PlatformEvent* platform_event_fetch_event(const PlatformEventReactorContext* context,const PlatformEventEndpoint* endpoint){
	    assert(context);
	    assert(endpoint);

            size_t r_size = 0;//       Readed Size
	    size_t t_size = 0;// Total Readed Size
            std::vector<PlatformEventBuffer*> event_buffers;
	    PlatformEventBuffer* buffer = new PlatformEventBuffer(context->bufferSize);
            if(!buffer){
                printf("platform_event_fetch_event failed with buffer allocate failed.%s:%s\n",__FILE__,__func__);
                assert(buffer);
	    }
	    while((r_size = read(endpoint->fd,buffer->data,context->bufferSize))){
                 buffer->size = r_size;
                 event_buffers.push_back(buffer);
		 t_size += r_size;
                 buffer = new PlatformEventBuffer(context->bufferSize);
                 if(!buffer){
                    printf("platform_event_fetch_event failed with buffer allocate failed.%s:%s\n",__FILE__,__func__);
                    for(std::vector<PlatformEventBuffer*>::iterator iter = event_buffers.begin();iter != event_buffers.end();iter ++){
                        delete *iter;
                    }
                    assert(buffer);
                 }
            }
            PlatformEvent* event = new PlatformEvent(t_size);
	    size_t offset = 0;
            if(event){
                for(std::vector<PlatformEventBuffer*>::iterator iter = event_buffers.begin();iter != event_buffers.end();iter ++){
                    memcpy(event->data,(*iter)->data + offset,(*iter)->size);
		    offset += (*iter)->size;
		}
            }

	    return event;

}
PlatformEventHandler::EventStatus PlatformEventEndpoint::handleEvent(){
    switch(type){
        case PEET_UNKNOWN:{
            return PlatformEventHandler::UNTOUCHED;
        }break;
	case PEET_UNIX_SOCKET_LISTEN:{
            PlatformEvent* e = platform_event_fetch_event(this->reactor,this);
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
/** Reactor
 *
 * */
PlatformEventReactorContext::PlatformEventReactorContext(){
    epoll = epoll_create1(0);
    if (epoll == -1) {
    }
}

PlatformEventReactorContext::~PlatformEventReactorContext(){
    if(events) delete[] events;
}

int PlatformEventReactorContext::prepare(){
    events = new epoll_event[eventCount];
    return events ? 1 : 0;
}

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
           PlatformEventEndpoint* ep = (PlatformEventEndpoint*)context->events[n].data.ptr;
	   if(ep){
               ep->handleEvent();
	   }
        }
    }
}

#endif

#ifdef PLATFORM_LINUX_KPI
#endif
#endif //PLATFORM_LINUX

PlatformEventReactor::PlatformEventReactor(const PlatformEventReactorCreateInfo& info) {
    bufferSize  = info.BufferSize;
    eventCount  = info.EventCount;
    threadCount = info.ThreadCount;
    prepare();
    for(size_t i = 0;i < threadCount;i ++) {
        std::thread t(event_reactor_process,this);
	t.detach();
    }
}
PlatformEventReactor::~PlatformEventReactor() {}
int PlatformEventReactor::acceptEndpoint(PlatformEventEndpoint* e){
    assert(e);

    e->reactor = this;

    // PlatformEventContext::add
    return 0;
}
int PlatformEventReactor::remvoeEndpoint(PlatformEventEndpoint* e){
    assert(e);

    return 0;
}
#endif //_LIB_PLATFORM_LINUX_H_
