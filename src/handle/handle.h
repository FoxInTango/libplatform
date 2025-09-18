
#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
    #define FILE_HANDLE
    #define WINDOW_HANDLE
    #define PROCESS_HANDLE
#elif defined(ANDROID) || defined(_ANDROID_)
#elif defined(__linux__)
#elif defined(__APPLE__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_MAC)
#else
#endif
