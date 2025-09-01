#ifndef _LIB_PLATFORM_H_
#define _LIB_PLATFORM_H_
#include <libcpp/libcpp.h>

#include "event/reactor.h"

namespaceBegin(foxintango)
EXTERN_C_BEGIN


/** platform object handles
 */
#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#include <windows.h>
#define PLATFORM_HANDLE HANDLE
#else
#define PLATFORM_HANDLE int
#endif

 
PLATFORM_HANDLE platform_open(char* path);
Error platform_close(PLATFORM_HANDLE handle);
Size platform_read(PLATFORM_HANDLE handle,char* buffer);
Size platform_write();
Error platform_set();

/** Event
 */

Error platform_listen(PLATFORM_HANDLE handle);
Error platform_connect(PLATFORM_HANDLE handle);
Error platform_disconnect(PLATFORM_HANDLE handle);

/** filesystem
 */
/** network
 */

 /** UI
  *  UINativeWindow
  *  UINativeView
  *  UINativeText
  *  
  */

/** GPU
 *  VkRenderTarget
 *  VkRenderer
 *  VkTexture
 *  VkBuffer
 */
EXTERN_C_END
namespaceEnd
#endif
