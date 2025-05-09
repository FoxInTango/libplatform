#ifndef _LIB_PLATFORM_H_
#define _LIB_PLATFORM_H_
#include <libcpp/libcpp.h>

#include "event/reactor.h"

namespaceBegin(foxintango)
EXTERN_C_BEGIN

platform_open();
platform_close();
platform_read();
platform_write();
platform_set();

/** Event
 */

 platform_listen();
 platform_connect();
 platform_disconnect();

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
