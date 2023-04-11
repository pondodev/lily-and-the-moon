#include "logging.h"

#include <stdarg.h>
#include <stdio.h>

void console_log(const char* format, ...) {
    va_list arg;

    va_start(arg, format);
    printf(format, arg);
    va_end(arg);
}

