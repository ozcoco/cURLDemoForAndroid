//
// Created by Administrator on 2020/4/29.
//

#ifndef CURL_DEMO_LOG_HPP
#define CURL_DEMO_LOG_HPP

#include <android/log.h>
#include <cstdarg>

namespace adx {

    class Logger {

    public:
        inline static void debug(bool __debug) noexcept {
            bDebug = __debug;
        }

        inline static void i(const char *fmt, ...) noexcept {

            if (!bDebug)
                return;
            va_list ap;
            va_start(ap, fmt);
            __android_log_vprint(ANDROID_LOG_INFO, "=^_^=", fmt, ap);
            va_end(ap);
        }

        inline static void w(const char *fmt, ...) noexcept {

            if (!bDebug)
                return;
            va_list ap;
            va_start(ap, fmt);
            __android_log_vprint(ANDROID_LOG_WARN, "*_*", fmt, ap);
            va_end(ap);
        }

        inline static void e(const char *fmt, ...) noexcept {
            if (!bDebug)
                return;
            va_list ap;
            va_start(ap, fmt);
            __android_log_vprint(ANDROID_LOG_ERROR, "+^_^+", fmt, ap);
            va_end(ap);
        }

        inline static void d(const char *fmt, ...) noexcept {
            if (!bDebug)
                return;
            va_list ap;
            va_start(ap, fmt);
            __android_log_vprint(ANDROID_LOG_DEBUG, "^_9", fmt, ap);
            va_end(ap);
        }

    private:
        inline static bool bDebug = true;

    };


}


#endif //CURL_DEMO_LOG_HPP
