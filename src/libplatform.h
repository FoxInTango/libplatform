#ifndef _LIB_PLATFORM_H_
#define _LIB_PLATFORM_H_
#include <libcpp/libcpp.h>

#include "event/reactor.h"

namespaceBegin(foxintango)
EXTERN_C_BEGIN

/** platform handles
 */
#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#ifdef foxintangoEXPORT
#if defined(_USRDLL)
#define foxintangoAPI __declspec(dllexport)
#else 
#define foxintangoAPI
#endif
#else
#if defined(_USRDLL)
#define foxintangoAPI __declspec(dllimport)
#else
#define foxintangoAPI
#endif
#endif
#elif defined(ANDROID) || defined(_ANDROID_)
#define foxintangoAPI __attribute__ ((visibility("default")))
#elif defined(__linux__)
#define foxintangoAPI __attribute__ ((visibility("default")))
#elif defined(__APPLE__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_MAC)
#define foxintangoAPI __attribute__ ((visibility("default")))
#else
#define foxintangoAPI
#endif

Error platform_open();
Error platform_close();
Error platform_read();
Error platform_write();
Error platform_set();

/** Event
 */

Error platform_listen();
Error platform_connect();
Error platform_disconnect();

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
